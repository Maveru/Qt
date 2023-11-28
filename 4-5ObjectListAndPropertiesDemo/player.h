#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(bool playing READ playing WRITE setPlaying NOTIFY playingChanged FINAL)
    Q_PROPERTY(QString position READ position WRITE setPosition NOTIFY positionChanged FINAL)



    QString name() const;
    void setName(const QString &newName);

    bool playing() const;
    void setPlaying(bool newPlaying);

    QString position() const;
    void setPosition(const QString &newPosition);

signals:

    void nameChanged();
    void playingChanged();
    void positionChanged();

private:
    QString m_name;
    bool m_playing;
    QString m_position;
};

#endif // PLAYER_H
