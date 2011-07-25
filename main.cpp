// User Interface for Kodak MotionCorder Analyzer

#include <QApplication>
#include <iostream>
#include "MainWindow.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);               //application context which holds the program
	MainWindow test(0);                         //the main user interface window (not yet visible)
    
	test.resize(300,400);                       //size the window to 300 pixels wide by 400 pixels high
	test.show();                                //make window visible
	return app.exec();                          //run the program!
}
