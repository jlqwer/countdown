#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QMouseEvent>
#include <QThread>
#include <checkUpdate.h>

namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

    public:
        explicit About(QWidget *parent = nullptr);
        ~About();

    private slots:
        void on_close_clicked();
        void on_check_update_clicked();
        void checkUpdateReceiv(QString version, QString update_time, QString url, QString describe);

    private:
        Ui::About *ui;
        QThread m_checkUpdateThread;
        checkUpdate *m_checkUpdate;


    protected:
        bool m_isPressed = false;
        QPoint m_startMovePos;

        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);

    signals:
        void checkUpdateSignals();
};

#endif // ABOUT_H
