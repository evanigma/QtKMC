#pragma once
#include <QApplication>
#include <QCheckBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QProgressBar>
#include <QPushButton>
#include <QSpinBox>
#include <QStyle>
#include <QWidget>

class MainWindow : public QWidget
{
    Q_OBJECT                            //Required by Qt for signals/slots/etc.
public:
    MainWindow(QWidget* parent = 0);

public slots:
    void save();
    void fpsStateChange();
    void setDirectory();
    
private:
    void initKMC();
    
    QString home;    
    QLineEdit* dirText;
    QPushButton* dirBtn; 
    QSpinBox* startBox;
    QSpinBox* endBox;
    QCheckBox* vidCheck;
    QSpinBox* fpsBox;
    QLabel* fpsText;
    QProgressBar* saveProgress;
    QMessageBox error;
};
