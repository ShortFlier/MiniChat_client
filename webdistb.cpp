#include "webdistb.h"

long WebDistb::id=20;

QMap<long, WebDistb::FUN> WebDistb::id_fun=QMap<long, WebDistb::FUN>();
QMap<long, WebDistb::BFUN> WebDistb::id_bfun=QMap<long, WebDistb::BFUN>();

WebDistb::WebDistb(WebSocketConnect *nt, QObject *parent)
{
    cnect=nt;
    connect(cnect->getSocket(), &QWebSocket::textMessageReceived, this, &WebDistb::textHandler);
    connect(cnect->getSocket(),&QWebSocket::binaryMessageReceived, this, &WebDistb::binaryHandler);
}

void WebDistb::addHandler(const QString &path, Handler *handler)
{
    path_handler.insert(path, handler);
}

Handler *WebDistb::getHandler(const QString &path)
{
    if(path_handler.contains(path)){
        return path_handler.value(path);
    }else
        return nullptr;
}

void WebDistb::asyncWeb(WebSocketConnect *wc, DataHead &head, DataResult &result, FUN fun)
{
    //设置通信id号
    QString _id=QString::number(id);
    head.setId(_id);
    //加入fun回调函数
    id_fun.insert(id, fun);

    wc->sendText(head, result);
    ++id;
}

void WebDistb::asyncBin(WebSocketConnect *wc, DataHead &head, QJsonDocument &json, QByteArray &data, BFUN fun)
{
    QString tid=QString::number(id);
    head.setId(tid);
    id_bfun.insert(id,fun);
    qDebug()<<"error";
    wc->sendBinary(head, json, data);
    ++id;
}

void WebDistb::textHandler(const QString &msg)
{
    QString data=msg;
    QTextStream ts(&data);
    QString h=ts.readLine();
    DataHead head(h);
    QString d=ts.readAll();
    DataResult result(d);
    redirect(head, result);
}

void WebDistb::binaryHandler(const QByteArray &data)
{
    //头部
    QByteArray h=data.mid(0,HLENGTH);
    int i=h.indexOf(DataHead::sepe.toUtf8());
    //请求路径
    QString path=h.left(i);
    qDebug()<<"path: "<<path;
    DataHead head(path);
    //状态码
    QByteArray c=h.mid(i+2);
    i=c.indexOf(DataHead::sepe.toUtf8());
    int code = (c.mid(0,i)).toInt();
    //数据部分
    QByteArray d=data.mid(HLENGTH);

    long id=(head._tpid)->toLong();
    if(id_bfun.contains(id)){
        BFUN fun=getBFUN(id);
        fun(code, d);
    }
}

WebDistb::FUN WebDistb::getFUN(const long &id)
{
    FUN fun=id_fun.value(id);
    id_fun.remove(id);
    return fun;
}

WebDistb::BFUN WebDistb::getBFUN(const long &id)
{
    BFUN fun=id_bfun.value(id);
    id_bfun.remove(id);
    return fun;
}

void WebDistb::redirect(DataHead &head, DataResult &result)
{
    if(result.code!=DataResult::code_success){
        ERROR
        return;
    }
    long id=(*head._tpid).toLong();
    if(id_fun.contains(id)){
        FUN fun=getFUN(id);
        fun(head, result);
        return;
    }
    Handler* hd=getHandler(*head._path);
    if(hd)
        hd->handler(head, result);
}
