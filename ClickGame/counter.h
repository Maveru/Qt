#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>
#include <QTimer>
class Counter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged FINAL)
    Q_PROPERTY(bool up READ up WRITE setUp NOTIFY upChanged FINAL) // 1 si contamos hacia arriba

public:
    explicit Counter(QObject *parent = nullptr);

    int count(){
        return m_count;
    }

    bool up(){
        return m_up;
    }

    void setCount(int newCount);
    void setUp(bool newUp);


    void setTimer(QTimer *newTimer);

    //Helper methods

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();


signals:

    void countChanged();
    void upChanged();
    void countStopped();

private:

    int m_count;
    bool m_up;

    QTimer* m_timer;
};

#endif // COUNTER_H
