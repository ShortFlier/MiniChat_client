#ifndef REGISTWIDGET_H
#define REGISTWIDGET_H

#include "datahead.h"
#include "webdistb.h"

#include <QWidget>

namespace Ui {
class RegistWidget;
}

class RegistWidget : public QWidget, public Handler
{
    Q_OBJECT

public:
    explicit RegistWidget(QWidget *parent = nullptr);
    ~RegistWidget();
    void error(const QString& msg);
    void paintEvent(QPaintEvent*) override;


signals:
    //返回登入界面
    void swap();
    void submit(const QString& email);
    //请问注册确认界面
    void torgtcfm(const QString& email);

private slots:
    void on_back_clicked();

    void on_submit_clicked();

public slots:
    //接收信息处理
    void handler(DataHead& head, DataResult& result) override;

private:
    Ui::RegistWidget *ui;
    QString email;
};

#endif // REGISTWIDGET_H
