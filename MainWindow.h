#pragma once
#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include <QProgressBar>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QCheckBox>

class MainWindow : public QWidget
{
    Q_OBJECT                            //Required by Qt for signals/slots/etc.
public:
    MainWindow(QWidget* parent = 0);

public slots:
    void save();
    
private:
    void initKMC();
    
    QLineEdit* fileDialog;    
    QSpinBox* startBox;
    QSpinBox* endBox;
    QProgressBar* saveProgress;
    QMessageBox error;
};
