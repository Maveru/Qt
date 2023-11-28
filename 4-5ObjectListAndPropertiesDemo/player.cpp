#include "player.h"

Player::Player(QObject *parent)
    : QObject{parent}
{

}

QString Player::name() const
{
    return m_name;
}

void Player::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

bool Player::playing() const
{
    return m_playing;
}

void Player::setPlaying(bool newPlaying)
{
    if (m_playing == newPlaying)
        return;
    m_playing = newPlaying;
    emit playingChanged();
}

QString Player::position() const
{
    return m_position;
}

void Player::setPosition(const QString &newPosition)
{
    if (m_position == newPosition)
        return;
    m_position = newPosition;
    emit positionChanged();
}
