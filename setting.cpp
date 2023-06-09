#include "setting.h"
#include "timeitem.h"
#include "ui_setting.h"
#include <QMessageBox>
#include "config.h"

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->setupUi(this);
}

Setting::~Setting()
{
    delete ui;
}

void Setting::init(QSqlDatabase database)
{
    this->ui->title->setFont(Config::getFont(10));
    this->ui->timeAdd->setFont(Config::getFont(12));
    this->ui->timeList->setFont(Config::getFont(14));
    this->ui->timeSave->setFont(Config::getFont(14));

    this->db = database;
    QList<QString> list = Config::getTimePionts(database);
    QList<QString>::const_iterator ci;

    this->ui->timeList->setFocusPolicy(Qt::NoFocus);
    this->ui->timeList->setAlternatingRowColors(true);
    for(ci = list.constBegin(); ci != list.constEnd(); ++ci){
        addListWidgetItem(*ci);
    }
}

void Setting::addListWidgetItem(QString row)
{
    QListWidgetItem* item;
    item = new QListWidgetItem(ui->timeList);
    item->setData(Qt::UserRole, row);
    item->setSizeHint(QSize(380,36));
    TimeItem *timeItem = new TimeItem(ui->timeList);
    connect(timeItem,SIGNAL(deleteItem(QListWidgetItem *)),this,SLOT(deleteItem(QListWidgetItem *)));
    timeItem->init(item, row);
    ui->timeList->addItem(item);
    ui->timeList->setItemWidget(item, timeItem);
}


void Setting::addNewListWidgetItem(QString row)
{
    int i = 0, nCnt = this->ui->timeList->count();
    for (i = 0; i < nCnt; ++i) {
        QListWidgetItem* pItem = this->ui->timeList->item(i);
        if(row == pItem->data(Qt::UserRole).toString()) {
               QMessageBox::warning(this, "错误", "该时间点已存在！", QMessageBox::Ok);
               return;
        }
    }

    addListWidgetItem(row);
}

//鼠标点击
void Setting::mousePressEvent(QMouseEvent *event)
{
    //左键窗口拖动
    if (event->button() == Qt::LeftButton) {
        m_isPressed = true;
        m_startMovePos = event->globalPosition().toPoint()-this->frameGeometry().topLeft();
    }
}

//鼠标拖动
void Setting::mouseMoveEvent(QMouseEvent *event)
{
    if(m_isPressed)
    {
        move(this->mapToGlobal(event->pos() - m_startMovePos));
    }
}

void Setting::on_close_clicked()
{
    emit returnMain();
    this->close();
}

void Setting::deleteItem(QListWidgetItem *item)
{
    this->ui->timeList->removeItemWidget(item);
    QListWidgetItem *aItem = this->ui->timeList->takeItem(ui->timeList->row(item));
    delete aItem;
}

//保存
void Setting::on_timeSave_clicked()
{
    Config::truncateTimePioonts(this->db);

    int i = 0, nCnt = this->ui->timeList->count();
    for (i = 0; i < nCnt; ++i) {
        QListWidgetItem* pItem = this->ui->timeList->item(i);
        Config::addTimePiont(this->db, pItem->data(Qt::UserRole).toString());
    }
    emit returnMain();
    this->close();
}


void Setting::on_timeAdd_clicked()
{
    addtime_w = new AddTime();
    connect(addtime_w,SIGNAL(returnSetting(QString)),this,SLOT(addNewListWidgetItem(QString)));
    addtime_w->show();
    return;
}

