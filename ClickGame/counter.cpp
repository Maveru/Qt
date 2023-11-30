#include "counter.h"
#include <QDebug>
Counter::Counter(QObject *parent)
    : QObject{parent}
{
    m_count = 0;
    m_up = true;
    m_timer = new QTimer(this);
    m_timer->setInterval(1000);

    connect(m_timer,&QTimer::timeout,[=](){
        ++m_count;
        qDebug() << m_count;
        if(m_count == 10){
            m_count = 0;
            //qDebug() << "Time up!";
            emit countStopped();
        }
        emit countChanged();// always emit signal when value changes on cpp code
    });

    qDebug() << "Counter here!";
}

void Counter::setCount(int newCount)
{
    if (m_count == newCount)
        return;
    m_count = newCount;
    emit countChanged();
}

void Counter::setUp(bool newUp)
{
    if (m_up == newUp)
        return;
    m_up = newUp;
    emit upChanged();
}


void Counter::setTimer(QTimer *newTimer)
{
    m_timer = newTimer;
}

void Counter::start()
{
    m_timer->start();
}

void Counter::stop()
{
    m_timer->stop();
}
