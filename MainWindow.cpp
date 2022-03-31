#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "ui_Dialog.h"
#include "Dialog.h"


#include <QIODevice>
#include <QDir>
#include <QFile>
#include <QString>
#include <QByteArray>
#include <QTextStream>
#include <QRandomGenerator>
#include <QTimer>
#include <QScreen>
#include <QIcon>
///////////////////
#include <QAction>
#include <QCheckBox>
#include <QComboBox>
#include <QCoreApplication>
#include <QCloseEvent>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QPushButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMessageBox>

#include <QMessageBox>

using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setStyleSheet("background:transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);

    ui->setupUi(this);
    move(screen()->geometry().center() -frameGeometry().center());
    // move(450,250);
    ui->textEdit->setWindowOpacity(1.0);
    ui->textEdit->setFrameShape(QFrame ::NoFrame);
    ui->textEdit->setFontWeight(50);
    ui->textEdit->setFontPointSize(32);
    ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit->setFontFamily("Corbel");
    ui->textEdit->setTextColor("White");
    if(settings.value("fontSize",1024).toInt()== 1)
    {
        ui->textEdit->setFontWeight(24);
        ui->textEdit->setFontPointSize(24);
    }else if(settings.value("fontSize",1024).toInt()== 2){
        ui->textEdit->setFontWeight(50);
        ui->textEdit->setFontPointSize(32);
    }else if(settings.value("fontSize",1024).toInt()== 3)
    {
        ui->textEdit->setFontWeight(70);
        ui->textEdit->setFontPointSize(40);
    }

    createActions();
    createTrayIcon();
    cosmere();
    /////////////////////////////////////////////////////////////////////////////////
    qmovie();

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(nullptr, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                      "on this system."));
        return ;
    }
    connect(trayIcon, &QSystemTrayIcon::messageClicked, this, &MainWindow::messageClicked);
    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::iconActivated);
    connect(ui->checkBox,&QAbstractButton::toggled,this,&MainWindow::musicPlaying);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::qmovie()
{
    // scene = new QGraphicsScene(this);
    // ui->graphicsView->setScene(scene);
    //    QMovie *mv = new QMovie("C:\\Users\\Acer\\Desktop\\App\\Roshar\\2305-settings-icon.gif");
    //    mv->start();
    //    ui->label_2->setAttribute(Qt::WA_NoSystemBackground);
    //    ui->label_2->setMovie(mv);
    // scene->addWidget(ui->label_2);
    ////////////////////////////////////////
    QMovie *mv = new QMovie("C:\\Users\\Acer\\Desktop\\App\\Roshar\\GIF-210827_134433.gif");
    //label gif
    ui->label_2->setMovie(mv);
    mv->setScaledSize(QSize(1000,1000));
    mv->start();

}


QByteArray getHeader(){
    QByteArray header;
    header.append("@!~!@");
    return header;
}
void MainWindow::cosmere()
{
    ui->textEdit->clear();
    QString path = QDir::currentPath()+QDir::separator()+"text.txt";
    QFile file(path);
    QByteArray header = getHeader();
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    qint64 value =  QRandomGenerator::global()->bounded(3500);
    qInfo() << value;
    in.seek(value);
    QByteArray buffer = file.peek(5);
    while (!in.atEnd() && !buffer.startsWith(header)) {
        file.seek(value++);
        buffer = file.peek(value);
        qInfo()<< "header not found at beggining " << " value: "<< value;
        //  return;
    }
    qInfo()<< "looking for header at file pos: " << file.pos() << " value: "<< value;
    //  buffer = file.peek(5);

    file.seek(value+4);
    for (int i=0;i<3 ;i++ ) {
        line = in.readLine();
        ui->textEdit->append(line);

        showMessage(line);
        emit trayMessage(line);


        qInfo() << value;

        qInfo() << line;

    }
    QTimer::singleShot(70000,this,&MainWindow::cosmere);
}

void MainWindow::smallText()
{
    qDebug() << "setting text to small";

    ui->textEdit->clear();
    ui->textEdit->setFontWeight(20);
    ui->textEdit->setFontPointSize(15);
    QTimer::singleShot(1000,this,&MainWindow::cosmere);

    qDebug() << " Done setting text to small";
    settings.setValue("fontSize",1);
}

void MainWindow::mediumText()
{
    qDebug() << "setting text to medium";
    ui->textEdit->clear();
    ui->textEdit->setFontWeight(50);
    ui->textEdit->setFontPointSize(32);
    QTimer::singleShot(1000,this,&MainWindow::cosmere);

    settings.setValue("fontSize",2);
}

void MainWindow::largeText()
{
    qDebug() << "setting text to large";
    ui->textEdit->clear();
    ui->textEdit->setFontWeight(70);
    ui->textEdit->setFontPointSize(40);
    QTimer::singleShot(1000,this,&MainWindow::cosmere);

    settings.setValue("fontSize",3);
}

void MainWindow::CourierFont()
{
    ui->textEdit->setFontFamily("Courier");
    QTimer::singleShot(1000,this,&MainWindow::cosmere);

    settings.setValue("fontText",1);
}

void MainWindow::CorbelFont()
{
    ui->textEdit->setFontFamily("Corbel");
    QTimer::singleShot(1000,this,&MainWindow::cosmere);
    settings.setValue("fontText",2);
}

void MainWindow::CallunaFont()
{
    ui->textEdit->setFontFamily("Calluna");
    QTimer::singleShot(1000,this,&MainWindow::cosmere);
    settings.setValue("fontText",3);

}

