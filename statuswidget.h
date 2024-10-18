#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H

#include <QWidget>

class StatusWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StatusWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);

signals:
};

#endif // STATUSWIDGET_H
