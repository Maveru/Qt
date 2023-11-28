#ifndef FOOTBALLTEAM_H
#define FOOTBALLTEAM_H

#include <QObject>
#include <QQmlListProperty>
#include <QVector>
#include <QDebug>
#include "player.h"
class FootBallTeam : public QObject
{
    Q_OBJECT
public:
    explicit FootBallTeam(QObject *parent = nullptr);
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged FINAL)
    Q_PROPERTY(QString coach READ coach WRITE setCoach NOTIFY coachChanged FINAL)
    Q_PROPERTY(Player *  captain READ captain WRITE setCaptain NOTIFY captainChanged FINAL)
    Q_PROPERTY(QQmlListProperty<Player> players READ players NOTIFY playersChanged FINAL)



    QString title() const;
    void setTitle(const QString &newTitle);

    Player *captain() const;
    void setCaptain(Player *newCaptain);

    QString coach() const;
    void setCoach(const QString &newCoach);



    QQmlListProperty<Player> players();

    //Helper Methods
    void appendPlayerCustom(Player *);
    int playerCountCustom() const;
    Player *playerCustom(int) const;
    void clearPlayersCustom();

signals:

    void titleChanged();
    void captainChanged();
    void coachChanged();
    void playersChanged();



private:
    //CallBack Methods

    static void appendPlayer(QQmlListProperty<Player>*,Player*);
    static long long int playerCount(QQmlListProperty<Player>*);
    static Player *player (QQmlListProperty<Player>*,long long int );
    static void clearPlayers(QQmlListProperty<Player>*);



    QString m_title;
    Player *m_captain = nullptr;
    QString m_coach;
    QVector<Player*> m_players;
};

#endif // FOOTBALLTEAM_H
