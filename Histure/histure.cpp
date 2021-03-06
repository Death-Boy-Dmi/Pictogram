#include "histure.h"

using namespace ImageChange;

cv::Mat ChangeImg(Histure &obj)
{
    obj.RewritePicture();
    return obj.GetPicture();
}

//----------------------------------------------------------------

double* Histure::EstablishHistogram()
{
    for (size_t i = 0; i < BYTE; ++i) {
        currentHistogram[i] = 0;
    }
    for (size_t row = 0; row < widht; ++row) {
        for (size_t col = 0; col < height; ++col) {
            currentHistogram[pict.at<uchar>(row, col)] += 1;
        }
    }
    return currentHistogram;
}
double* Histure::EqualHistogram()
{
    for (size_t i = 0; i < BYTE; ++i) {
        equHistogram[i] = 0;
    }
    for (size_t currentValue = 0; currentValue < BYTE; ++currentValue) {
        for (size_t i = 0; i < currentValue; ++i) {
            equHistogram[currentValue] += currentHistogram[i] / (widht * height);
        }
    }
    return equHistogram;
}
Histure::Histure(cv::Mat img)
{
    this->pict = img;
    this->height = img.cols;
    this->widht = img.rows;
    this->func = "";

    EstablishHistogram();
    EqualHistogram();
}
Histure::Histure(cv::Mat img, std::string inf)
{
    this->pict = img;
    this->height = img.cols;
    this->widht = img.rows;
    this->func = inf;

    EstablishHistogram();
    EqualHistogram();
}
Histure::Histure(const Histure &hist)
{
    this->pict = hist.pict;
    this->height = hist.height;
    this->widht = hist.widht;
    this->func = hist.func;

    for (size_t i = 0; i < BYTE; ++i) {
        this->currentHistogram[i] = hist.currentHistogram[i];
        this->equHistogram[i] = hist.equHistogram[i];
    }
}
void Histure::SetFunction(std::string inf)
{
    this->func = inf;
}
void Histure::SetPicture(cv::Mat img)
{
    this->pict = img;
    this->height = img.cols;
    this->widht = img.rows;

    EstablishHistogram();
    EqualHistogram();
}
cv::Mat Histure::GetPicture()
{
    return this->pict;
}
void Histure::RewritePicture()
{
    if (func == "") {
        for (size_t row = 0; row < widht; ++row) {
            for (size_t col = 0; col < height; ++col) {
                pict.at<uchar>(row, col) = BYTE * equHistogram[pict.at<uchar>(row, col)];
            }
            process->setValue(++counter);
        }
    } else {
        ToFunction function(func);
        for (size_t row = 0; row < widht; ++row) {
                for (size_t col = 0; col < height; ++col) {
                    double x = equHistogram[pict.at<uchar>(row, col)];
                    pict.at<uchar>(row, col) = (uchar)function.Calculate(x);
                }
                process->setValue(++counter);
        }
    }
    EstablishHistogram();
    EqualHistogram();
}
double* Histure::GetCurrentHisogram()
{
    return this->currentHistogram;
}
double* Histure::GetNewHistogram()
{
    return this->equHistogram;
}

void Histure::SetProgressBar(QProgressBar *prbar)
{
    process = prbar;
    counter = 0;
}


//----------------------------------------------------------------


LocalHisture::LocalHisture(cv::Mat img, size_t mask) : Histure(img), maskSize(mask)
{
    for (size_t i = 0; i < BYTE; ++i) {
        equHistogram[i] = 0;
        currentHistogram[i] = 0;
    }
}

LocalHisture::LocalHisture(cv::Mat img, std::string inf, size_t mask) : Histure(img, inf), maskSize(mask)
{
    for (size_t i = 0; i < BYTE; ++i) {
        equHistogram[i] = 0;
        currentHistogram[i] = 0;
    }
}

LocalHisture::LocalHisture(const LocalHisture &lochist) : Histure(lochist.pict, lochist.func), maskSize(lochist.maskSize)
{
    for (size_t i = 0; i < BYTE; ++i) {
        equHistogram[i] = 0;
        currentHistogram[i] = 0;
    }
}

