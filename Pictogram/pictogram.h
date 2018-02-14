#ifndef PICTOGRAM_H
#define PICTOGRAM_H

#include <QWidget>

#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>

#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>

#include <QFileDialog>

#include <QProgressBar>

#include <QVBoxLayout>
#include <QHBoxLayout>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class Pictogram : public QWidget
{
    Q_OBJECT
private:
    QVBoxLayout* mainLayout;

    QHBoxLayout* openFileLayout;
    QLabel* openFileLabel;
    QLineEdit* openFileLineEdit;
    QPushButton* openFilePushButton;
    QFileDialog* openFileDialog;

    QComboBox* settingComboBox;
    QRadioButton* globMethRadioButton;
    QRadioButton* localMethRadioButton;
    QCheckBox* setFuncCheckBox;
    QCheckBox* saveCheckBox;

    QHBoxLayout* setMaskLayout;
    QLabel* setMaskLabel;
    QSpinBox* setMaskSize;

    QLabel* funcLable;
    QLineEdit* funcLineEdit;

    QHBoxLayout* saveFileLayout;
    QLabel* saveFileLabel;
    QLineEdit* saveFileLineEdit;
    QPushButton* saveFilePushButton;
    QFileDialog* saveFileDialog;

    QPushButton* runPushButton;
    QPushButton* quitPushButton;

    QProgressBar* progrressBar;
    QLabel* progressLabel;

    void setMainWindow();
    void setOpenFile();
    void setComboBox();
    void setSetting();
    void setSaveFile();

public:
    explicit Pictogram(QWidget *parent = 0);
    ~Pictogram();

};

#endif // PICTOGRAM_H
