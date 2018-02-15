#include "pictogram.h"


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

    openFileLineEdit->setText("D:/Users/smert/Libs/Docs/Histogram/test_img/bird.png");
}

void Pictogram::setComboBox()
{
    mainWindow->settingComboBox = new QGroupBox("Settings:");
    mainWindow->globMethRadioButton = new QRadioButton("Global method");
    mainWindow->localMethRadioButton = new QRadioButton("Local method");
    mainWindow->setFuncCheckBox = new QCheckBox("Set function");
    mainWindow->saveCheckBox = new QCheckBox("Save output image");

    mainWindow->globMethRadioButton->setChecked(true);
    mainWindow->saveCheckBox->setChecked(false);

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
    setMaskSize->setEnabled(false);
    setMaskSize->setRange(1, 45);
    setMaskSize->setSingleStep(2);

    mainWindow->setMaskLayout = new QHBoxLayout();
    setMaskLayout->addWidget(setMaskLabel, 0);
    setMaskLayout->addWidget(setMaskSize, 0.6);
    setMaskLayout->addStretch();

    mainWindow->funcLable = new QLabel("Enter the function:");
    mainWindow->funcLineEdit = new QLineEdit("256*x");
    funcLineEdit->setEnabled(false);

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

    saveFileLineEdit->setEnabled(false);
    saveFilePushButton->setEnabled(false);

    mainWindow->saveFileLayout = new QHBoxLayout();
    saveFileLayout->addWidget(saveFileLineEdit, 2);
    saveFileLayout->addWidget(saveFilePushButton, 0);
}

