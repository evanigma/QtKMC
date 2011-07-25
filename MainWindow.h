// MainWindow -- main window of the user interface in Qt for visualizing sound with OpenGL and SDL.
// Summer 2009, Evan Fox and Doug Hogan

#pragma once
#include <QMainWindow>
#include <QtGui>
#include <vector>
using namespace std;

class MainWindow : public QMainWindow
{
	Q_OBJECT                    //Required by Qt to allow for signals, slots, etc. 
	
public:
	MainWindow(QWidget *parent);
	//PRE: parent points to an initialized QWidget
	//POST: The application's GUI elements are created (menus, dock, toolbar), and we are set up to
	//		start playing songs
    
	~MainWindow();
	//POST: Dynamically allocated memory not handled by Qt is freed.
	
public slots:
	//void open();
	
signals:
	//void newSong(Wave* song);
	
protected:
	/*void contextMenuEvent(QContextMenuEvent* event);
	//POST: Creates a context menu at the current mouse location with options for increasing the red,
	//		green, or blue of the visualization, switching the visualization, or entering/leaving full screen.*/
	
private:
	//void createDock();
	//POST: Creates a playlist widget dock that allows for our playlist to be docked on either the
	//		left or right side of our window.
    
    
    //DATA MEMBERS
    //--------------------------------------------------------------------------
};
