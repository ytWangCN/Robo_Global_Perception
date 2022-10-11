#include "include/CarDetection.h"
Mat Cardetection(Mat &frame, Mat &frameprev, Mat &Dectresult, Mat &DecisionDisplay, DetectionModel &dect, ClassificationModel &classif,
                 mapping &map, sl::Camera &zed, Tree &tree, refereeio &_judge, VideoWriter &writer, int side)
{
    Mat preprocessframe;
    Mat decision = Mat::zeros(308, 881, CV_8UC3);
    vector<int> cid;
    vector<float> conf;
    vector<Rect> dectboxes;
    vector<Rect> mogboxes;
    vector<Rect> boxes;
    vector<Point> PointResultsB;
    vector<Rect> RectangleResultsB;
    vector<Point> PointResultsR;
    vector<Rect> RectangleResultsR;
    vector<Point> bluecenterswithnum;
    vector<Point> redcenterswithnum;
    vector<Point> bluecenters;
    vector<Point> redcenters;
    static vector<Rect2d> trackboxes;
    static vector<Ptr<Tracker>> tracker;
    static MultiTracker *trackers;
    /*     static int trackertype[20] = {0};
    static float trackerconf[20] = {0}; */
    //DS_Tracker h_tracker = DS_Create();
    static bool isfirst = true;
    bool renew = false;
    //vector<int> cartypes;
    int cartypes[20] = {0};
    float carconf[20] = {0};
    //Mat frame;
    //preprocess(frame).copyTo(prep);
    //preprocessframe=MOGProcess(frame);

    //检测
    //dect.detect(frame, cid, conf, boxes, param.confThreshold, param.nmsThreshold);
    TickMeter tick;
    tick.reset();
    tick.start();
    dect.detect(frame, cid, conf, boxes, param.confThreshold, param.nmsThreshold);
    tick.stop();
    cout << tick.getTimeMilli() << '\n';
    /* MotionDetect(frame, mogboxes);
    MeshRect(dectboxes, mogboxes, boxes); */

    //cout << boxes.size() << '\n';
    //cout << boxes.size() << '\n';

    multiTracker(frame, boxes, trackboxes, tracker, trackers, renew, isfirst);

    //DeepSort(frame, boxes, trackboxes, conf, cid, h_tracker, renew, isfirst);

    for (size_t idx = 0; idx < trackboxes.size(); idx++)
    {
        if (if_ROI_suitable(trackboxes[idx], frame))
        {
            //Point center((int)trackboxes[idx].x + (trackboxes[idx].width * 0.5), trackboxes[idx].y + (trackboxes[idx].height / 2));
            Mat ROI = frame(trackboxes[idx]);
            classif.classify(ROI, cartypes[idx], carconf[idx]);
            //ColorSelect(ROI) == 0 ? cartypes.emplace_back(10) : cartypes.emplace_back(0);
        }
    };

    //CarTypeAssign(trackertype,trackerconf,carttrackerconfypes,carconf,renew);
    for (size_t idx = 0; idx < trackboxes.size(); idx++)
    {
        drawDect(cartypes[idx], trackboxes[idx], frame);
    }

    //地图
    Mat map_copy;
    map.RMMap.copyTo(map_copy);
    map.redmapping.clear();
    map.rednum.clear();
    map.bluemapping.clear();
    map.bluenum.clear();

    for (size_t idx = 0; idx < trackboxes.size(); idx++)
    {
        Point center(trackboxes[idx].x + (trackboxes[idx].width * 0.5), (int)trackboxes[idx].y + (trackboxes[idx].height * (0.5)));
        if (cartypes[idx] <= 4 && cartypes[idx] >= 0)
        {
            bluecenterswithnum.emplace_back(center);
            map.bluenum.emplace_back((cartypes[idx] + 1));
        }
        if (cartypes[idx] <= 14 && cartypes[idx] >= 10)
        {
            redcenterswithnum.emplace_back(center);
            map.rednum.emplace_back((cartypes[idx] - 9));
        }
    };
    //conventional color detect
    /* for (size_t idx = 0; idx < trackboxes.size(); idx++)
    {
        Point center(trackboxes[idx].x + (trackboxes[idx].width * 0.5), (int)trackboxes[idx].y + (trackboxes[idx].height * (0.875)));
        if (cartypes[idx] <= 4 && cartypes[idx] >= 0)
        {
            bluecenterswithnum.emplace_back(center);
            map.bluenum.emplace_back((cartypes[idx] + i));
            i++;
        }
        if (cartypes[idx] <= 14 && cartypes[idx] >= 10)
        {
            redcenterswithnum.emplace_back(center);
            map.rednum.emplace_back((cartypes[idx] - j));
            j--;
        }
    }; */
    map.mappingpost(bluecenterswithnum, map.bluemapping);
    map.mappingpost(redcenterswithnum, map.redmapping);
    //map.redmapping.emplace_back(Point(800,50));
    // bug in check within polygon
    if (!map.bluemapping.empty())
        map.drawmap(map.bluemapping, map.bluenum, false, map.bluenum.size(), map_copy);
    if (!map.redmapping.empty())
        map.drawmap(map.redmapping, map.rednum, true, map.rednum.size(), map_copy);
    //决策
    _judge.readRefereeData();
    //_judge.referee.robot_client_ID.local == 109 ? param.Side = 0 : param.Side = 1;
    param.Side = 1;
    gameinfo.start = 1;
    if (_judge.referee.robot_client_ID.local != 9 && _judge.referee.robot_client_ID.local != 109)
        gameinfo.start = 0;
    _judge.wrapMapData(map.redmapping, map.bluemapping, map.rednum, map.bluenum, side); //rbrb
    gameinfo.judge = &_judge;
    //gameinfo.showqueue.clear();
    dataProcess(side, map.redmapping, map.bluemapping);
    tree.tickRoot();
    printMessage(decision, map_copy);
    decision.copyTo(DecisionDisplay);
    cout << param.warningStatus << '\n';
    //输出
    resize(frame, frame, Size(871, 581));
    frame.copyTo(Dectresult);

    return map_copy;
};

