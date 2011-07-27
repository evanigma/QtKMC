#include "MainWindow.h"
#include "kmc.h"

MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{
    error.setIcon(QMessageBox::Warning);
    home = QDir::home().absolutePath();
    initKMC();
    //setFixedSize(350,150);
    QLabel* infoText = new QLabel("Kodak Motion Corder");
    QLabel* dirLabel = new QLabel("Directory:");
    dirText = new QLineEdit(home+"/Desktop/");
    dirBtn = new QPushButton(style()->standardIcon(QStyle::SP_DirIcon),"");
    
    startBox = new QSpinBox();
    QLabel* startText = new QLabel("Start Frame:");
    endBox = new QSpinBox();
    QLabel* endText = new QLabel("End Frame:");
    
    vidCheck = new QCheckBox("Export Video");
    fpsText = new QLabel("fps:");
    fpsBox = new QSpinBox();
    fpsBox->setMinimum(0);
    fpsBox->setValue(fps);
    
    QPushButton* saveBtn = new QPushButton(tr("Save"), this);

    startBox->setRange(1,totalFrames);
    endBox->setRange(1,totalFrames);
    endBox->setValue(totalFrames);
    vidCheck->setCheckState(Qt::Checked);
    
    saveProgress = new QProgressBar();

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
    
    strcpy((char*)&filenamebase,(char*)dirText->text().toStdString().c_str());
    
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

void MainWindow::fpsStateChange()
{
    fpsBox->setEnabled(!fpsBox->isEnabled());
    fpsText->setEnabled(!fpsText->isEnabled());
}

void MainWindow::setDirectory()
{
    dirText->setText(QFileDialog::getExistingDirectory(this,
     tr("Choose Output Directory"), home));
}

void MainWindow::initKMC()
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
