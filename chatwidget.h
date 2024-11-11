#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include "entity.h"

#include <QWidget>

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWidget(User& user,const bool& isfriend, const bool& online=false, QWidget *parent = nullptr);
    ~ChatWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ChatWidget *ui;
    User user;
    bool isfriend;
    bool online;

    void img(const QString& name);
    void info();
};

#endif // CHATWIDGET_H
