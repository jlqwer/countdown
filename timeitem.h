#ifndef TIMEITEM_H
#define TIMEITEM_H

#include <QListWidgetItem>
#include <QWidget>

namespace Ui {
class TimeItem;
}

class TimeItem : public QWidget
{
    Q_OBJECT

    public:
        explicit TimeItem(QWidget *parent = nullptr);
        ~TimeItem();
        void init(QListWidgetItem *item, QString text);

    private:
        QListWidgetItem *item;

    private slots:
        void on_del_clicked();

    signals:
        void deleteItem(QListWidgetItem *item);

private:
    Ui::TimeItem *ui;
};

#endif // TIMEITEM_H
