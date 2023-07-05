#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QThread>
#include <QSqlDatabase>
#include <QMenu>
#include <checkUpdate.h>
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
        QStringList getTimeStr();
        QStringList splitLastTime(int time);
        QSqlDatabase db;
        Config *config;
        Setting *setting_w;
        int fontId;

        QMenu menu;
        bool settingIsShow;

        QThread m_checkUpdateThread;
        checkUpdate *m_checkUpdate;

        void savePos(int x, int y);

    protected:
        bool m_isPressed = false;
        QPoint m_startMovePos;

        void paintEvent(QPaintEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void enterEvent(QEnterEvent *event);

    signals:
        void checkUpdateSignals();

    public slots:
        void downTime();
        void quit();    //右键退出
        void showSetting();  //编辑配置文件
        void returnMain();
        void about();   //关于
        void checkUpdateReceiv(QString version, QString update_time, QString url, QString describe);
};
#endif // COUNTDOWN_H
