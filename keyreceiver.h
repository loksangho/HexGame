#ifndef KEYRECEIVER_H
#define KEYRECEIVER_H

/*
 *  This is a key receiver class that handles key press events. Not really used.
 *
 */

#include <QObject>

class KeyReceiver : public QObject
{
    Q_OBJECT
public:
    bool eventFilter(QObject* obj, QEvent* event);

signals:
    void w_key();
    void a_key();
    void s_key();
    void d_key();
    void key_release();
};

#endif // KEYRECEIVER_H