void drawDect(int classId, Rect box, Mat &frame)
{
    rectangle(frame, box.tl(), box.br(), Scalar(0, 255, 0));
    std::string label;
    Point center(box.x + (box.width / 2), box.y + (box.height / 2));
    //std::string label = format("%.2f", conf);
    if (!param.carclasses.empty())
    {
        CV_Assert(classId < (int)param.carclasses.size());
        std::string labelpoint = format("(%.2i,%.2i)", center.x, center.y);
        label = param.carclasses[classId] + ": " + label; //+ labelpoint;
    };

    int baseLine;
    Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
    int top;
    top = max(box.tl().y, labelSize.height);
    rectangle(frame, Point(box.tl().x, top - labelSize.height),
              Point(box.tl().x + labelSize.width, top + baseLine), Scalar::all(255), FILLED);
    putText(frame, label, Point(box.tl().x, top), FONT_HERSHEY_SIMPLEX, 0.5, Scalar());
}

bool if_ROI_suitable(Rect2d &Area, Mat &frame)
{
    if (Area.x >= frame.size().width || Area.y >= frame.size().height || Area.width <= 0 || Area.height <= 0)
        return false;
    if (Area.x < 0)
    {
        Area.x = 0;
    }
    if (Area.y < 0)
    {
        Area.y = 0;
    }
    if (Area.x + Area.width >= frame.size().width)
    {
        Area.width = Area.width - (Area.x + Area.width - frame.size().width);
    }
    if (Area.y + Area.height >= frame.size().height)
    {
        Area.height = Area.height - (Area.y + Area.height - frame.size().height);
    }
    /* if (Area.x >= frame.size().width - 1000)
        return false;
    if (Area.y >= frame.size().height - 450)
        return false;*/
    return true;
}

void multiTracker(Mat &frame, vector<Rect> &boxes, vector<Rect2d> &trackboxes, vector<Ptr<Tracker>> &tracker, MultiTracker *&trackers, bool &renew, bool &isfirst)
{
    static int i;
    i++;
    if (boxes.size() == trackboxes.size())
    {
        for (size_t idx = 0; idx < trackboxes.size(); idx++)
        {
            if (sqrt((pow(boxes[idx].x - trackboxes[idx].x, 2) + pow(boxes[idx].y - trackboxes[idx].y, 2))) >= 30)
            {
                renew = true;
            }
        }
        for (size_t idx = 0; idx < trackboxes.size(); idx++)
        {
            if (trackboxes[idx].area() >= 2000)
            {
                renew = true;
            }
        }
    }; //delete far boxes.
    if (i % 100 == 0)
        renew = true;
    if (isfirst == true || renew == true || trackboxes.size() < boxes.size())
    {
        trackboxes.clear();
        tracker.clear();
        if (!isfirst)
        {
            delete trackers;
        }

        trackers = (new (MultiTracker));
        for (auto box : boxes)
        {
            //if(box.width*box.height >= 1000) continue;
            Rect2d tmp((double)box.x, (double)box.y, (double)box.width, (double)box.height);
            trackboxes.emplace_back(tmp);
        }

        for (size_t idx = 0; idx < trackboxes.size(); idx++)
        {
            Ptr<Tracker> tmp = TrackerMOSSE ::create();
            tracker.emplace_back(tmp);
        };
        trackers->add(tracker, frame, trackboxes);
        isfirst = false;
    }

    trackers->update(frame, trackboxes);
}

