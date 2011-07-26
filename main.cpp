// User Interface for Kodak MotionCorder Analyzer

#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QObject>
#include <iostream>
#include "MainWindow.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);               //application context which holds the program
    MainWindow window;
	window.show();                                //make window visible

	return app.exec();                          //run the program!
}
