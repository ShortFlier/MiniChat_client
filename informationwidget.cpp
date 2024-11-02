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
