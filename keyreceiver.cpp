#include "keyreceiver.h"
#include <QKeyEvent>
#include <QObject>
#include <iostream>

bool KeyReceiver::eventFilter(QObject* obj, QEvent* event)
{
    std::cout << "event filter" << std::endl;

    if (event->type()==QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if ( (key->key()==Qt::Key_Enter) || (key->key()==Qt::Key_Return) ) {
            //Enter or return was pressed
            std::cout << "received enter key" << std::endl;
        }
        else if(key->key() == Qt::Key_W) {
            std::cout << "received w key" << std::endl;

            emit w_key();

            //return true;
        }
        else if(key->key() == Qt::Key_A) {
            emit a_key();
            //return true;
        }
        else if(key->key() == Qt::Key_S) {
            emit s_key();
            //return true;
        }
        else if(key->key() == Qt::Key_D) {
            emit d_key();
            //return true;
        }
        else{
            return QObject::eventFilter(obj, event);
        }
        return true;
    } else if(event->type()==QEvent::KeyRelease) {
        emit key_release();
        return true;

    }
    else {
        return QObject::eventFilter(obj, event);
    }
    return false;
}
