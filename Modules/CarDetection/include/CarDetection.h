#ifndef CD
#define CD

#include <fstream>
#include "../../ZEDConfigure/include/ZEDConfigure.h"
#include <sl/Camera.hpp>
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
#include "../../Preprocess/include/Preprocess.h"
#include "../../Mapping/include/Mapping.h"
#include "../../BTree/include/Btree.h"
#include "../../BTree/include/GameStatus.h"
#include "../../../Referee/include/refereeio.h"
#include <opencv2/tracking.hpp>
#include <time.h>
#define TO_CVRect2d(ds_rect) Rect2d(ds_rect.x, ds_rect.y, ds_rect.width, ds_rect.height)
using namespace cv;
using namespace dnn;
using namespace std;
using namespace cv::cuda;


Mat Cardetection(Mat &, Mat &, Mat &,Mat &, DetectionModel &, ClassificationModel &, mapping &, sl::Camera &, Tree &, refereeio &, VideoWriter &,int side);
void drawDect(int classId, Rect box, Mat &frame);
bool if_ROI_suitable(Rect2d &Area, Mat &frame);
void multiTracker(Mat &, vector<Rect> &, vector<Rect2d> &,
                  vector<Ptr<Tracker>> &,
                  MultiTracker *&, bool &, bool &);
void CarTypeAssign(int *trackertype, float *trackerconf, int *cartypes, float *carconf, bool renew);
void CameraRecordinit(VideoWriter&,Mat &,int);
/* void DeepSort(Mat &, vector<Rect> &, vector<Rect2d> &,
              vector<float> &, vector<int> &,
              DS_Tracker &, bool &, bool &);
 */
//void NMSselect(vector<int> &classIds, vector<float> &confidences, vector<Rect> &boxes);
int ColorSelect(Mat& area);
void MotionDetect(Mat&,vector<Rect>&);
void MeshRect(vector<Rect>& dectbox,vector<Rect>& mogbox,vector<Rect>&finalboxes);

#endif