void MainWindow::EarthOrbiterFont()
{
    ui->textEdit->setFontFamily("Earth Orbiter");
    QTimer::singleShot(1000,this,&MainWindow::cosmere);
    settings.setValue("fontText",4);

}

void MainWindow::FrightNightFont()
{
    ui->textEdit->setFontFamily("Fright Night");
    QTimer::singleShot(1000,this,&MainWindow::cosmere);
    settings.setValue("fontText",5);
}

void MainWindow::redColor()
{
    ui->textEdit->setTextColor("red");
    QTimer::singleShot(1000,this,&MainWindow::cosmere);
    settings.setValue("fontColor",1);
}

void MainWindow::blueColor()
{
    ui->textEdit->setTextColor("blue");
    QTimer::singleShot(1000,this,&MainWindow::cosmere);
    settings.setValue("fontColor",2);
}

void MainWindow::whiteColor()
{
    ui->textEdit->setTextColor("white");
    QTimer::singleShot(1000,this,&MainWindow::cosmere);
    settings.setValue("fontColor",3);
}

void MainWindow::on_settingBtn_clicked()
{

    QString style = "border:4px solid; \n";
    style += " border-top-left-radius: 20px; \n";
    style += "border-top-right-radius: 20px;";
    ui->label_2->setStyleSheet(style);
    QPropertyAnimation *animation2 = new QPropertyAnimation(ui->settingBtn, "iconSize");
    animation2->setDuration(500);
    animation2->setStartValue(QSize(100,50));
    animation2->setEndValue(QSize(50,25));
    animation2->start();

    Dialog *dialog = new Dialog(this);
    QObject::connect(dialog,&Dialog::smallText,this,&MainWindow::smallText);
    QObject::connect(dialog,&Dialog::mediumText,this,&MainWindow::mediumText);
    QObject::connect(dialog,&Dialog::largeText,this,&MainWindow::largeText);

    QObject::connect(dialog,&Dialog::CourierFont,this,&MainWindow::CourierFont);
    QObject::connect(dialog,&Dialog::CorbelFont,this,&MainWindow::CorbelFont);
    QObject::connect(dialog,&Dialog::CallunaFont,this,&MainWindow::CallunaFont);
    QObject::connect(dialog,&Dialog::EarthOrbiterFont,this,&MainWindow::EarthOrbiterFont);
    QObject::connect(dialog,&Dialog::FrightNightFont,this,&MainWindow::FrightNightFont);

    QObject::connect(dialog,&Dialog::blueColor,this,&MainWindow::blueColor);
    QObject::connect(dialog,&Dialog::redColor,this,&MainWindow::redColor);
    QObject::connect(dialog,&Dialog::whiteColor,this,&MainWindow::whiteColor);

    dialog->show();
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        ui->reasonLabel->setText(line + " Hello");
        break;
    case QSystemTrayIcon::MiddleClick:
        showMessage(line);
        break;
    default:
        ;
    }

}

void MainWindow::setVisible(bool visible)
{
    minimizeAction->setEnabled(visible);
    maximizeAction->setEnabled(!isMaximized());
    restoreAction->setEnabled(isMaximized() || !visible);
    QMainWindow::setVisible(visible);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
#ifdef Q_OS_MACOS
    if (!event->spontaneous() || !isVisible()) {
        return;
    }
#endif
    if (trayIcon->isVisible()) {
        QMessageBox::information(this, tr("Systray"),
                                 tr("The program will keep running in the "
                                    "system tray. To terminate the program, "
                                    "choose <b>Quit</b> in the context menu "
                                    "of the system tray entry."));
        hide();
        event->ignore();
    }
}

void MainWindow::setIcon(QString line)
{
    qInfo() << line;
}

void MainWindow::showMessage(QString line)
{

    qInfo() << "message: " << line;
    QString filename = ":/myresources/icon-img.gif";
    QIcon icon = QIcon(filename);
    qInfo() << filename;
    trayIcon->setIcon(icon);

    setWindowIcon(icon);
    //    trayIcon->setToolTip(iconComboBox->itemText(index));
    trayIcon->setVisible(true);
    trayIcon->setToolTip("Journey before Destination");
    // QSystemTrayIcon::MessageIcon msgIcon = QSystemTrayIcon::MessageIcon(0);
    trayIcon->showMessage("Roshar",line,icon,10000);

}

void MainWindow::messageClicked()
{
    QMessageBox::information(nullptr, tr("Systray"),
                             tr("Sorry, I already gave what help I could.\n"
                                "Maybe you should try asking a human?"));
}

void MainWindow::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, &QAction::triggered, this, &QWidget::hide);

    maximizeAction = new QAction(tr("Ma&ximize"), this);
    connect(maximizeAction, &QAction::triggered, this, &QWidget::showMaximized);

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, &QAction::triggered, this, &QWidget::showNormal);

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}


void MainWindow::on_checkBox_clicked(bool checked)
{

    playlist->addMedia(QUrl("qrc:/myresources/Lithium.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

  //  music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->setVolume(50);

    if(checked) {
        music->play();
    }
else{
    qInfo() << "Stopping music from else";
    music->stop();

    }
     qInfo() << "the end of music from else";
}

void MainWindow::musicPlaying(bool playing)
{
   playing =  ui->checkBox->checkState();
    qInfo() << "playing" << playing;
}

