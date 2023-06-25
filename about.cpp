#include "about.h"
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
}

About::~About()
{
    delete ui;
}
void About::on_check_update_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/jlqwer/countdown/releases/latest"));
}
