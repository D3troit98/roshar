#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QDebug>
#include <QSystemTrayIcon>
#include <QDialog>
#include <QMediaPlaylist>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QAction;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QPushButton;
class QSpinBox;
class QTextEdit;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void qmovie();
    void setVisible(bool visible) override;
    void showMessage(QString line);
    void musicPlaying(bool playing);


protected:
    void mousePressEvent(QMouseEvent *evt) override
    {
        oldPos = evt->globalPos();
    }

    void mouseMoveEvent(QMouseEvent *evt) override
    {
        const QPoint delta = evt->globalPos() -oldPos;
        move(x()+delta.x(),y()+delta.y());
        oldPos = evt->globalPos();
    }
    void closeEvent(QCloseEvent *event) override;
signals:
    void trayMessage(QString line);
private:
    QPoint oldPos;
public slots:
    void cosmere();
    void smallText();
    void mediumText();
    void largeText();

    void CourierFont();
    void CorbelFont();
    void CallunaFont();
    void EarthOrbiterFont();
    void FrightNightFont();

    void redColor();
    void blueColor();
    void whiteColor();


private slots:

    void on_settingBtn_clicked();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void messageClicked();
    void setIcon(QString line);

    //    void on_checkBox_stateChanged(int status);

    void on_checkBox_clicked(bool checked);

public:
    QString line;

private:
    Ui::MainWindow *ui;
    QSettings settings;/*(QCoreApplication::organizationName(),QCoreApplication::applicationName());*/
    QGraphicsScene *scene;

    void createActions();
    void createTrayIcon();

    QPushButton *showMessageButton;

    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QMediaPlaylist *playlist =  new QMediaPlaylist();
    QMediaPlayer *music = new QMediaPlayer(nullptr);



};
#endif // MAINWINDOW_H
