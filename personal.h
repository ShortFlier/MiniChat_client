#ifndef PERSONAL_H
#define PERSONAL_H

#include "entity.h"

#include <QWidget>

#define SELF 1
#define FRIEND 2
#define STRANGER 3

namespace Ui {
class Personal;
}

//个人信息展示界面
class Personal : public QWidget
{
    Q_OBJECT

public:
    explicit Personal(User user, int self,  QWidget *parent = nullptr);
    ~Personal();
    void disSelf(User user);
    //头像图片显示
    void img(const QString& name);

private slots:
    void on_change_clicked();

    void on_img_clicked();

signals:
    void rename(QString name);
    void reimg(QString name);

private:
    Ui::Personal *ui;
    bool avb=false;
    QString name;
};

#endif // PERSONAL_H
