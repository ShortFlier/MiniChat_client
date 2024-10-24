#ifndef REGISTWIDGET_H
#define REGISTWIDGET_H

#include <QWidget>

namespace Ui {
class RegistWidget;
}

class RegistWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RegistWidget(QWidget *parent = nullptr);
    ~RegistWidget();
    void error(const QString& msg);
    void paintEvent(QPaintEvent*) override;


signals:
    void swap();
    void submit(const QString& email, unsigned int id);

private slots:
    void on_back_clicked();

    void on_submit_clicked();

private:
    Ui::RegistWidget *ui;
};

#endif // REGISTWIDGET_H
