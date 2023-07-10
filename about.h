#ifndef ABOUT_H
#define ABOUT_H

#include <QThread>
#include <QWidget>
#include <checkUpdate.h>

namespace Ui {
class About;
}

class About : public QWidget
{
    Q_OBJECT

    public:
        explicit About(QWidget *parent = nullptr);
        ~About();
    private slots:
        void on_check_update_clicked();
        void checkUpdateReceiv(QString version, QString update_time, QString url, QString describe);

    private:
        Ui::About *ui;
        QThread m_checkUpdateThread;
        checkUpdate *m_checkUpdate;

    signals:
        void checkUpdateSignals();
};

#endif // ABOUT_H
