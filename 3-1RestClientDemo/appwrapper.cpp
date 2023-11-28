#include "appwrapper.h"
#include <QNetworkRequest>
#include <QIODevice>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QQmlContext>


AppWrapper::AppWrapper(QObject *parent): QObject{parent},
    mNetManager(new QNetworkAccessManager(this)),
    mNetReply(nullptr),
    mDataBuffer(new QByteArray)
{

}

void AppWrapper::fetchPosts(int number)
{
    //Inicialize API DATA
    const QUrl API_ENDPOINT("https://v2.jokeapi.dev/joke/Any?type=single&amount="+ QString::number(number));

    QNetworkRequest request;
    request.setUrl(API_ENDPOINT);

    mNetReply = mNetManager->get(request);
    connect(mNetReply,&QIODevice::readyRead,this,&AppWrapper::dataReadyRead);
    connect(mNetReply,&QNetworkReply::finished,this,&AppWrapper::dataReadFinished);


}

void AppWrapper::removeLast()
{
    if(mJokes.size()!=0){

        mJokes.removeLast();
        resetModel();
    }
}

QStringList AppWrapper::jokes() const
{
    return mJokes;
}

bool AppWrapper::initialize()
{
//    QQmlApplicationEngine engine;

    mEngine.rootContext()->setContextProperty("Wrapper",this);
    resetModel();
    mEngine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if(mEngine.rootObjects().isEmpty()){
        return false;
    }else{
        return true;
    }


}

void AppWrapper::dataReadyRead()
{
    mDataBuffer->append(mNetReply->readAll());
}

void AppWrapper::resetModel()
{
    mEngine.rootContext()->setContextProperty("myModel",QVariant::fromValue(mJokes));
}

void AppWrapper::dataReadFinished()
{
    //Parse the JSON
    if(mNetReply->error()){
        qDebug() << "Error: " <<mNetReply->errorString();
    }else{
        //Turn data into JSON
        QJsonDocument doc = QJsonDocument::fromJson(*mDataBuffer);
        QJsonObject data = doc.object();
        QJsonArray arry = data["jokes"].toArray();

        qDebug()<< "Has descargado " <<arry.size() <<" chistes!";

        for(int i {0}; i < arry.size();i++){
            QJsonObject object = arry.at(i).toObject();

            QString joke =  object["joke"].toString();

            mJokes.append(joke);

            //qDebug() << joke;
        }
        if(arry.size() !=0 ){
            resetModel();
        }
        // Clear Buffr

        mDataBuffer->clear();
    }


}
