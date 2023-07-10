#include "about.h"
#include "config.h"
#include "ui_about.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFontDatabase>

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    this->setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowStaysOnTopHint);
    ui->setupUi(this);
    this->ui->version->setText(QString("Version %1").arg(QApplication::applicationVersion()));
}

About::~About()
{
    delete ui;
}
void About::on_check_update_clicked()
{
    m_checkUpdate = new checkUpdate();
    m_checkUpdate->moveToThread(&m_checkUpdateThread);
    connect(this, &About::checkUpdateSignals, m_checkUpdate, &checkUpdate::doCheckUpdate);
    connect(&m_checkUpdateThread, &QThread::finished, m_checkUpdate, &QObject::deleteLater);
    connect(m_checkUpdate, &checkUpdate::resultReady, this, &About::checkUpdateReceiv);
    m_checkUpdateThread.start();
    emit checkUpdateSignals();
}


void About::checkUpdateReceiv(QString version,QString update_time,QString url,QString describe)
{
    m_checkUpdateThread.quit();
    m_checkUpdateThread.wait();
    if (Config::compareVersion(version, QApplication::applicationVersion())) {
        QPushButton *okbtn=new QPushButton(QObject::tr("去更新"));
        connect(okbtn, &QPushButton::clicked, this, [=](){
            QDesktopServices::openUrl(QUrl(url));
        });
        QPushButton *cancelbtn=new QPushButton(QObject::tr("取消"));
        QMessageBox *updatemsgbox=new QMessageBox;
        updatemsgbox->addButton(okbtn,QMessageBox::YesRole);
        updatemsgbox->addButton(cancelbtn,QMessageBox::RejectRole);
        updatemsgbox->setWindowTitle(QString("检测到新版本[%1]").arg(version));
        updatemsgbox->setText(QString("新版本发布日期：%1\n版本更新日志：\n  %2").arg(update_time, describe));
        updatemsgbox->show();
    }
}