LocalHisture::LocalHisture(const Histure &globhist, size_t mask) : Histure(globhist), maskSize(mask)
{
    for (size_t i = 0; i < BYTE; ++i) {
        equHistogram[i] = 0;
        currentHistogram[i] = 0;
    }
}

void LocalHisture::SetPicture(cv::Mat img)
{
    pict = img;
    height = img.cols;
    widht = img.rows;

    for (size_t i = 0; i < BYTE; ++i) {
        equHistogram[i] = 0;
        currentHistogram[i] = 0;
    }
}

void LocalHisture::SetMask(size_t mask)
{
    maskSize = mask;
    for (size_t i = 0; i < BYTE; ++i) {
        equHistogram[i] = 0;
        currentHistogram[i] = 0;
    }
}

size_t LocalHisture::GetMask()
{
    return maskSize;
}

void LocalHisture::RewritePicture()
{
    cv::Mat img = cv::Mat::zeros(pict.size(), CV_8UC1);
    if (func == "") {
        for (size_t row = maskSize / 2; row < widht - maskSize / 2; ++row) {
            for (size_t col = maskSize / 2; col < height - maskSize / 2; ++col) {
                EqualHistogram(row, col);
				for (size_t i = row - maskSize / 2; i < row + maskSize / 2; ++i) {
					for (size_t j = col - maskSize / 2; j < col + maskSize / 2; ++j) {
						img.at<uchar>(i, j) = BYTE * equHistogram[pict.at<uchar>(i, j)];
					}
				}
            }
            process->setValue(++counter);
        }
    } else {
        ToFunction function(func);
		for (size_t row = maskSize / 2; row < widht - maskSize / 2; ++row) {
			for (size_t col = maskSize / 2; col < height - maskSize / 2; ++col) {
                EqualHistogram(row, col);
				for (size_t i = row - maskSize / 2; i < row + maskSize / 2; ++i) {
					for (size_t j = col - maskSize / 2; j < col + maskSize / 2; ++j) {
						double x = equHistogram[pict.at<uchar>(i, j)];
						img.at<uchar>(i, j) = (uchar)function.Calculate(x);
					}
                }
            }
            process->setValue(++counter);
        }
    }

    pict = img;
    for (size_t i = 0; i < BYTE; ++i) {
        equHistogram[i] = 0;
        currentHistogram[i] = 0;
    }
}

double* LocalHisture::EqualHistogram(size_t i, size_t j)
{
    EstablishHistogram(i, j);
    for (size_t i = 0; i < BYTE; ++i) {
        equHistogram[i] = 0;
    }
    for (size_t currentValue = 0; currentValue < BYTE; ++currentValue) {
        for (size_t i = 0; i < currentValue; ++i) {
            equHistogram[currentValue] += currentHistogram[i] / (maskSize * maskSize);
        }
    }
    return equHistogram;
}	

double* LocalHisture::EstablishHistogram(size_t i, size_t j)
{
    for (size_t k = 0; k < BYTE; ++k) {
        currentHistogram[k] = 0;
    }

    for (size_t row = i - maskSize / 2; row < i + maskSize / 2; ++row) {
        for (size_t col = j - maskSize / 2; col < j + maskSize / 2; ++col) {
            currentHistogram[pict.at<uchar>(row, col)] += 1;
        }
    }
//    if (j == maskSize / 2) {
//        for (size_t row = i - maskSize / 2; row < i + maskSize / 2; ++row) {
//            for (size_t col = j - maskSize / 2; col < j + maskSize / 2; ++col) {
//                currentHistogram[pict.at<uchar>(row, col)] += 1;
//            }
//        }
//    } else {
//        for (size_t row = i - maskSize / 2; row < i + maskSize / 2; ++row) {
//            currentHistogram[pict.at<uchar>(row, j - (maskSize / 2 + 1))] -= 1;
//            currentHistogram[pict.at<uchar>(row, j + maskSize / 2)] += 1;
//        }
//    }
    return currentHistogram;
}
