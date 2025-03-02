#ifndef SENDFRAME_H
#define SENDFRAME_H
#include <qstring.h>
#include <QVector>


class SendFrame
{

public:


    SendFrame();
    void config_buffer ();
    QString frame;
    char char_array[30];
};

#endif // SENDFRAME_H
