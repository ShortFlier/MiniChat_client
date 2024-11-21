#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include "entity.h"

#include <QJsonArray>
#include <QVBoxLayout>
#include <QWidget>

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWidget(User& user,const bool& isfriend,const QString& rname=QString(), const bool& online=false, QWidget *parent = nullptr);
    ~ChatWidget();

    void reciver(const QString& act, QJsonArray& data);

    int h=0;

private slots:
    void on_pushButton_clicked();

    void on_textEdit_textChanged();

    void on_send_clicked();

private:
    Ui::ChatWidget *ui;
    User user;
    bool isfriend;
    bool online;

    QLayout * layout;

    void img(const QString& name);
    void info();
    void dismsg(Information& info);
    void historymsg();
};

#endif // CHATWIDGET_H
