#include "addtime.h"
#include "config.h"
#include "ui_addtime.h"

AddTime::AddTime(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTime)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    ui->setupUi(this);
}

AddTime::~AddTime()
{
    delete ui;
}

void AddTime::on_close_clicked()
{
    this->close();
}


void AddTime::on_addTime_clicked()
{
    emit returnSetting(this->ui->time->text());
    this->close();
}

