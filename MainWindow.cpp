#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{
    //setFixedSize(350,150);
    QLabel* infoText = new QLabel("Kodak Motion Corder");
    QLabel* fileLabel = new QLabel("Filename:");
    QLineEdit* fileDialog = new QLineEdit();
    
    QSpinBox* startBox = new QSpinBox();
    QLabel* startText = new QLabel("Start Frame:");
    QSpinBox* endBox = new QSpinBox();
    QLabel* endText = new QLabel("End Frame:");
    
    QCheckBox* vidCheck = new QCheckBox("Export Video");
    QLabel* fpsText = new QLabel("fps:");
    QSpinBox* fpsBox = new QSpinBox();
    fpsBox->setMinimum(0);
    
    QPushButton* saveBtn = new QPushButton(tr("Save"), this);

    startBox->setRange(0,100);
    endBox->setRange(0,100);
    vidCheck->setCheckState(Qt::Checked);

    connect(saveBtn, SIGNAL(clicked()), qApp, SLOT(quit()));

    QFormLayout* layout = new QFormLayout;
    QHBoxLayout* fileLayout = new QHBoxLayout;
    fileLayout->addWidget(fileLabel);
    fileLayout->addWidget(fileDialog);
    
    QHBoxLayout* frameBoxLayout = new QHBoxLayout;
    frameBoxLayout->addWidget(startText);
    frameBoxLayout->addWidget(startBox);
    frameBoxLayout->addStretch();
    frameBoxLayout->addWidget(endText);
    frameBoxLayout->addWidget(endBox);
    
    layout->addRow(infoText);
    layout->addRow(fileLayout);
    layout->addRow(frameBoxLayout);
    
    QHBoxLayout* vidLayout = new QHBoxLayout;
    vidLayout->addWidget(vidCheck);
    vidLayout->addStretch();
    vidLayout->addWidget(fpsText);
    vidLayout->addWidget(fpsBox);
    
    
    layout->addRow(vidLayout);
    layout->addRow(saveBtn);
    setLayout(layout);
}
