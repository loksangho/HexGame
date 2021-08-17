#ifndef OVERLAYWIDGETCLASS_H
#define OVERLAYWIDGETCLASS_H

/* This overlay class does not work because of a known limitation whereby the graphics window is always on top of the stack. May work later in the future.
 *
 * */

#include <QtGui>
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
#include <QtWidgets>
#endif

class OverlayWidget : public QWidget {
   void newParent();
public:
   explicit OverlayWidget(QWidget *parent = {});
protected:
   //! Catches resize and child events from the parent widget
   bool eventFilter(QObject *obj, QEvent *ev) override;

   //! Tracks parent widget changes
   bool event(QEvent *ev) override;
};

class ContainerWidget : public QWidget
{
public:
   explicit ContainerWidget(QWidget *parent = {});
   void setSize(QObject *obj) ;
protected:
   //! Resizes children to fill the extent of this widget
   bool event(QEvent *ev) override;
   //! Keeps the children appropriately sized
   void resizeEvent(QResizeEvent *) override;
};

class CrossHairOverlay : public OverlayWidget
{
public:
   CrossHairOverlay(QWidget *parent = {});
protected:
   void paintEvent(QPaintEvent *) override;
};


#endif // OVERLAYWIDGETCLASS_H