void Pictogram::setProcessPart()
{
    mainWindow->runPushButton = new QPushButton("Run");
    mainWindow->quitPushButton = new QPushButton("Exit");
    mainWindow->progressBar = new QProgressBar();

    mainWindow->buttonsLauout = new QHBoxLayout();
    buttonsLauout->addWidget(progressBar, 1);
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

void Pictogram::setSignals()
{
    // Open
    connect(openFilePushButton, SIGNAL(clicked()), mainWindow, SLOT(slotOpenFileButton()));
    connect(openFileLineEdit, SIGNAL(editingFinished()), mainWindow, SLOT(slotOpenFile()));
    //Settings
    connect(globMethRadioButton, SIGNAL(clicked()), SLOT(slotSettings()));
    connect(localMethRadioButton, SIGNAL(clicked()), SLOT(slotSettings()));
    connect(setFuncCheckBox, SIGNAL(clicked()), SLOT(slotSettings()));
    connect(saveCheckBox, SIGNAL(clicked()), SLOT(slotSettings()));
    // Save
    connect(saveFilePushButton, SIGNAL(clicked()), mainWindow, SLOT(slotSaveFileButton()));
    connect(saveFileLineEdit, SIGNAL(editingFinished()), mainWindow, SLOT(slotSaveFile()));
    // RUN!!!
    connect(runPushButton, SIGNAL(clicked()), SLOT(slotRun()));
    // Exit
    connect(quitPushButton, SIGNAL(clicked()), mainWindow, SLOT(close()));

}

void Pictogram::slotOpenFileButton()
{
    inputFileQT = QFileDialog::getOpenFileName(openFilePushButton, "Open file...", "", "*.png *.jpg");

    QRegExp checkPNG("*.png");
    QRegExp checkJPG("*.jpg");
    checkJPG.setPatternSyntax(QRegExp::Wildcard);
    checkPNG.setPatternSyntax(QRegExp::Wildcard);
    if (!(checkPNG.exactMatch(inputFileQT) || checkJPG.exactMatch(inputFileQT)))
        return;

    openFileLineEdit->setText(inputFileQT);

    inputFileSTD = inputFileQT.toStdString();
    inputIMG = cv::imread(inputFileSTD, 0);

    cv::namedWindow("Input File", cv::WINDOW_AUTOSIZE);
    cv::imshow("Input File", inputIMG);
}

void Pictogram::slotOpenFile()
{
    inputFileQT = openFileLineEdit->text();

    QRegExp checkPNG("*.png");
    QRegExp checkJPG("*.jpg");
    checkJPG.setPatternSyntax(QRegExp::Wildcard);
    checkPNG.setPatternSyntax(QRegExp::Wildcard);
    if (!(checkPNG.exactMatch(inputFileQT) || checkJPG.exactMatch(inputFileQT)))
        return;

    inputFileSTD = inputFileQT.toStdString();
    inputIMG = cv::imread(inputFileSTD, 0);

    cv::namedWindow("Input File", cv::WINDOW_AUTOSIZE);
    cv::imshow("Input File", inputIMG);
}

void Pictogram::slotSettings()
{
    if (globMethRadioButton->isChecked()) {
        setMaskSize->setEnabled(false);
        setMaskSize->setValue(1);
    } else if (localMethRadioButton->isChecked()) {
        setMaskSize->setEnabled(true);
        setMaskSize->setValue(5);
    }

    if (setFuncCheckBox->isChecked()) {
        funcLineEdit->setEnabled(true);
    } else {
        funcLineEdit->setEnabled(false);
    }

    if (saveCheckBox->isChecked()) {
        saveFileLineEdit->setEnabled(true);
        saveFilePushButton->setEnabled(true);
    } else {
        saveFileLineEdit->setEnabled(false);
        saveFilePushButton->setEnabled(false);
    }

}

void Pictogram::slotSaveFileButton()
{
    outputFileQT = QFileDialog::getSaveFileName(saveFilePushButton, "Save file...", "", "*.png ;; *.jpg");

    QRegExp checkPNG("*.png");
    QRegExp checkJPG("*.jpg");
    checkJPG.setPatternSyntax(QRegExp::Wildcard);
    checkPNG.setPatternSyntax(QRegExp::Wildcard);
    if (!(checkPNG.exactMatch(outputFileQT) || checkJPG.exactMatch(outputFileQT)))
        return;

    saveFileLineEdit->setText(outputFileQT);

    outputFileSTD = outputFileQT.toStdString();
}

void Pictogram::slotSaveFile()
{
    outputFileQT = saveFileLineEdit->text();

    QRegExp checkPNG("*.png");
    QRegExp checkJPG("*.jpg");
    checkJPG.setPatternSyntax(QRegExp::Wildcard);
    checkPNG.setPatternSyntax(QRegExp::Wildcard);
    if (!(checkPNG.exactMatch(outputFileQT) || checkJPG.exactMatch(outputFileQT)))
        return;

    saveFileLineEdit->setText(outputFileQT);

    outputFileSTD = outputFileQT.toStdString();
}

void Pictogram::slotRun()
{
    progressBar->reset();

    std::string func = "";
    size_t mask_size = 1;
    ImageChange::Histure* changeImg;

    if (setFuncCheckBox->isChecked()) {
        QString funcQT= funcLineEdit->text();
        func = funcQT.toStdString();
    }

    ImageChange::Histure global_func(inputIMG, func);
    ImageChange::LocalHisture local_func(inputIMG, func, mask_size);

    if (globMethRadioButton->isChecked()) {
        changeImg = &global_func;
        progressBar->setRange(0, inputIMG.rows - 1);

    }
    if (localMethRadioButton->isChecked()) {
        mask_size = (size_t)setMaskSize->value();
        local_func.SetMask(mask_size);
        changeImg = &local_func;
        progressBar->setRange(0, inputIMG.rows - mask_size - 1);

    }
    changeImg->SetProgressBar(progressBar);
    changeImg->RewritePicture();
    outputIMG = changeImg->GetPicture();

    cv::namedWindow("Output File", cv::WINDOW_AUTOSIZE);
    cv::imshow("Output File", outputIMG);

    if (saveCheckBox->isChecked()) {
        cv::imwrite(outputFileSTD, outputIMG);
    }
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

    setSignals();
}

Pictogram::~Pictogram()
{
//    delete mainLayout;

//    delete openFileLayout;
//    delete openFileLabel;
//    delete openFileLineEdit;
//    delete openFilePushButton;
//    delete openFileDialog;

//    delete settingComboBox;
//    delete settingLayout;
//    delete globMethRadioButton;
//    delete localMethRadioButton;
//    delete setFuncCheckBox;
//    delete saveCheckBox;

//    delete setMaskLayout;
//    delete setMaskLabel;
//    delete setMaskSize;

//    delete setFuncLayout;
//    delete funcLable;
//    delete funcLineEdit;

//    delete saveFileLayout;
//    delete saveFileLabel;
//    delete saveFileLineEdit;
//    delete saveFilePushButton;
//    delete saveFileDialog;

//    delete buttonsLauout;
//    delete runPushButton;
//    delete quitPushButton;

//    delete progrressBar;
//    delete progressLabel;
}
