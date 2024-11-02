#ifndef PERSONAL_H
#define PERSONAL_H

#include "entity.h"

#include <QWidget>

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

private:
    Ui::Personal *ui;
};

#endif // PERSONAL_H
