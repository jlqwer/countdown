#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>

class Config
{
    public:
        Config();
        bool init();
        QSqlDatabase getDb();
        static QString getTimeStr(int last_time);
        static QList<QString> getTimePionts(QSqlDatabase db);
        static int addTimePiont(QSqlDatabase db, QString time);
        static bool truncateTimePioonts(QSqlDatabase db);
        static QFont getFont(int size);
        static QString getConfig(QSqlDatabase, QString);
        static QString setConfig(QSqlDatabase, QString, QString);

        static int compareVersion(QString version1, QString version2);

    private:
        QSqlDatabase db;
};

#endif // CONFIG_H
