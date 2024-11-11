#include "informationwidget.h"
#include "ui_informationwidget.h"

InformationWidget::InformationWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InformationWidget)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);

    setFixedWidth(320);
}

InformationWidget::~InformationWidget()
{
    delete ui;
}

void InformationWidget::sizeSet()
{
    int w=ui->infosr->width();
    int h=ui->tabWidget->height()-30;
    ui->infosr->resize(w,h);
    ui->friendssr->resize(w,h);
    ui->groupsr->resize(w,h);
}
