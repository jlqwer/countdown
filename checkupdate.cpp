#include "checkupdate.h"
#include <QNetworkInterface>
#include <QJsonDocument>
#include <QJsonObject>

checkUpdate::checkUpdate(QObject *parent) : QObject(parent){}

void checkUpdate::doCheckUpdate()
{
    QNetworkRequest netReq;
    netReq.setUrl(QUrl("https://raw.githubusercontent.com/jlqwer/countdown/main/update.json"));

    QNetworkAccessManager *m_manager = new QNetworkAccessManager(this);
    // 发送参数
    m_manager->get(netReq);
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(checkUpdateSlot(QNetworkReply*)));
}

void checkUpdate::checkUpdateSlot(QNetworkReply* reply)
{
    QString version = "";
    QString update_time = "";
    QString url = "";
    QString describe = "";

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray bytes = reply->readAll();
        QJsonDocument jsonDocument = QJsonDocument::fromJson(bytes);
        QJsonObject jsonObject = jsonDocument.object();
        version = jsonObject.value("version").toString();
        update_time = jsonObject.value("update_time").toString();
        url = jsonObject.value("url").toString();
        describe = jsonObject.value("describe").toString();
    }
    reply->abort();
    reply->deleteLater();
    reply->close();
    emit resultReady(version, update_time, url, describe);
}
