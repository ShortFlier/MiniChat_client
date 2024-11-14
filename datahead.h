#ifndef DATAHEAD_H
#define DATAHEAD_H

#include <QObject>
#include <qjsondocument.h>
#include <QJsonObject>
#include <QMessageBox>

#define ERROR QMessageBox::critical(nullptr, "错误", result.jsdata.object().value("msg").toString());
#define DEFAULT_ID QString::number(DataHead::default_id)

class DataHead : public QObject
{
    static const int default_id;
    Q_OBJECT
public:
    explicit DataHead(QString str, QObject *parent = nullptr);
    DataHead operator=(const DataHead&)=delete;
    DataHead(const DataHead&)=delete;
    ~DataHead();
    int show();
    DataHead(const QString& _tp_type,const QString& _http_type,const QString& _path,const QString& _tpid);
    QString getUrl() const;
    static QString getUrl(const QString& _tp_type,const QString& _http_type,const QString& _path,const QString& _tpid);
    void setId(const QString& id);
    static DataHead dataHead(const QString& path){return DataHead(DataHead::http, DataHead::request, path, QString::number(11));}
    static DataHead wsHead(const QString& path){return DataHead(DataHead::websocket, "none", path, "11");}

public:
    enum tp_type{ws, htp};
    static const QString websocket;
    static const QString http;

    enum http_type{rqe, rsp};
    static const QString request;
    static const QString response;

    static const QString seph;
    static const QString sep;
    static const QString sepe;

signals:


public:
    QString* _tp_type=nullptr;
    QString* _http_type=nullptr;
    QString* _tpid=nullptr;
    QString* _path=nullptr;
};

class DataResult{
public:
    DataResult(){}
    DataResult(const int& code, const QJsonDocument& jsdata):code(code),jsdata(jsdata){}
    DataResult(const QString& datastr);
    //合并code和jsdata,转成格式可以发送的数据部分
    QString data() const;
    QString getstr(const QString& str)const { return jsdata.object().value(str).toString();}
    void show()const{ qDebug()<<"code:"<<code<<jsdata.object();}
    static DataResult error(const QString& msg);
    static DataResult success(const QString& msg);

public:
    enum code_result{code_success=200, code_error=400};
public:
    int code=0;
    QJsonDocument jsdata;

};

#endif // DATAHEAD_H
