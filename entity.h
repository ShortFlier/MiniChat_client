#ifndef ENTITY_H
#define ENTITY_H

#include <QDateTime>
#include <QJsonObject>
#include <QString>


struct User
{
    int id;
    QString email;
    QString account;
    QString password;
    QString name;
    QDateTime create_time;
    QString imgPath;

    User(const QString& email, const QString account, const QString password, const QString name)
        :email(email),account(account),password(password),name(name)
    {
        create_time=QDateTime::currentDateTime();
    }
    User(){}
    User(const int& id, const QString& email, const QString account, const QString password, const QString name, const QDateTime& create_time)
        :id(id),email(email),account(account),password(password),name(name),create_time(create_time){}
    void enjson(const QJsonObject& jo);

    QJsonObject json();
};


#define INFO_TEXT 'a'
#define INFO_IMGE 'b'
struct Information{
    long id=0;
    QString sender;
    QString reciver;
    QDateTime time;
    char type;
    QString msg;

    Information(){}
    Information(const QString& sender, const QString& reciver, char type, const QString& msg=QString())
        :sender(sender), reciver(reciver), type(type), msg(msg){}
    static Information enjson(const QJsonObject& jo);
    QJsonObject json();
    //比较时间
    bool operator>(Information& info);
};

#endif // ENTITY_H
