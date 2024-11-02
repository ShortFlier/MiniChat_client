#include "entity.h"


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
