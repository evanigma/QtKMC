#include <QMainWindow>
#include <QtGui>
#include "MainInterface.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT                    //Required by Qt to allow for signals, slots, etc.
	
public:
	MainWindow(QWidget *parent);
	
public slots:
    void about();
	
private:
    MainInterface* interface;
    QMenu* helpMenu;
    
    QAction* aboutAct;	
};
