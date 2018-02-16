#ifndef PICTOGRAM_H
#define PICTOGRAM_H

#include <QWidget>

#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>

#include <QPushButton>
#include <QGroupBox>
#include <QCheckBox>
#include <QRadioButton>

#include <QFileDialog>

#include <QProgressBar>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QString>
#include <string>

#include "../Histure/histure.h"

class Pictogram : public QWidget
{
    Q_OBJECT
private:
    Pictogram* mainWindow;

    QVBoxLayout* mainLayout;

    QHBoxLayout* openFileLayout;
    QLabel* openFileLabel;
    QLineEdit* openFileLineEdit;
    QPushButton* openFilePushButton;

    QGroupBox* settingComboBox;
    QVBoxLayout* settingLayout;
    QRadioButton* globMethRadioButton;
    QRadioButton* localMethRadioButton;
    QCheckBox* setFuncCheckBox;
    QCheckBox* saveCheckBox;

    QHBoxLayout* setMaskLayout;
    QLabel* setMaskLabel;
    QSpinBox* setMaskSize;

    QHBoxLayout* setFuncLayout;
    QLabel* funcLable;
    QLineEdit* funcLineEdit;

    QHBoxLayout* saveFileLayout;
    QLabel* saveFileLabel;
    QLineEdit* saveFileLineEdit;
    QPushButton* saveFilePushButton;

    QHBoxLayout* buttonsLauout;
    QPushButton* runPushButton;
    QPushButton* quitPushButton;

    QProgressBar* progressBar;
    QLabel* progressLabel;

    QString inputFileQT;
    QString oldStr;
    std::string inputFileSTD;

    QString outputFileQT;
    std::string outputFileSTD;

    cv::Mat inputIMG;
    cv::Mat outputIMG;

    void setMainWindow();
    void setOpenFile();
    void setComboBox();
    void setSetting();
    void setSaveFile();
    void setProcessPart();
    void setMainLayout();

    void setSignals();
    void closeEvent(QCloseEvent *event);
public slots:
    void slotOpenFileButton();
    void slotOpenFile();
    void slotSettings();
    void slotSaveFileButton();
    void slotSaveFile();
    void slotRun();

public:
    explicit Pictogram(QWidget *parent = 0);
    ~Pictogram();

};

#endif // PICTOGRAM_H
