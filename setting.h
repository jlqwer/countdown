#ifndef SETTING_H
#define SETTING_H

#include <QListWidgetItem>
#include <QSqlDatabase>
#include <QWidget>
#include "qevent.h"
#include "config.h"
#include "addtime.h"

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

    public:
        explicit Setting(QWidget *parent = nullptr);
        ~Setting();
        void init(QSqlDatabase database);

    protected:
        bool m_isPressed = false;
        QPoint m_startMovePos;
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);

    private slots:
            void on_close_clicked();
            void on_timeSave_clicked();
            void on_timeAdd_clicked();

    public slots:
            void deleteItem(QListWidgetItem *item);
            void addNewListWidgetItem(QString row);

    private:
            Ui::Setting *ui;
            AddTime *addtime_w;
            QSqlDatabase db;

            void addListWidgetItem(QString row);

    signals:
            void returnMain();
};

#endif // SETTING_H
