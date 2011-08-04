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
#include <QDoubleSpinBox>
#include <QStyle>
#include <QWidget>
#include <string>

class MainWindow : public QWidget
{
    Q_OBJECT                            //Required by Qt for signals/slots/etc.
public:
    MainWindow(QWidget* parent = 0);

public slots:
    void exportVideo();
    void save();
    void fpsStateChange();
    void setDirectory();
    
private:
    void initKMC();
    
    char directoryName[512];
    
    QString home;    
    QLineEdit* dirText;
    QPushButton* dirBtn; 
    QSpinBox* startBox;
    QSpinBox* endBox;
    QCheckBox* vidCheck;
    QDoubleSpinBox* timeFactorBox;
    QLabel* fpsText;
    QProgressBar* saveProgress;
    QMessageBox error;
};
