#include "footballteam.h"

FootBallTeam::FootBallTeam(QObject *parent)
    : QObject{parent}
{

}

QString FootBallTeam::title() const
{
    return m_title;
}

void FootBallTeam::setTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    emit titleChanged();
}

Player *FootBallTeam::captain() const
{
    return m_captain;
}

void FootBallTeam::setCaptain(Player *newCaptain)
{
    if (m_captain == newCaptain)
        return;
    m_captain = newCaptain;
    emit captainChanged();
}

QString FootBallTeam::coach() const
{
    return m_coach;
}

void FootBallTeam::setCoach(const QString &newCoach)
{
    if (m_coach == newCoach)
        return;
    m_coach = newCoach;
    emit coachChanged();
}

QQmlListProperty<Player> FootBallTeam::players()
{
    return QQmlListProperty<Player>(this,this,&FootBallTeam::appendPlayer,
                                    &FootBallTeam::playerCount,
                                    &FootBallTeam::player,
                                    &FootBallTeam::clearPlayers);
}

void FootBallTeam::appendPlayerCustom(Player *player)
{
    qDebug() << "Added: " << player->name();
    m_players.append(player);
}

int FootBallTeam::playerCountCustom() const
{
    return m_players.count();
}

Player *FootBallTeam::playerCustom(int index) const
{
    return m_players.at(index);
}

void FootBallTeam::clearPlayersCustom()
{
    m_players.clear();
}

void FootBallTeam::appendPlayer(QQmlListProperty<Player> *list, Player *player)
{
    reinterpret_cast<FootBallTeam*>(list->data)->appendPlayerCustom(player);
}

long long int FootBallTeam::playerCount(QQmlListProperty<Player> * list)
{
    return reinterpret_cast<FootBallTeam*>(list->data)->playerCountCustom();
}

Player *FootBallTeam::player(QQmlListProperty<Player> * list, long long int index)
{
    return reinterpret_cast<FootBallTeam*>(list->data)->playerCustom(index);
}

void FootBallTeam::clearPlayers(QQmlListProperty<Player> * list)
{
    reinterpret_cast<FootBallTeam*>(list->data)->clearPlayersCustom();
}
