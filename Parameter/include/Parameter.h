#ifndef PROCESS_H
#define PROCESS_H


#include <sl/Camera.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/core/utility.hpp"
#include "opencv2/cudabgsegm.hpp"
#include <vector>
#include <map>
#include <stdio.h>
#include <string.h>

using namespace cv;
using namespace dnn;
using namespace std;
using namespace cv::cuda;

 struct RegParam
{
    //选颜色 自己边的颜色
    int Side;//0Red 1Blue
    std::vector<std::string> classes;
    std::vector<std::string> carclasses;
    float confThreshold;
    float nmsThreshold;
    float scale;
    //Scalar mean = Scalar();
    int inpWidth;
    int inpHeight;
    std::string classfile;
    std::string carclassfile;
    std::string weightfile;
    std::string cfgfile;
    std::string videofile;
    std::string cffile;
    std::string cfcfgfile;
    std::string mapfile;
    std::string mapdatafile;
    std::string mapareafile;
    std::string gamestatefile;
    std::string zedparamfile;
    std::string btreefile;
    int game;
    vector<Mat> Warnings;
    int warningStatus;
    Ptr<BackgroundSubtractor> mog = cuda::createBackgroundSubtractorMOG2();
    RegParam();
};
extern RegParam param;

struct filepath{
    string detectcfg;
    string detectweight;
    string classifiercfg;
    string classifierweight;
    string video;
    string mapdata;
};

 struct ZEDParam
{

    ZEDParam();
};
extern ZEDParam zedparam;
struct CameraParam
{

    CameraParam();
};
extern CameraParam camparam;


void getClasses();
void loadModel(DetectionModel &dect, ClassificationModel &classif);

#endif
