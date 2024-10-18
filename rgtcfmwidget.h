#ifndef RGTCFMWIDGET_H
#define RGTCFMWIDGET_H

#include <QWidget>

namespace Ui {
class RgtCfmWidget;
}

class RgtCfmWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RgtCfmWidget(QWidget *parent = nullptr);
    ~RgtCfmWidget();
    void email(const QString& email);
    void paintEvent(QPaintEvent*)override;
    void error(const QString& msg);

signals:
    void back();
    void home();

private slots:
    void on_back_clicked();

    void on_home_clicked();

    void on_again_clicked();

    void on_submit_clicked();

private:
    Ui::RgtCfmWidget *ui;
};

#endif // RGTCFMWIDGET_H
