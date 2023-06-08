#include "config.h"

#include <QDir>
#include <QStandardPaths>
#include <QFile>
#include <QFontDatabase>
#include <QFont>


Config::Config()
{

}

QString Config::getTimeStr(int time)
{
    QString time_str;
    if(time < 0) {
        time = -time;
        time_str = '-';
    }
    int s = time % 60;
    time = int(time / 60);
    int m = time % 60;
    int h = int(time / 60);
    return time_str+QString("%1:%2:%3")
            .arg(h, 2, 10, QChar('0'))
            .arg(m, 2, 10, QChar('0'))
            .arg(s, 2, 10, QChar('0'));
}

bool Config::init()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    QDir dir;
    if (!dir.exists(path)) {
        dir.mkdir(path);
    }

    QString dbFile = QString("%1/%2").arg(path,"config.db");
    this->db = QSqlDatabase::addDatabase("QSQLITE", "config");
    this->db.setDatabaseName(dbFile);
    if(!this->db.open()) {
        return false;
    }

    QSqlQuery query = QSqlQuery(this->db);
    query.exec("select * from sqlite_master where type = 'table' and name = 'time_pionts'");
    if(!query.next()) {
        //初始化表
        query.exec("create table time_pionts (time varchar)");
    }
    QList<QString> list = getTimePionts(this->db);
    if(list.isEmpty()) {
        addTimePiont(this->db, QString("08:00:00"));
        addTimePiont(this->db, QString("12:00:00"));
        addTimePiont(this->db, QString("14:00:00"));
        addTimePiont(this->db, QString("17:30:00"));
    }

    return true;
}

QSqlDatabase Config::getDb() {
    return this->db;
}

QList<QString> Config::getTimePionts(QSqlDatabase db)
{
    QSqlQuery query(db);
    QList<QString> list;

    query.exec(QString("select time from time_pionts order by time asc"));
    while(query.next()) {
        list.append(query.value(0).toString());
    }

    return list;
}

int Config::addTimePiont(QSqlDatabase db, QString time)
{
    QSqlQuery query(db);
    int id = 0;
    QString insert_sql = QString("insert into time_pionts (time) values('%1')").arg(time);
    query.prepare(insert_sql);
    if (query.exec()) {
        id = query.lastInsertId().toInt();
    }
    return id;
}

bool Config::truncateTimePioonts(QSqlDatabase db)
{
    QSqlQuery query(db);
    query.exec("delete from time_pionts");
    if(query.next()) {
        return true;
    }
    return false;
}

QFont Config::getFont(int size)
{
    QFont font = QFont("MiSans");
    font.setPointSize(size);
    return font;
}
