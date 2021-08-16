#include "boardview3d.h"
#include "ui_boardview3d.h"
#include <QtQuick>
#include "keyreceiver.h"
#include "squircle.h"
#include "customdialog.h"
#include <QtQuick/QQuickView>


BoardView3D::BoardView3D(QMainWindow* main_window, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoardView3D),
    main_window(main_window)
{
    ui->setupUi(this);
}


// Sets the Graphics API according to platform, then creates a QQuickView object that is the 3D mode of the game
void BoardView3D::init(int board_length, int colour, int difficulty) {
    qmlRegisterType<Squircle>("OpenGLUnderQML", 1, 0, "Squircle");

#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)



    QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGLRhi);

#elif defined(Q_OS_WIN)
    QQuickWindow::setGraphicsApi(QSGRendererInterface::Direct3D11Rhi);
#endif
    QQuickView* view = new QQuickView();
    QWidget* container = QWidget::createWindowContainer(view, this);
    container->setFocusPolicy(Qt::ClickFocus);

    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->setSource(QUrl("qrc:///scenegraph/openglunderqml/main.qml"));
    squircle = view->rootObject()->findChild<Squircle *>("squircle");
    squircle->init(board_length, colour==0?Colour::BLUE:Colour::RED, difficulty);
    ui->verticalLayout->addWidget(container);

}


BoardView3D::~BoardView3D()
{
    delete ui;
    delete squircle;
}

// When the '2D Mode' button is clicked, it hides current window and goes back to the main window.
void BoardView3D::on_pushButton_clicked()
{
    main_window->setVisible(true);
    this->hide();
}


void BoardView3D::on_mouseSensitivitySlider_valueChanged(int value)
{
    squircle->changeMouseSensitivity(value);
}


void BoardView3D::on_moveSpeedSlider_valueChanged(int value)
{
    squircle->changeMoveSpeed(value);
}

