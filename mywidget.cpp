#include "mywidget.h"
#include <QPainter>
#include "mainwindow.h"

MyWidget::MyWidget(QWidget *parent, Qt::WindowFlags f) : QWidget(parent)
{

}


void MyWidget::paintEvent(QPaintEvent * e)
{
    int size = 50;
    int length=((MainWindow)(this->window())).length;
    int offset = 100;
    double length_of_hexagon_side = (size*sin(30*M_PI/180))/sin(120*M_PI/180);
    double move_up = sqrt(pow(length_of_hexagon_side,2)-pow(size/2,2));
    double vertical_side = size-2*move_up;
    double height_of_edge_bar = 50;

    double x_offset = size/2 + offset;
    double y_offset = length_of_hexagon_side/2+move_up + offset;
    static const QPointF top_edge[4] = {QPointF(x_offset,y_offset), QPointF(-height_of_edge_bar*tan(60*M_PI/180)+x_offset, -height_of_edge_bar+y_offset), QPointF((length-1)*size+height_of_edge_bar*tan(30*M_PI/180)+x_offset,-height_of_edge_bar+y_offset), QPointF((length-1)*size+x_offset,y_offset)};
    static const QPointF bottom_edge[4] = {QPointF(x_offset+(size/2)*(length-1),y_offset+(length-1)*(vertical_side+move_up)), QPointF(x_offset+(size/2)*(length-1)+(length-1)*size,y_offset+(length-1)*(vertical_side+move_up)), QPointF(x_offset+(size/2)*(length-1)+(length-1)*size+height_of_edge_bar*tan(60*M_PI/180),y_offset+(length-1)*(vertical_side+move_up)+height_of_edge_bar), QPointF(x_offset+(size/2)*(length-1)-height_of_edge_bar*tan(30*M_PI/180),y_offset+(length-1)*(vertical_side+move_up)+height_of_edge_bar)};

    static const QPointF left_edge[4] = {QPointF(x_offset,y_offset),QPointF(x_offset+(size/2)*(length-1),y_offset+(length-1)*(vertical_side+move_up)),QPointF(x_offset+(size/2)*(length-1)-height_of_edge_bar*tan(30*M_PI/180),y_offset+(length-1)*(vertical_side+move_up)+height_of_edge_bar),QPointF(-height_of_edge_bar*tan(60*M_PI/180)+x_offset, -height_of_edge_bar+y_offset)};
    static const QPointF right_edge[4] = {QPointF((length-1)*size+height_of_edge_bar*tan(30*M_PI/180)+x_offset,-height_of_edge_bar+y_offset), QPointF((length-1)*size+x_offset,y_offset),QPointF(x_offset+(size/2)*(length-1)+(length-1)*size,y_offset+(length-1)*(vertical_side+move_up)), QPointF(x_offset+(size/2)*(length-1)+(length-1)*size+height_of_edge_bar*tan(60*M_PI/180),y_offset+(length-1)*(vertical_side+move_up)+height_of_edge_bar)};


    QPainter painter(this);
    painter.setBrush(Qt::red);
    painter.setPen(Qt::red);
    painter.drawConvexPolygon(top_edge, 4);
    painter.drawConvexPolygon(bottom_edge,4);
    painter.setBrush(Qt::blue);
    painter.setPen(Qt::blue);
    painter.drawConvexPolygon(left_edge,4);
    painter.drawConvexPolygon(right_edge,4);
}
