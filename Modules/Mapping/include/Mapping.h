#ifndef MAP_H
#define MAP_H

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
#include "../../ZEDConfigure/include/ZEDConfigure.h"
#define WINDOW "CAMERA"
#define WINDOW_MAP "MAP"
/*#define RED 0
#define BLUE 1*/
//#include "referee.h"

/*#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>*/

using namespace cv;
using namespace dnn;
using namespace std;
using namespace cv::cuda;

class mapping
{
public:
    mapping();
    void On_mouse(int event, int x, int y); // int flags, void *ustc); //鼠标回调事件函数
    void On_mouse2(int event, int x, int y);
    bool isPointInRect(int x, int y, vector<Point> choosePoints);
    void mappingpre(cv::String, cv::String);
    void mappingpost(vector<Point> point_dect, vector<Point> &point_map);
    void drawmap(vector<Point> &point_map, bool red, Mat);
    void drawmap(vector<Point> &point_map, vector<int> type, bool red, int typenum, Mat);
    static void Onmouse(int event, int x, int y, int, void *this_);
    static void Onmouse2(int event, int x, int y, int, void *this_);
    void point_cloud_mapping( vector<Point> point_dect, vector<Point> &point_map, sl::Camera &);
    vector<int> bluenum;
    vector<int> rednum;
    vector<Point> bluemapping;
    vector<Point> redmapping;
    vector<Rect> maparea;
    Point2f choosePoints[4];
    Point2f choosePointsmap[4];
    bool ischosen = false;
    int clickTimes = 0;
    int clickTimesmap = 0;
    Mat framem;
    vector<vector<Point>> point_camera;
    vector<cv::Point> point_map;
    sl::Mat point_cloud;
    vector<Mat> warpmatrix; //透视变换矩阵
    vector<vector<Point2f>> SelectedPoints;
    sl::Pose cam_pose;
    int countedAreas = 0;
    String isContinue = "o";
    bool isClicked = false;
    bool isClicked2 = false;
    Mat RMMap;
    int map_height, map_width, camera_height, camera_width;
    float x_min, x_max; // show objects between [x_min; x_max] (in millimeters)
    float z_min;        // show objects between [z_min; 0] (z_min < 0) (in millimeters)

    // Conversion from world position to pixel coordinates
    float x_step, z_step;

    // window size
    int window_width, window_height;
};

#endif