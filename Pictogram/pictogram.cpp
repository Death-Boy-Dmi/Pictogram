#include "pictogram.h"
#include "ui_pictogram.h"

void Pictogram::setMainWindow()
{
    mainWindow->setWindowTitle("Pictogram");
    mainWindow->setGeometry(125, 100, 400, 350);
    mainWindow->setMinimumSize(400, 350);
    mainWindow->setMaximumSize(900, 350);
}

void Pictogram::setOpenFile()
{
    mainWindow->openFileLabel = new QLabel("Input image:");
    mainWindow->openFileLineEdit = new QLineEdit();
    mainWindow->openFilePushButton = new QPushButton("Choose...");

    mainWindow->openFileLayout = new QHBoxLayout();
    openFileLayout->addWidget(openFileLineEdit, 2);
    openFileLayout->addWidget(openFilePushButton, 0);
}

void Pictogram::setComboBox()
{
    mainWindow->settingComboBox = new QGroupBox("Settings:");
    mainWindow->globMethRadioButton = new QRadioButton("Global method");
    mainWindow->localMethRadioButton = new QRadioButton("Local method");
    mainWindow->setFuncCheckBox = new QCheckBox("Set function");
    mainWindow->saveCheckBox = new QCheckBox("Save output image");

    mainWindow->globMethRadioButton->setChecked(true);

    mainWindow->settingLayout = new QVBoxLayout();
    settingLayout->addWidget(globMethRadioButton);
    settingLayout->addWidget(localMethRadioButton);
    settingLayout->addWidget(setFuncCheckBox);
    settingLayout->addWidget(saveCheckBox);

    settingComboBox->setLayout(settingLayout);
}

void Pictogram::setSetting()
{
    mainWindow->setMaskLabel = new QLabel("Set size of mask:");
    mainWindow->setMaskSize = new QSpinBox();
    setMaskSize->setRange(3, 45);
    setMaskSize->setSingleStep(2);

    mainWindow->setMaskLayout = new QHBoxLayout();
    setMaskLayout->addWidget(setMaskLabel, 0);
    setMaskLayout->addWidget(setMaskSize, 0.6);
    setMaskLayout->addStretch();

    mainWindow->funcLable = new QLabel("Enter the function:");
    mainWindow->funcLineEdit = new QLineEdit("256*x");

    mainWindow->setFuncLayout = new QHBoxLayout();
    setFuncLayout->addWidget(funcLable, 0);
    setFuncLayout->addWidget(funcLineEdit, 1);
    setFuncLayout->addStretch();
}

void Pictogram::setSaveFile()
{
    mainWindow->saveFileLabel = new QLabel("Output image:");
    mainWindow->saveFileLineEdit = new QLineEdit();
    mainWindow->saveFilePushButton = new QPushButton("Choose...");

    mainWindow->saveFileLayout = new QHBoxLayout();
    saveFileLayout->addWidget(saveFileLineEdit, 2);
    saveFileLayout->addWidget(saveFilePushButton, 0);
}

void Pictogram::setProcessPart()
{
    mainWindow->runPushButton = new QPushButton("Run");
    mainWindow->quitPushButton = new QPushButton("Quit");
    mainWindow->progrressBar = new QProgressBar();

    mainWindow->buttonsLauout = new QHBoxLayout();
    buttonsLauout->addWidget(progrressBar, 1);
    buttonsLauout->addWidget(runPushButton, 0);
    buttonsLauout->addWidget(quitPushButton, 0);
}

void Pictogram::setMainLayout()
{
    mainWindow->mainLayout = new QVBoxLayout();
    mainLayout->addWidget(openFileLabel);
    mainLayout->addLayout(openFileLayout);
    mainLayout->addWidget(settingComboBox);
    mainLayout->addLayout(setMaskLayout);
    mainLayout->addLayout(setFuncLayout);
    mainLayout->addWidget(saveFileLabel);
    mainLayout->addLayout(saveFileLayout);

    mainLayout->addStretch();

    mainLayout->addLayout(buttonsLauout);
}

Pictogram::Pictogram(QWidget *parent) :
    QWidget(parent)
{
    mainWindow = this;

    setMainWindow();
    setOpenFile();
    setComboBox();
    setSetting();
    setSaveFile();
    setProcessPart();
    setMainLayout();

    mainWindow->setLayout(mainLayout);
}

Pictogram::~Pictogram()
{

}
