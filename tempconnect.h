#ifndef TEMPCONNECT_H
#define TEMPCONNECT_H

#include "websocketconnect.h"

class TempConnect : public WebSocketConnect
{
public:
    explicit TempConnect(QObject *parent = nullptr);
    ~TempConnect();
};

#endif // TEMPCONNECT_H