void CarTypeAssign(int *trackertype, float *trackerconf, int *cartypes, float *carconf, bool renew)
{
    if (renew == true)
    {
        for (int i = 0; i < 20; i++)
        {

            trackertype[i] = 0;
            trackerconf[i] = 0;
        };
    };
    for (int i = 0; i < 20; i++)
    {
        if (carconf[i] >= trackerconf[i])
        {
            trackertype[i] = cartypes[i];
            trackerconf[i] = carconf[i];
        }
    };
}

void CameraRecordinit(VideoWriter &writer, Mat &frame, int longshort)
{
    switch (longshort)
    {
    case 1:
    {
        time_t timep;
        time(&timep);
        char tmp[64];
        strftime(tmp, sizeof(tmp), "%Y-%m-%d-%H_%M_%S.avi", localtime(&timep));
        writer.open(tmp, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 25.0, Size(frame.cols, frame.rows), true);
        break;
    }
    case 2:
    {
        time_t timep;
        time(&timep);
        char tmp[64];
        strftime(tmp, sizeof(tmp), "long-%Y-%m-%d-%H_%M_%S.avi", localtime(&timep));
        writer.open(tmp, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 25.0, Size(frame.cols, frame.rows), true);
        break;
    }
    }
    //writer.open(tmp, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 25.0, Size(800, 600), true);
};
int ColorSelect(Mat &area)
{
    Mat tmp;
    area.copyTo(tmp);
    //cvtColor(area, area, COLOR_BGR2HSV_FULL);
    int tmpred = 0;
    int tmpblue = 0;
    for (int i = 0; i < tmp.rows; i++)
    {
        for (int j = 0; j < tmp.cols; j++)
        {
            int b = tmp.ptr<Vec3b>(i)[j][0];
            //int g = tmp.ptr<Vec3b>(i)[j][1];
            int r = tmp.ptr<Vec3b>(i)[j][2];
            /* if (s >= 43 && s <= 255 && v >= 46 && v <= 255)
            { */
            if (r > 130)
                tmpred++;
            else if (b > 130)
                tmpblue++;
            //}
        }
    }
    /* cout << "red" << '\n';
    cout << tmpred << '\n';
    cout << "blue" << '\n';
    cout << tmpblue << '\n'; */
    if (tmpred > tmpblue)
        return 0;
    else
        return 1;
}
void MotionDetect(Mat &frame, vector<Rect> &boxes)
{

    static int i = 0;
    vector<vector<Point>> contours;
    Mat tmp;
    MOGProcess(frame).copyTo(tmp);

    Mat element1 = getStructuringElement(MORPH_RECT, Size(11, 11));
    morphologyEx(tmp, tmp, MORPH_DILATE, element1);
    morphologyEx(tmp, tmp, MORPH_DILATE, element1);
    threshold(tmp, tmp, 30, 255, 0);

    findContours(tmp, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    for (auto contour : contours)
    {
        RotatedRect tmp = minAreaRect(contour);
        if (!(tmp.size.height * tmp.size.width <= 120 || i <= 20))
            boxes.emplace_back(tmp.boundingRect());
    }
    if (boxes.size() > 5)
        boxes.clear();

    i++;
}

void MeshRect(vector<Rect> &dectbox, vector<Rect> &mogbox, vector<Rect> &finalboxes)
{

    for (auto box : mogbox)
    {
        bool canp = true;
        for (auto dbox : dectbox)
        {
            if (sqrt((pow(dbox.x - box.x, 2) + pow(dbox.y - box.y, 2))) <= 10)
                canp = false;
            if (box.y >= 750)
                canp = false;
        }
        if (canp == true)
            finalboxes.emplace_back(box);
    }
    for (auto dbox : dectbox)
    {
        finalboxes.emplace_back(dbox);
    }
}
/* void DeepSort(Mat &frame, vector<Rect> &boxes, vector<Rect2d> &trackboxes, vector<float> &conf, vector<int> &cid, DS_Tracker &trackers, bool &renew, bool &isfirst)
{
    DS_DetectObjects detect_objects;
    static DS_TrackObjects track_objects;
    for (size_t idx = 0; idx < boxes.size(); idx++)
    {
        DS_Rect tmpr;
        tmpr.x = boxes[idx].x;
        tmpr.y = boxes[idx].y;
        tmpr.height = boxes[idx].height;
        tmpr.width = boxes[idx].width;
        DS_DetectObject tmp;
        tmp.rect = tmpr;
        tmp.class_id = cid[idx];
        tmp.confidence = conf[idx];
        detect_objects.emplace_back(tmp);
    }
    DS_Update(trackers, detect_objects, track_objects);
    for (auto track_object : track_objects)
    {
        trackboxes.emplace_back(TO_CVRect2d(track_object.rect));
    }
} */
/*void NMSselect(vector<int> &classIds, vector<float> &confidences, vector<Rect> &boxes)
{
    std::map<int, std::vector<size_t>> class2indices;
    for (size_t i = 0; i < classIds.size(); i++)
    {
        if (confidences[i] >= param.confThreshold)
        {
            class2indices[classIds[i]].push_back(i);
        }
    }
    std::vector<Rect> nmsBoxes;
    std::vector<float> nmsConfidences;
    std::vector<int> nmsClassIds;
    for (std::map<int, std::vector<size_t>>::iterator it = class2indices.begin(); it != class2indices.end(); ++it)
    {
        std::vector<Rect> localBoxes;
        std::vector<float> localConfidences;
        std::vector<size_t> classIndices = it->second;
        for (size_t i = 0; i < classIndices.size(); i++)
        {
            localBoxes.push_back(boxes[classIndices[i]]);
            localConfidences.push_back(confidences[classIndices[i]]);
        }
        std::vector<int> nmsIndices;
        NMSBoxes(localBoxes, localConfidences, param.confThreshold, param.nmsThreshold, nmsIndices);
        for (size_t i = 0; i < nmsIndices.size(); i++)
        {
            size_t idx = nmsIndices[i];
            nmsBoxes.push_back(localBoxes[idx]);
            nmsConfidences.push_back(localConfidences[idx]);
        }
    }
    boxes = nmsBoxes;
    classIds = nmsClassIds;
    confidences = nmsConfidences;
}*/

/* Archieved:这一段是传统和目标检测输入融合，后来不需要了 */

/*Mat mask = frameDiff(frame, frameprev);
    NDProcess(mask, frame, PointResultsB, RectangleResultsB, PointResultsR, RectangleResultsR);
    for (size_t idx = 0; idx < PointResultsB.size(); idx++)
    {
        for (size_t idb = 0; idb < boxes.size(); idb++)
        {
            if (!boxes[idb].contains(PointResultsB[idx]))
            {
                int type;
                float conf;
                Mat ROI = frame(RectangleResultsB[idx]);
                classif.classify(ROI, type, conf);
                if (type >= 10 && conf >= 0.7)
                {
                    bluecenterswithnum.emplace_back(PointResultsB[idx]);
                    bluenum.emplace_back((type - 9));
                }
                else
                {
                    bluecenters.emplace_back(PointResultsB[idx]);
                }
            }
        };
    };

    for (size_t idx = 0; idx < PointResultsR.size(); idx++)
    {
        for (size_t idb = 0; idb < boxes.size(); idb++)
        {
            if (!boxes[idb].contains(PointResultsR[idx]))
            {
                int type;
                float conf;
                Mat ROI = frame(RectangleResultsR[idx]);
                classif.classify(ROI, type, conf);
                if (type <= 4 && conf >= 0.7)
                {
                    redcenterswithnum.emplace_back(PointResultsR[idx]);
                    rednum.emplace_back((type + 1));
                }
                else
                {
                    redcenters.emplace_back(PointResultsR[idx]);
                }
            }
        };
    };

    for (size_t idx = 0; idx < boxes.size(); idx++)
    {
        Point center(boxes[idx].x + (boxes[idx].width / 2), boxes[idx].y + (boxes[idx].height / 2));
        Mat ROI = frame(boxes[idx]);
        classif.classify(ROI, cartypes[idx], carconf[idx]);
        if (cartypes[idx] <= 4 && carconf[idx] >= 0.7)
        {
            redcenterswithnum.emplace_back(center);
            rednum.emplace_back((cartypes[idx] + 1));
        }
        if (cartypes[idx] >= 10 && carconf[idx] >= 0.7)
        {
            bluecenterswithnum.emplace_back(center);
            bluenum.emplace_back((cartypes[idx] - 9));
        }
    };*/