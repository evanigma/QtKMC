#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowIcon(QIcon(":/Icon/QtKMC.png"));
    helpMenu = menuBar()->addMenu(tr("&Help"));
    aboutAct = new QAction("&About", this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    helpMenu->addAction(aboutAct);
    
    interface = new MainInterface(0);
    setCentralWidget(interface);
}

void MainWindow::about()
//POST: Displays an "about" message box, with information about this program.
{
    QMessageBox::about(this, tr("QtKMC"),
             tr("QtKMC.\nCreated Summer 2011 by Evan Fox."));
}
