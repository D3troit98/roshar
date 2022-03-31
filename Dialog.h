#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QToolButton>
#include <QList>
#include <QSettings>
#include <QCoreApplication>
//#include "main.cpp"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    void changeBackgroundColor();
    ~Dialog();
signals:
    void smallText();
    void  mediumText();
    void largeText();

    void CourierFont();
    void CorbelFont();
    void CallunaFont();
    void EarthOrbiterFont();
    void FrightNightFont();

    void redColor();
    void blueColor();
    void whiteColor();


public slots:
    void Courier();
    void Corbel();
    void Calluna();
    void EarthOrbiter();
    void FrightNight();

    void center();
    void top();
    void buttom();

    void smallFont();
    void mediumFont();
    void largeFont();

    void red();
    void blue();
    void white();
    void updateTextOnSliderChange(int position);
    void updateTextOnSliderChange2(int position);
    void updateTextOnSliderChange3(int position);

private:
    void createActions();
    void createMenus();
    //    void createToolbars();
    //    void createToolButtons();
public :

private slots:

    void on_dontBtn_clicked();

private:
    Ui::Dialog *ui;
    QAction* CourierAction;
    QAction* CorbelAction;
    QAction* CallunaAction;
    QAction* EarthOrbiterAction;
    QAction* FrightNightAction;


    QAction* centerAction;
    QAction* buttomAction;
    QAction* topAction;

    QAction* smallAction;
    QAction* MediumAction;
    QAction* largeAction;

    QAction* redAction;
    QAction* whiteAction;
    QAction* blueAction;





    //   QMenu* fontMenu;
    //    QMenu* fontSizeMenu;
    QMenu* geometryMenu;
    //    QToolBar* editToolBar;
    //    QToolBar* editMovement;
    //    CustomToolButton* aligntoolBtton;
    //    CustomToolButton* centerToolbutton;
    QList<QAction *>fontSizeActions;
    QList<QAction *>fontColorActions;
    QList<QAction *>fontTextActions;


};

#endif // DIALOG_H
