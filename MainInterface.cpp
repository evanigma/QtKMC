#include "MainInterface.h"
#include "kmc.h"
#include <stdio.h>
using namespace std;

MainInterface::MainInterface(QWidget* parent) : QWidget(parent)
{    
    error.setIcon(QMessageBox::Warning);
    home = QDir::home().absolutePath();
   
    //system("export PATH=$PATH:`pwd`"); //Doesn't Work
    initKMC();
    
    MPEG_FRAME_RATE = (fps % 30 == 0) ? 30 : 25;
    
    //setFixedSize(350,150);
    QLabel* infoText = new QLabel("Kodak Motion Corder");
    QLabel* dirLabel = new QLabel("Directory:");
    
    char* timestamp = new char[20];
    sprintf(timestamp,"%02d-%02d-%d_%02d:%02d",month,date,year%1000,time_hour,time_minute);
    dirText = new QLineEdit(home+"/Desktop/"+timestamp+"/");
    dirBtn = new QPushButton(style()->standardIcon(QStyle::SP_DirIcon),"");
    
    startBox = new QSpinBox();
    QLabel* startText = new QLabel("Start Frame:");
    endBox = new QSpinBox();
    QLabel* endText = new QLabel("End Frame:");
    
    vidCheck = new QCheckBox("Export Video");
    fpsText = new QLabel("Time Factor:");
    timeFactorBox = new QDoubleSpinBox();
    timeFactorBox->setRange(MPEG_FRAME_RATE/double(fps),(totalFrames-1)*MPEG_FRAME_RATE/double(fps));
    timeFactorBox->setValue(1);
    timeFactorBox->setSingleStep(MPEG_FRAME_RATE/double(fps));
    
    QPushButton* saveBtn = new QPushButton(tr("Save"), this);

    startBox->setRange(1,totalFrames);
    endBox->setRange(1,totalFrames);
    endBox->setValue(totalFrames);
    vidCheck->setCheckState(Qt::Checked);
    
    saveProgress = new QProgressBar();
    //saveProgress->setFormat("%v/%m"); //(%v doesn't do what you would think it does.)

    connect(saveBtn, SIGNAL(clicked()), this, SLOT(save()));
    connect(vidCheck, SIGNAL(stateChanged(int)), this, SLOT(fpsStateChange()));
    connect(dirBtn, SIGNAL(clicked()), this, SLOT(setDirectory()));

    QFormLayout* layout = new QFormLayout;
    QHBoxLayout* fileLayout = new QHBoxLayout;
    fileLayout->addWidget(dirLabel);
    fileLayout->addWidget(dirText);
    fileLayout->addWidget(dirBtn);
    
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
    vidLayout->addWidget(timeFactorBox);
    
    
    layout->addRow(vidLayout);
    layout->addRow(saveBtn);
    layout->addRow(saveProgress);
    setLayout(layout);
}

void MainInterface::exportVideo()
{
    int frameSkip = int(timeFactorBox->value()*fps/MPEG_FRAME_RATE);
    char frameMessage[128];
    sprintf(frameMessage, "videos.sh %s %d %d", directoryName, frameSkip, MPEG_FRAME_RATE);
    system(frameMessage); 
}

void MainInterface::save()
{
    QDir().mkdir(dirText->text());
    
    if (!dirText->text().endsWith("/"))
        dirText->setText(dirText->text().append("/"));
        
    start_frame = startBox->value()-1;
    end_frame = endBox->value()-1;
    
    strcpy(directoryName, (char*)dirText->text().toStdString().c_str());
    strcpy((char*)&filenamebase, directoryName);
    
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
        saveProgress->setRange(start_frame, end_frame+1);
        for (framenumber=startBox->value()-1; framenumber<=endBox->value()-1; framenumber++)
        {
            saveProgress->setValue(framenumber+1);
            read_frame(framenumber-(startBox->value()-1));
        }
        if (vidCheck->isChecked())
            exportVideo();
    }
}

void MainInterface::fpsStateChange()
{
    timeFactorBox->setEnabled(!timeFactorBox->isEnabled());
    fpsText->setEnabled(!fpsText->isEnabled());
}

void MainInterface::setDirectory()
{
    dirText->setText(QFileDialog::getExistingDirectory(this,
     tr("Choose Output Directory"), home));
}

void MainInterface::initKMC()
{
    if (kmc_dev_fd("/dev/sg3") < 0)
    {
        error.setText("Device not found.\n\n You must record something before the computer is turned on for the device to be recognized. Try a reboot.");
        error.exec();
        setEnabled(false);
        return;
    }
    init("/dev/sg3");
}
