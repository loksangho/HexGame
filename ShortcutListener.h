#ifndef SHORTCUTLISTENER_H
#define SHORTCUTLISTENER_H

#include <QtGui>
#include <QtQml>


class ShortcutListener : public QObject
{
    Q_OBJECT

public:
    ShortcutListener(QObject *parent = nullptr) :
        QObject(parent)
    {
    }

    Q_INVOKABLE void listenTo(QObject *object)
    {
        if (!object)
            return;

        object->installEventFilter(this);
    }

    bool eventFilter(QObject *object, QEvent *event) override
    {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            qDebug() << "key" << keyEvent->key() << "pressed on" << object;
            return true;
        }
        return false;
    }
};

static QObject *shortcutListenerInstance(QQmlEngine *, QJSEngine *engine)
{
    return new ShortcutListener(engine);
}

#endif // SHORTCUTLISTENER_H
