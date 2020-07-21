#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


#include "MyTextEditor.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
    MyTextEditor* edit;
    QWidget* w;

protected:
    virtual void resizeEvent(QResizeEvent* event);
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void about();

private:
    Ui::MainWindow *ui;

    void createMenuBar(QMenuBar* menu);
    void setIcon();
};
#endif // MAINWINDOW_H
