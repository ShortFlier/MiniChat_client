#ifndef NOTIFYWIDGET_H
#define NOTIFYWIDGET_H

#include "validconnect.h"
#include "webdistb.h"

#include <QWidget>

namespace Ui {
class NotifyWidget;
}

class NotifyWidget : public QWidget, public Handler
{
    Q_OBJECT

public:
    explicit NotifyWidget(const QString& act, ValidConnect* vc, QWidget *parent = nullptr);
    ~NotifyWidget();

    void handler(DataHead& head, DataResult& result) override;

private:
    Ui::NotifyWidget *ui;
};

class Friend:public QWidget{
    Q_OBJECT
public:
    explicit Friend(QJsonObject& jo);
signals:
    void del(Friend*, int s);
private:
    unsigned int id;
    void img(QPushButton* img,const QString& iname);
    void access(QJsonObject& jo, bool status);
};

#endif // NOTIFYWIDGET_H
