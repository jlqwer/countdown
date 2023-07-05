
#ifndef CHECKUPDATE_H
#define CHECKUPDATE_H


#include <QObject>
#include <QNetworkReply>

class checkUpdate : public QObject
{
    Q_OBJECT
    public:
        explicit checkUpdate(QObject *parent = nullptr);
    signals:
        void resultReady(const QString version, const QString update_time, const QString url, const QString describe);

    public slots:
        void doCheckUpdate();
    private slots:
        void checkUpdateSlot(QNetworkReply*);
};

#endif // CHECKUPDATE_H
