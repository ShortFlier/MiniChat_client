#ifndef INFORMATIONWIDGET_H
#define INFORMATIONWIDGET_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

namespace Ui {
class InformationWidget;
}

class InformationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InformationWidget(QWidget *parent = nullptr);
    ~InformationWidget();
    void sizeSet();
signals:
    void userchat(const QString& act, bool online, const QString& name);

private:
    Ui::InformationWidget *ui;
    QVBoxLayout* frd;
    QVBoxLayout* grp;
    QWidget* info;
    int infosize=0;
    //获取好友列表
    void frdinit();
    //获取群列表
    void grpinit();
    //获取消息
    void infoinit();
    void addinfo(QJsonObject&);
};
//好友显示类
class IFriend:public QWidget{
    Q_OBJECT
public:
    IFriend(const QJsonObject& jo, QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event) override;
signals:
    void chat(const QString& act, bool online, const QString& name);
private:
    QString act;
    QString name;
    bool online;
};
//消息显示类
class IInfo:public QWidget{
    Q_OBJECT
public:
    IInfo(QJsonObject& jo, QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event) override;
signals:
    void chat(const QString& act, bool online, const QString& name);
private:
    QString act;
    QString name;
    //false表示好友消息，true表示群消息
    bool group;
};

void img(QPushButton* img, const QString& act);
#endif // INFORMATIONWIDGET_H
