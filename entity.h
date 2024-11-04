#ifndef ENTITY_H
#define ENTITY_H

#include <QDateTime>
#include <QJsonObject>
#include <QString>

#define DEFAULT_IMAGE ":/img/camera.png"
#define HEADSHOT_PATH "./assets/headshot/"


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

//参数为图片名，返回图像的路径，如果没有，返回默认图像
QString getImage(const QString& path);

#endif // ENTITY_H
