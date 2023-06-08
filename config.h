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

    private:
        QSqlDatabase db;
};

#endif // CONFIG_H
