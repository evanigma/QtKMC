#include "MainWindow.h"
#include "kmc.h"

MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{
    initKMC();
    //setFixedSize(350,150);
    QLabel* infoText = new QLabel("Kodak Motion Corder");
    QLabel* fileLabel = new QLabel("Filename:");
    fileDialog = new QLineEdit();
    
    startBox = new QSpinBox();
    QLabel* startText = new QLabel("Start Frame:");
    endBox = new QSpinBox();
    QLabel* endText = new QLabel("End Frame:");
    
    QCheckBox* vidCheck = new QCheckBox("Export Video");
    QLabel* fpsText = new QLabel("fps:");
    QSpinBox* fpsBox = new QSpinBox();
    fpsBox->setMinimum(0);
    fpsBox->setValue(fps);
    
    QPushButton* saveBtn = new QPushButton(tr("Save"), this);

    startBox->setRange(1,totalFrames);
    endBox->setRange(1,totalFrames);
    endBox->setValue(totalFrames);
    vidCheck->setCheckState(Qt::Checked);
    
    saveProgress = new QProgressBar();

    connect(saveBtn, SIGNAL(clicked()), this, SLOT(save()));

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
    layout->addRow(saveProgress);
    setLayout(layout);
}

void MainWindow::save()
{
    start_frame = startBox->value()-1;
    end_frame = endBox->value()-1;
    
    strcpy((char*)&filenamebase,(char*)fileDialog->text().toStdString().c_str());
    
    QMessageBox error;
    error.setText("Start Frame must not be greater than End Frame.\nSwitching indices.");
    if (start_frame > end_frame)
    {
        error.exec();
        startBox->setValue(end_frame+1);
        endBox->setValue(start_frame+1);
    }
    else
    {
        saveProgress->reset();
        saveProgress->setRange(start_frame, end_frame);
        for (framenumber=startBox->value()-1; framenumber<=endBox->value()-1; framenumber++)
        {
            saveProgress->setValue(framenumber);
            start_frame = framenumber;
            end_frame = framenumber;
            read_multiple_frames();
        }
    }
}

void MainWindow::initKMC()
{
    init("/dev/sg3");
    //read_multiple_frames();
}
