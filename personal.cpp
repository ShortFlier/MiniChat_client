#include "personal.h"
#include "ui_personal.h"


Personal::Personal(User user, int self, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Personal)
{
    ui->setupUi(this);
}

Personal::~Personal()
{
    delete ui;
}
