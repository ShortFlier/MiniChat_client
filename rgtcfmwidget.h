#ifndef RGTCFMWIDGET_H
#define RGTCFMWIDGET_H

#include "webdistb.h"

#include <QWidget>

namespace Ui {
class RgtCfmWidget;
}

class RgtCfmWidget : public QWidget, public Handler
{
    Q_OBJECT

public:
    explicit RgtCfmWidget(QWidget *parent = nullptr);
    ~RgtCfmWidget();
    void email(const QString& email);
    void paintEvent(QPaintEvent*)override;
    void error(const QString& msg);

    void handler(DataHead& head, DataResult& result) override;

signals:
    void back();
    void home();
    //重新发送验证码
    void again_code(QString email);
    //注册提交
    void submit(QString email, QString code);

private slots:
    void on_back_clicked();

    void on_home_clicked();

    void on_again_clicked();

    void on_submit_clicked();

private:
    Ui::RgtCfmWidget *ui;
    QString _email;
};

#endif // RGTCFMWIDGET_H
