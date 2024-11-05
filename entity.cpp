#include "entity.h"

#include <QFile>


void User::enjson(const QJsonObject &jo)
{
    id=jo.value("id").toInt();
    email=jo.value("email").toString();
    account=jo.value("account").toString();
    password=jo.value("password").toString();
    name=jo.value("name").toString();
    create_time=QDateTime::fromString(jo.value("create_time").toString(), "yyyy-MM-dd HH:mm:ss");
    imgPath=jo.value("imgPath").toString();
}

QJsonObject User::json()
{
    QJsonObject jo;
    jo.insert("id",id);
    jo.insert("email",email);
    jo.insert("account",account);
    jo.insert("password",password);
    jo.insert("name",name);
    jo.insert("create_time",create_time.toString("yyyy-MM-dd HH:mm:ss"));
    return jo;
}


