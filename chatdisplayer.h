#ifndef CHATDISPLAYER_H
#define CHATDISPLAYER_H

#include "entity.h"

#include <QWidget>

namespace Ui {
class ChatDisplayer;
}

class ChatDisplayer : public QWidget
{
    Q_OBJECT

public:
    explicit ChatDisplayer(Information& info, QWidget *parent = nullptr);
    ~ChatDisplayer();
    void img(const QString& sender);
    void content(Information& info);
private:
    Ui::ChatDisplayer *ui;
};

#endif // CHATDISPLAYER_H
