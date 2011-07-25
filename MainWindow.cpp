#include <iostream>
#include <string>
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
//PRE: parent points to an initialized QWidget
//POST: The application's GUI elements are created (menus, dock, toolbar), and we are set up to
//		start playing songs
{
	//setWindowIcon(QIcon(":/Icon/GLUI.png"));		//Set Icon to image as located by .qrc file
	
	setCentralWidget(this);						//every QMainWindow needs a central widget
													//(the one that is the primary focus)
														
	/*connect(this, SIGNAL(newSong(Wave*)), 			//When we start playing a new song,
			myPlayer, SLOT(playNewSong(Wave*)));	//let the SDL music player*/
}

MainWindow::~MainWindow()
//POST: Dynamically allocated memory not handled by Qt is freed.
{
}
