
#include "randomnumber.h"
#include<QRandomGenerator>

RandomNumber::RandomNumber(QObject *parent)
    : QObject{parent}
{
    m_maxValue = 500;
    m_timer = new QTimer(this);
    //m_timer->setInterval(m_maxValue);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(updateProperty()));
    m_timer->start(750);

}

void RandomNumber::setTarget(const QQmlProperty &prop)
{
    m_targetProperty = prop;
}

int RandomNumber::maxValue() const
{
    return m_maxValue;
}

void RandomNumber::setMaxValue(int newMaxValue)
{
    if (m_maxValue == newMaxValue)
        return;
    m_maxValue = newMaxValue;
    emit maxValueChanged();
}

void RandomNumber::updateProperty()
{
    m_targetProperty.write(QRandomGenerator::global()->bounded(m_maxValue));
}

int RandomNumber::interval() const
{
    return m_interval;
}

void RandomNumber::setInterval(int newInterval)
{
    if (m_interval == newInterval)
        return;
    m_timer->setInterval(newInterval);
    qDebug() << "Interval set to: " << newInterval;
    emit intervalChanged();
}
