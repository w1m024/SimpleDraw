#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "centerwidget.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QToolButton>
#include <QSlider>
#include <QSpinBox>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QColor currentColor;
    CenterWidget *centerWidget;
    QMenu *fileMenu;
    QMenu *drawMenu;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;
    QAction *lineAction;
    QAction *ellipseAction;
    QAction *rectangleAction;
    QAction *pointAction;
    QAction *undoAction;
    QAction *redoAction;
    QToolBar *drawToolBar;
    QToolBar *colorToolBar;
    QSlider *lineWidthSlider;
    QSpinBox *lineWidthBox;
protected slots:

    void line();
    void ellipse();
    void rectangle();
    void point();
    void setColor();
    void setLineWidth(int value);
    void undo();
    void redo();
    void newDrawing();
    void openDrawing();
    void saveDrawing();
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
