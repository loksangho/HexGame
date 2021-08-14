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

#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
    //ui->quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
#endif

    int colour = 0;
    bool colour_checked = true;
    int difficulty = 0;
    bool difficulty_checked = true;

    CustomDialog d("This will start a new game. Please choose your colour", this);                            // We want our custom dialog called "Registration".
    d.addLabel    ("Please choose your colour below (Blue starts first) ...");           // The first element is just a text label (non interactive).
    d.addRadioGrp ("Colour: ", "Blue|Red", &colour, "Blue starts first, Red starts second", "Blue colour|Red colour", false, &colour_checked);
    d.addLabel    ("Please choose your difficulty (Easy is fastest) ...");           // The first element is just a text label (non interactive).
    d.addRadioGrp ("Difficulty: ", "Easy|Intermediate|Hard", &difficulty, "Based on Monte Carlo AI method", "MC trials=50|MC trials=200|MC trials=1000", false, &difficulty_checked);
    d.exec();                             // Execution stops here until user closes dialog



    if(d.wasCancelled()){                // If the user hit cancel, your values stay the same
        main_window->setVisible(true);
        this->hide();
    }                                 // and you probably don't need to do anything
    else {
        if(colour != -1) {
            //qmlRegisterSingletonType<Squircle>("OpenGLUnderQML", 1, 0, "Squircle",Squircle::squircleInstance);
            //Squircle testObj;
            qmlRegisterType<Squircle>("OpenGLUnderQML", 1, 0, "Squircle");

#if defined(Q_OS_MAC) || defined(Q_OS_LINUX)
            //ui->quickWidget->engine()->rootContext()->setContextProperty("test", &testObj);
            //ui->quickWidget->setSource(QUrl("qrc:///scenegraph/openglunderqml/main.qml"));
            //Squircle* squircle = ui->quickWidget->rootObject()->findChild<Squircle *>("squircle");
            //squircle->init(11, colour==0?Colour::BLUE:Colour::RED, difficulty);


            QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGLRhi);

#elif defined(Q_OS_WIN)
            //qmlRegisterType<Squircle>("OpenGLUnderQML", 1, 0, "Squircle");
            QQuickWindow::setGraphicsApi(QSGRendererInterface::Direct3D11Rhi);

#endif
            QQuickView* view = new QQuickView();
            QWidget* container = QWidget::createWindowContainer(view, this);
            container->setFocusPolicy(Qt::TabFocus);

            view->setResizeMode(QQuickView::SizeRootObjectToView);
            view->setSource(QUrl("qrc:///scenegraph/openglunderqml/main.qml"));
            Squircle* squircle = view->rootObject()->findChild<Squircle *>("squircle");
            squircle->init(11, colour==0?Colour::BLUE:Colour::RED, difficulty);
            ui->verticalLayout->addWidget(container);
            //QQmlApplicationEngine engine;
            //engine.load(QUrl(QStringLiteral("qrc:///scenegraph/openglunderqml/main.qml")));;
        }
    }


}



BoardView3D::~BoardView3D()
{
    delete ui;

}

void BoardView3D::on_pushButton_clicked()
{
    std::cout << "here" << std::endl;
    main_window->setVisible(true);
    this->hide();
}

