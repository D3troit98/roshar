#include "Dialog.h"
#include "ui_Dialog.h"
#include "MainWindow.h"
#include <QDebug>

const int MIN_VALUE = 0;
const int MAX_VALUE = 255;
const unsigned STEPS = 13;


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    this->setWindowOpacity(0.99);
    this->setAttribute(Qt::WA_TranslucentBackground,false);
    this->setStyleSheet("background-color: blue;");

    ui->setupUi(this);
    qInfo() <<"Dialog Opened";
    createActions();
    createMenus();
    changeBackgroundColor();
    //createToolButtons();
    // createToolbars();
    ///////////////?GEOMETRY MENU///////////////////////////
    ui->toolButton_4->setPopupMode(QToolButton::MenuButtonPopup);
    ui->toolButton_4->setMenu(geometryMenu);
    QObject::connect(ui->toolButton_4,SIGNAL(triggered(QAction*)),ui->toolButton_4,SLOT(setDefaultAction(QAction*)));
    /////////////////////FONT SIZE/////////////////////////////////////////////
    ui->toolButton_2->setPopupMode(QToolButton::MenuButtonPopup);
    fontSizeActions.append(smallAction);
    fontSizeActions.append(MediumAction);
    fontSizeActions.append(largeAction);
    ui->toolButton_2->addActions(fontSizeActions);
    QObject::connect(ui->toolButton_2,SIGNAL(triggered(QAction*)),ui->toolButton_2,SLOT(setDefaultAction(QAction*)));

    /////////////////FONT STYLE//////////////////////
    ui->toolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fontTextActions.append(CallunaAction);
    fontTextActions.append(CorbelAction);
    fontTextActions.append(CourierAction);
     fontTextActions.append(EarthOrbiterAction);
     fontTextActions.append(FrightNightAction);

    ui->toolButton->addActions(fontTextActions);
    //ui->toolButton->setMenu.(fontMenu);
    QObject::connect(ui->toolButton,SIGNAL(triggered(QAction*)),ui->toolButton,SLOT(setDefaultAction(QAction*)));

    //////////////////FONT COLOR
    ui->toolButton_3->setPopupMode(QToolButton::MenuButtonPopup);
    fontColorActions.append(redAction);
    fontColorActions.append(blueAction);
    fontColorActions.append(whiteAction);
    ui->toolButton_3->addActions(fontColorActions);
    QObject::connect(ui->toolButton_3,SIGNAL(triggered(QAction*)),ui->toolButton_3,SLOT(setDefaultAction(QAction*)));

}

void Dialog::changeBackgroundColor()
{
    ui->horizontalSlider->setMaximum(MAX_VALUE * STEPS);
    ui->horizontalSlider->setMinimum(MIN_VALUE);
    ui->horizontalSlider_2->setMaximum(MAX_VALUE * STEPS);
    ui->horizontalSlider_2->setMinimum(MIN_VALUE);
    ui->horizontalSlider_3->setMaximum(MAX_VALUE * STEPS);
    ui->horizontalSlider_3->setMinimum(MIN_VALUE);
    int bg_r = ui->horizontalSlider->value();
    int bg_g = ui->horizontalSlider_2->value();
    int bg_b = ui->horizontalSlider_3->value();

    ui->R_label->setText(QString::number(bg_r));
    ui->G_label->setText(QString::number(bg_g));
    ui->B_label->setText(QString::number(bg_b));

    //QString styleSheet = "QDialog { background-color : rgb(%1, %2, %3)}"; // normal color
    QString styleSheet =  "QDialog {qlineargradient(spread:pad, x1:0, y1:0, x2:0 , y2:0.568,stop:0 rgba(%1, %2, %3, 255)) }";

    this->setStyleSheet(styleSheet.arg(bg_r).arg(bg_g).arg(bg_b));



}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::Courier()
{
    qDebug() << "Courier font!";
    emit CourierFont();
}

void Dialog::Corbel()
{
    qDebug() << "Corbel font!";
    emit CorbelFont();
}

void Dialog::Calluna()
{
    qDebug() << "Calluna font!";
    emit CallunaFont();
}

void Dialog::FrightNight()
{
    qDebug() << "Fright Night font!";
    emit FrightNightFont();
}

void Dialog::EarthOrbiter()
{
    qDebug() << "Orbiter font!";
    emit EarthOrbiterFont();
}

void Dialog::center()
{
    qDebug() << "Move to Center!";
}

void Dialog::top()
{
    qDebug() << "Move to top!";
}

void Dialog::buttom()
{
    qDebug() << "Move to buttom!";
}

void Dialog::smallFont()
{
    qInfo() << "emiting smallText";
    /*
    ui->textEdit->setFontWeight(50);
    ui->textEdit->setFontPointSize(32);*/
    emit smallText();



}

void Dialog::mediumFont()
{
    emit mediumText();
//   qInfo() << settings.value("testx").toString();
//    qInfo() << settings.value("test").toInt();

}

