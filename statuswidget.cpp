#include "statuswidget.h"

#include <QPainter>

StatusWidget::StatusWidget(QWidget *parent)
    : QWidget{parent}
{
    //320 x 30
    setFixedSize(320, 30);
}

void StatusWidget::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    QPixmap pix(":/img/disonline.png");
    paint.drawPixmap(geometry(),pix);
}
