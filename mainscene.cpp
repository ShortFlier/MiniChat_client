#include "mainscene.h"
#include "ui_mainscene.h"

MainScene::MainScene(ValidConnect* vc, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    this->vc=vc;

    //图标
    setWindowIcon(QIcon(":/img/app_icon.png"));
    setWindowTitle("MiniChat");

    ui->search->setIcon(QIcon(":/img/search.png"));

    vc->getUserInfo();


    //处理函数
    wd=new WebDistb(vc);
    wd->addHandler("userinfo",this);
}

MainScene::~MainScene()
{
    delete ui;
    vc->disconnect();
    delete vc;
}

void MainScene::handler(DataHead &head, DataResult &result)
{
    result.show();
    ui->name->setText(result.getstr("name"));
    ui->act->setText(result.getstr("account"));
}