void Dialog::largeFont()
{
    emit largeText();
}


void Dialog::red()
{
    emit redColor();
}

void Dialog::blue()
{
    emit blueColor();
}

void Dialog::white()
{
    emit whiteColor();
}

void Dialog::updateTextOnSliderChange(int position)
{
    float positionF = position / float(STEPS);
    ui->R_label->setText(QString::number(positionF, 'f', 2));
}
void Dialog::updateTextOnSliderChange2(int position)
{
    float positionF = position / float(STEPS);
    ui->G_label->setText(QString::number(positionF, 'f', 2));
}

void Dialog::updateTextOnSliderChange3(int position)
{
    float positionF = position / float(STEPS);
    ui->B_label->setText(QString::number(positionF, 'f', 2));
}



void Dialog::createActions()
{
    CorbelAction = new QAction("set text to CorbelAction",this);
    CallunaAction = new QAction("set text to CallunaAction",this);
    CourierAction = new QAction("set text to Courier",this);
    EarthOrbiterAction = new QAction("set text to Earth Orbiter",this);
    FrightNightAction = new QAction("set text to Fright Night",this);

    topAction = new QAction("move it to the top",this);
    buttomAction = new QAction("move it to the bottom",this);
    centerAction = new QAction("move it to the center",this);

    smallAction = new QAction("make it small",this);
    MediumAction = new QAction("make it medium",this);
    largeAction = new QAction("make it very large",this);

    redAction = new QAction("make it red",this);
    whiteAction = new QAction("make it white",this);
    blueAction = new QAction("make it blue",this);


    CorbelAction->setIcon(QIcon(":/myresources/icons8_font_size_1.ico"));
    CourierAction->setIcon(QIcon(":/myresources/icons8_font_size_2.ico"));
    CallunaAction->setIcon(QIcon(":/myresources/icons8_font_style_formatting_3.ico"));
    EarthOrbiterAction->setIcon(QIcon(":/myresources/icons8_typography.ico"));
    FrightNightAction->setIcon(QIcon(":/myresources/icons8_ttf.ico"));

    topAction->setIcon(QIcon(":/myresources/icons8_top_docking.ico"));
    buttomAction->setIcon(QIcon(":/myresources/icons8_bottom_docking.ico"));
    centerAction->setIcon(QIcon(":/myresources/icons8_center_of_gravity.ico"));

    redAction->setIcon(QIcon(":/myresources/icons8_lowercase_2_2.ico"));
    whiteAction->setIcon(QIcon(":/myresources/icons8_lowercase_2_1.ico"));
    blueAction->setIcon(QIcon(":/myresources/icons8_lowercase_2_3.ico"));

    QObject::connect(CorbelAction,SIGNAL(triggered()),
                     this,SLOT(Corbel()));
    QObject::connect(CallunaAction,SIGNAL(triggered()),
                     this,SLOT(Calluna()));
    QObject::connect(CourierAction,SIGNAL(triggered()),
                     this,SLOT(Courier()));
    QObject::connect(EarthOrbiterAction,SIGNAL(triggered()),
                     this,SLOT(EarthOrbiterFont()));
    QObject::connect(FrightNightAction,SIGNAL(triggered()),
                     this,SLOT(FrightNight()));


    QObject::connect(topAction,SIGNAL(triggered()),
                     this,SLOT(top()));
    QObject::connect(buttomAction,SIGNAL(triggered()),
                     this,SLOT(buttom()));
    QObject::connect(centerAction,SIGNAL(triggered()),
                     this,SLOT(center()));

    QObject::connect(smallAction,SIGNAL(triggered()),
                     this,SLOT(smallFont()));
    QObject::connect(MediumAction,SIGNAL(triggered()),
                     this,SLOT(mediumFont()));
    QObject::connect(largeAction,SIGNAL(triggered()),
                     this,SLOT(largeFont()));

    QObject::connect(redAction,SIGNAL(triggered()),
                     this,SLOT(red()));
    QObject::connect(blueAction,SIGNAL(triggered()),
                     this,SLOT(blue()));
    QObject::connect(whiteAction,SIGNAL(triggered()),
                     this,SLOT(white()));

    QObject::connect(ui->horizontalSlider,SIGNAL(valueChanged(int)),
                     this,SLOT(updateTextOnSliderChange(int)));
    QObject::connect(ui->horizontalSlider_2,SIGNAL(valueChanged(int)),
                     this,SLOT(updateTextOnSliderChange2(int)));
    QObject::connect(ui->horizontalSlider_3,SIGNAL(valueChanged(int)),
                     this,SLOT(updateTextOnSliderChange3(int)));



}

void Dialog::createMenus()
{
    geometryMenu = new QMenu;
    geometryMenu->addAction(topAction);
    geometryMenu->addAction(buttomAction);
    geometryMenu->addAction(centerAction);


}



void Dialog::on_dontBtn_clicked()
{
    this->close();
}
