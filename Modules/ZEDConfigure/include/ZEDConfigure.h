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
#include <time.h>
#include <string>
#include "../../../Parameter/include/Parameter.h"

using namespace cv;
using namespace dnn;
using namespace std;
using namespace cv::cuda;


void init(sl::Camera &zed);
cv::Mat getFrame(sl::Camera &zed);
void getDepth(sl::Camera &zed,sl::Mat&);
void ROI_AEC(sl::Camera &zed, sl::Rect Area);
void zedclose(sl::Camera &zed);