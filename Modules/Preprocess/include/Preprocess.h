
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
#include "../../../Parameter/include/Parameter.h"


using namespace cv;
using namespace dnn;
using namespace std;
using namespace cv::cuda;
Mat MOGProcess(Mat &frame);
Mat frameDiff(Mat &frame,Mat&);
void NDProcess(Mat&, Mat &frame, vector<Point> &PointResultsB, vector<Rect> &RectResultsB,vector<Point> &PointResultsR, vector<Rect> &RectResultsR);