#ifndef RANDOMNUMBER_H
#define RANDOMNUMBER_H

#include <QObject>
#include <QQmlPropertyValueSource>
#include <QQmlProperty>
#include <qqml.h>
#include <QTimer>
#include <QDebug>

class RandomNumber : public QObject, public QQmlPropertyValueSource
{
    Q_OBJECT
    Q_PROPERTY(int maxValue READ maxValue WRITE setMaxValue NOTIFY maxValueChanged FINAL)
    Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged FINAL)
    Q_INTERFACES(QQmlPropertyValueSource)
public:
    explicit RandomNumber(QObject *parent = nullptr);

    virtual void setTarget(const QQmlProperty & prop);
    int maxValue() const;
    void setMaxValue(int newMaxValue);


    int interval() const;
    void setInterval(int newInterval);

signals:
    void maxValueChanged();
    void intervalChanged();

public slots:

private slots:
    void updateProperty();


private:
    QQmlProperty m_targetProperty;
    int m_maxValue;
    QTimer * m_timer;

    int m_interval;
};

#endif // RANDOMNUMBER_H
