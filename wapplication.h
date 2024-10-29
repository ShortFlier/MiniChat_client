#ifndef WAPPLICATION_H
#define WAPPLICATION_H

#include "loginscene.h"

#include <QObject>

 //页面调度类
class WApplication : public QObject
{
    Q_OBJECT
private:
    explicit WApplication(QObject *parent = nullptr);
    ~WApplication();
public:
    static WApplication* getInstance();

signals:

private:
    LoginScene* loginScene=nullptr;
};

#endif // WAPPLICATION_H
