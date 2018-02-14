#ifndef HISTURE_H
#define HISTURE_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "../ToFunction/tofunction.h"

namespace ImageChange {

#ifndef BYTE
#define BYTE 256
#endif

class Histure
{
protected:
    cv::Mat pict;
    size_t widht;
    size_t height;
    std::string func;
    uchar currentHistogram[BYTE];
    uchar equHistogram[BYTE];
private:
    uchar* EqualHistogram();
    uchar* EstablishHistogram();
public:
    Histure() {}
    Histure(cv::Mat img);
    Histure(cv::Mat img, std::string inf);
    Histure(const Histure &hist);
    virtual ~Histure() {}

    void SetFunction(std::string inf);

    virtual void SetPicture(cv::Mat img);
    cv::Mat GetPicture();
    virtual void RewritePicture();

    uchar* GetCurrentHisogram();
    uchar* GetNewHistogram();

};

class LocalHisture : public Histure
{
private:
    size_t maskSize;
    uchar* EqualHistogram(size_t currentRow, size_t currentCol);
    uchar* EstablishHistogram(size_t currentRow, size_t currentCol);
public:
    LocalHisture() : Histure() {    }
    LocalHisture(cv::Mat img, size_t mask);
    LocalHisture(cv::Mat img, std::string inf, size_t mask);
    LocalHisture(const LocalHisture &lochist);
    LocalHisture(const Histure &globhist, size_t mask_size);
    virtual ~LocalHisture() {}

    virtual void SetPicture(cv::Mat img);

    void SetMask(size_t mask);
    size_t GetMask();

    virtual void RewritePicture(); //

};


cv::Mat ChangeImg(Histure &obj);


}

#endif // HISTURE_H
