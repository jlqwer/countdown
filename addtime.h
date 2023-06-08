#ifndef ADDTIME_H
#define ADDTIME_H

#include <QDialog>

namespace Ui {
class AddTime;
}

class AddTime : public QDialog
{
    Q_OBJECT

    public:
        explicit AddTime(QWidget *parent = nullptr);
        ~AddTime();

    private slots:
        void on_close_clicked();
        void on_addTime_clicked();

    private:
        Ui::AddTime *ui;

    signals:
        void returnSetting(QString row);
};

#endif // ADDTIME_H
