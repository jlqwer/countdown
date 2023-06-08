#include "countdown.h"
#include "ui_countdown.h"
#include "about.h"

#include <QDateTime>
#include <QTimer>
#include <QString>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QFileInfo>
#include <QCoreApplication>
#include <QMessageBox>
#include <QProcess>
#include <QStandardPaths>
#include <QMessageBox>
#include <QPushButton>
#include <QDesktopServices>
#include <QImage>
#include <QFontDatabase>

Countdown::Countdown(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Countdown)
{
    ui->setupUi(this);
    this->ui->time_label->setStyleSheet("color:rgb(51,255,0);background:rgba(0, 0, 0, 1);");
    qApp->setQuitOnLastWindowClosed(false);
    this->init();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(downTime()));
    timer->start(1000);
}

Countdown::~Countdown()
{
    delete ui;
}

//右键菜单
void Countdown::quit()
{
    qApp->quit();
}

void Countdown::init()
{
    //初始化数据库&加载配置
    this->config = new Config();
    if(!this->config->init()) {
        QMessageBox::warning(NULL,"提示","初始化失败!");
    }
    this->ui->time_label->setFont(Config::getFont(16));

    this->db = this->config->getDb();
    this->timePionts = Config::getTimePionts(this->db);
    this->settingIsShow = false;
    this->menu.addAction(QIcon(":/resources/icon/edit.png"), "时间设置", this, &Countdown::showSetting);
    this->menu.addAction(QIcon(":/resources/icon/logo.ico"), "关于", this, &Countdown::about);
    this->menu.addAction(QIcon(":/resources/icon/exit.png"), "退出", this, &Countdown::quit);
}


//编辑配置
void Countdown::showSetting()
{
    if(this->settingIsShow) {
        this->setting_w->activateWindow();
        return;
    }
    this->settingIsShow = true;
    this->setting_w = new Setting();
    this->setting_w->init(this->db);
    connect(this->setting_w,SIGNAL(returnMain()),this,SLOT(returnMain()));
    this->setting_w->show();
}

//关于
void Countdown::about()
{
    About about_w;
    about_w.exec();
    return;
}



void Countdown::enterEvent(QEnterEvent *event)
{
    int width = QGuiApplication::primaryScreen()->geometry().width();
    if (event->globalPosition().x() > width - 100) {
        //移出
    }
}

//鼠标点击
void Countdown::mousePressEvent(QMouseEvent *event)
{
    //左键窗口拖动
    if (event->button() == Qt::LeftButton) {
        m_isPressed = true;
        m_startMovePos = event->globalPosition().toPoint() - this->frameGeometry().topLeft();
    }

    //右键菜单
    if (event->button() == Qt::RightButton) {
        //菜单位置
        QPoint piont = event->pos();
        piont.setY(piont.ry() + 20);
        this->menu.exec(this->mapToGlobal(piont));
    }
}

//鼠标拖动
void Countdown::mouseMoveEvent(QMouseEvent *event)
{
    if(m_isPressed)
    {
        move(this->mapToGlobal(event->pos() - m_startMovePos));
    }
}


QString Countdown::getTimeStr()
{
    QDateTime time = QDateTime::currentDateTime();   //获取当前时间
    int64_t now = time.toSecsSinceEpoch();
    QString date = time.toString("yyyy-MM-dd");
    long long int last_time = 0;

    foreach (QString node, this->timePionts)
    {
        QDateTime node_time = QDateTime::fromString(date+" "+node, "yyyy-MM-dd HH:mm:ss");
        int64_t time_sec = node_time.toSecsSinceEpoch();
        last_time = time_sec - now;
        if (now < time_sec) {
            break;
        }
    }

    return Config::getTimeStr(last_time);
}

void Countdown::downTime()
{
    QString time_str = getTimeStr();
    this->ui->time_label->setText(time_str);
}

void Countdown::returnMain()
{
    this->settingIsShow = false;
    this->timePionts = Config::getTimePionts(this->db);
    this->show();
}



