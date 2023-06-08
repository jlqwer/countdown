#include "config.h"
#include "timeitem.h"
#include "ui_timeitem.h"

TimeItem::TimeItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeItem)
{
    ui->setupUi(this);
}

TimeItem::~TimeItem()
{
    delete ui;
}


void TimeItem::init(QListWidgetItem *item, QString text)
{
    this->ui->text->setFont(Config::getFont(14));
    this->ui->del->setFont(Config::getFont(12));
    this->item = item;
    this->ui->text->setText(text);
}


void TimeItem::on_del_clicked()
{
    emit deleteItem(this->item);
}
