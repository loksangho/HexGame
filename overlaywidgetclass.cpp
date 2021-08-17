#include "overlaywidgetclass.h"



void OverlayWidget::newParent() {
  if (!parent()) return;
  parent()->installEventFilter(this);
  raise();
}

OverlayWidget::OverlayWidget(QWidget *parent) : QWidget(parent) {
  setAttribute(Qt::WA_NoSystemBackground);
  setAttribute(Qt::WA_TransparentForMouseEvents);
  newParent();
}

//! Catches resize and child events from the parent widget
bool OverlayWidget::eventFilter(QObject *obj, QEvent *ev) {
  if (obj == parent()) {
     if (ev->type() == QEvent::Resize)
        resize(static_cast<QResizeEvent*>(ev)->size());
     else if (ev->type() == QEvent::ChildAdded)
        raise();
  }
  return QWidget::eventFilter(obj, ev);
}

//! Tracks parent widget changes
bool OverlayWidget::event(QEvent *ev) {
    if (ev->type() == QEvent::ParentAboutToChange) {
     if (parent()) parent()->removeEventFilter(this);
    }
    else if (ev->type() == QEvent::ParentChange)
        newParent();
    return QWidget::event(ev);
}



ContainerWidget::ContainerWidget(QWidget *parent) : QWidget(parent) {}
void ContainerWidget::setSize(QObject *obj) {
    if (obj->isWidgetType()) static_cast<QWidget*>(obj)->setGeometry(rect());
}

//! Resizes children to fill the extent of this widget
bool ContainerWidget::event(QEvent *ev)  {
    if (ev->type() == QEvent::ChildAdded) {
        setSize(static_cast<QChildEvent*>(ev)->child());
    }
return QWidget::event(ev);
}
//! Keeps the children appropriately sized
void ContainerWidget::resizeEvent(QResizeEvent *)  {
    for(auto obj : children()) setSize(obj);
}



CrossHairOverlay::CrossHairOverlay(QWidget *parent) : OverlayWidget{parent} {
    setAttribute(Qt::WA_TranslucentBackground);
}

void CrossHairOverlay::paintEvent(QPaintEvent *) {
    QPainter p{this};
    p.fillRect(rect(), {100, 100, 100, 128});
    p.setPen({200, 200, 255});
    p.setFont({"arial,helvetica", 48});
    p.drawText(rect(), "Loading...", Qt::AlignHCenter | Qt::AlignTop);
}

