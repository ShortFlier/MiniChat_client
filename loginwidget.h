#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginWidget;
}
QT_END_NAMESPACE

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();
    void paintEvent(QPaintEvent*) override;

signals:
    void swap();
    void login(QString account, QString password);

private slots:
    void on_regist_clicked();

    void on_login_clicked();

private:
    Ui::LoginWidget *ui;

    void actErr(const QString&);
    void pwdErr(const QString&);
};
#endif // LOGINWIDGET_H
