#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    w=this->centralWidget();


    edit=new MyTextEditor(w);

    w->resize(this->size());
    edit->resize(w->size());


    createMenuBar(this->menuBar());

    setIcon();

    this->setWindowTitle("My text editor");

}

void MainWindow::setIcon()
{
    this->setWindowIcon(QIcon(":/images/icon.png"));
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);

   edit->resize(size());
}


void MainWindow::about()
{
    QMessageBox m("About",
                  "This is a text editor.\r\n"
                  "ver. 1.0.0",
                  QMessageBox::NoIcon,
                  QMessageBox::Ok,
                  QMessageBox::NoButton,
                  QMessageBox::NoButton
                  );
    m.setWindowIcon(QIcon(":/images/icon.png"));
    m.exec();
}
void MainWindow::createMenuBar(QMenuBar* menu)
{
    QMenu* menuFile=new QMenu("&Menu");
    menuFile->addAction("&New", edit,
                        &MyTextEditor::clear,
                        Qt::CTRL + Qt::Key_N
                        );

    menuFile->addAction("&Open...", edit,
                        &MyTextEditor::open,
                        Qt::CTRL + Qt::Key_O
                        );
    menuFile->addAction("&Save", edit,
                        &MyTextEditor::save,
                        Qt::CTRL +  Qt::Key_S
                        );
    menuFile->addAction("Sa&ve as...", edit,
                        &MyTextEditor::saveAs,
                        Qt::CTRL + Qt::SHIFT + Qt::Key_S
                        );
    menuFile->addSeparator();
    menuFile->addAction("&Font...", edit,
                        &MyTextEditor::changeFont
                        );
    menuFile->addSeparator();
    menuFile->addAction("&About", this,
                        &MainWindow::about);
    menuFile->addAction("&Close", this,
                        &MainWindow::close);

    ;

    menu->addMenu(menuFile);
}


MainWindow::~MainWindow()
{
    delete ui;
}

