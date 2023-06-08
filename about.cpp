#include "about.h"
#include "config.h"
#include "ui_about.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QDesktopServices>
#include <QFontDatabase>

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
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
