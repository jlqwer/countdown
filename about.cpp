#include "about.h"
#include "config.h"
#include "ui_about.h"

#include <QDesktopServices>
#include <QMessageBox>

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);
    this->ui->version->setText(QString("Version %1").arg(QApplication::applicationVersion()));
}

About::~About()
{
    delete ui;
}

void About::on_close_clicked()
{
    this->close();
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

//鼠标点击
void About::mousePressEvent(QMouseEvent *event)
{
    //左键窗口拖动
    if (event->button() == Qt::LeftButton) {
        m_isPressed = true;
        m_startMovePos = event->globalPosition().toPoint() - this->frameGeometry().topLeft();
    }
}

//鼠标拖动
void About::mouseMoveEvent(QMouseEvent *event)
{
    if(m_isPressed) {
        QPoint curPos = this->mapToGlobal(event->pos() - m_startMovePos);
        move(curPos);
    }
}
