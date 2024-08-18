#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QElapsedTimer>
#include <QTimer>
#include <QTime>
#include <QObject>


class Stopwatch : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString elapsedTime READ elapsedTime NOTIFY elapsedTimeChanged)

public:
    explicit Stopwatch(QObject* parent = nullptr);

    QString elapsedTime() const;

public slots:
    void start();
    void stop();
    void reset();

signals:
    void elapsedTimeChanged();

private slots:
    void updateElapsedTime();

private:
    QElapsedTimer* m_elapsedTimer;
    QTimer* m_updateTimer;
    QString m_elapsedTime;

    void setElapsedTime(const QString &newElapsedTime);
};

#endif // STOPWATCH_H
