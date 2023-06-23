#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QThread>
#include <QSqlDatabase>
#include <QMenu>
#include "config.h"
#include "setting.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Countdown; }
QT_END_NAMESPACE

class Countdown : public QWidget
{
    Q_OBJECT

    public:
        Countdown(QWidget *parent = nullptr);
        ~Countdown();
        void init();
        QLabel time_label;
        QList<QString> timePionts;

    private:
        Ui::Countdown *ui;
        QString getTimeStr();
        QSqlDatabase db;
        Config *config;
        Setting *setting_w;
        int fontId;

        QMenu menu;
        bool settingIsShow;

        void savePos(int x, int y);

    protected:
        bool m_isPressed = false;
        QPoint m_startMovePos;
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void enterEvent(QEnterEvent *event);

    public slots:
        void downTime();
        void quit();    //右键退出
        void showSetting();  //编辑配置文件
        void returnMain();
        void about();   //关于
};
#endif // COUNTDOWN_H
