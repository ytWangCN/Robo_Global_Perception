#include "include/Preprocess.h"

Mat MOGProcess(Mat &frame)
{
    GaussianBlur(frame, frame, Size(5,5),5);
    GpuMat d_frame(frame);
    GpuMat d_fgmask;
    GpuMat d_fgimg;
    GpuMat d_bgimg;

    Mat fgmask;
    Mat fgimg;
    Mat fgimg1;
    Mat bgimg;

    param.mog->apply(d_frame, d_fgmask, 0.01);
    d_fgimg.create(d_frame.size(), d_frame.type());
    d_fgimg.setTo(Scalar::all(0));
    d_frame.copyTo(d_fgimg, d_fgmask);

    d_fgmask.download(fgmask);
    d_fgimg.download(fgimg);

    Mat element = getStructuringElement(MORPH_RECT, Size(10, 10));

    morphologyEx(fgmask, fgmask, MORPH_OPEN, element);

    fgimg.copyTo(fgimg1, fgmask);

    /*imshow("foreground mask", fgmask);
    waitKey(10);*/
    //resize(frame, frame, Size(720, 540));

    return fgmask;
}

Mat frameDiff(Mat &frame, Mat &frameprev)
{

    Mat gray, grayprev, bg, fg, fgt, frame1;
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    cvtColor(frameprev, grayprev, COLOR_BGR2GRAY);
    absdiff(gray, grayprev, fg); //用帧差法求前景
    imshow("foreground", gray);
    Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
    GaussianBlur(fg, fg, Size(5, 5), 0);
    threshold(fg, fgt, 30, 255, 0); //二值化通常设置为50  255
    //threshold(foreground, foreground_BW, 0, 255 ,CV_THRESH_BINARY | CV_THRESH_OTSU) ;  //此处使用大津法  自适应取阈值

    //medianBlur(fgt, fgt, 3); //中值滤波法
    imshow("fgt", fgt);
    waitKey(10);
    dilate(fgt, fgt, element);
    dilate(fgt, fgt, element);
    dilate(fgt, fgt, element);
    erode(fgt, fgt, element);
    erode(fgt, fgt, element);
    erode(fgt, fgt, element);
    erode(fgt, fgt, element);
    frame.copyTo(frame1, fgt);
    imshow("gray_dilate1", frame1);
    waitKey(10);
    return fgt; //return a mask
}

void NDProcess(Mat &fgt, Mat &frame, vector<Point> &PointResultsB, vector<Rect> &RectangleresultsB, vector<Point> &PointResultsR, vector<Rect> &RectangleResultsR)
{
    vector<Point> PointResult;
    vector<Rect> Rectangleresult;
    Mat maskedframe, frameblue;
    frame.copyTo(maskedframe, fgt);
    vector<vector<Point>> contours; //存边界
    cvtColor(maskedframe, maskedframe, COLOR_BGR2GRAY);
    threshold(maskedframe, maskedframe, 30, 255, 0);
    findContours(maskedframe, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); //找边界
    for (auto contour : contours)
    {
        RotatedRect tmp = minAreaRect(contour);
        PointResult.emplace_back(tmp.center);
        Rectangleresult.emplace_back(tmp.boundingRect());
    }
    vector<Mat> imgchan;
    split(frame, imgchan); //分离颜色通道
    Mat dstblue = imgchan.at(0) - imgchan.at(2);
    for (size_t i = 0; i < Rectangleresult.size(); i++)
    {
        Mat Standard(Rectangleresult[i].height, Rectangleresult[i].width, CV_8UC1, Scalar(0));
        Mat ROIblue = dstblue(Rectangleresult[i]);
        Mat SHist, RHist;
        int Channels[] = {0};
        int nHistSize[] = {5};
        float range[] = {0, 70, 100, 120, 200, 255}; // 数组中又nHistSize[0] + 1个元素
        const float *fHistRanges[] = {range};
        // 计算直方图,uniform = false
        calcHist(&Standard, 1, Channels, Mat(), SHist, 1, nHistSize, fHistRanges, false, false);
        calcHist(&ROIblue, 1, Channels, Mat(), RHist, 1, nHistSize, fHistRanges, false, false);
        double compare = compareHist(SHist, RHist, HISTCMP_BHATTACHARYYA);
        if (compare == 0.0)
        {
            RectangleResultsR.emplace_back(Rectangleresult[i]);
            PointResultsR.emplace_back(PointResult[i]);
        }
        else
        {
            RectangleresultsB.emplace_back(Rectangleresult[i]);
            PointResultsB.emplace_back(PointResult[i]);
        }
    }

    //frame.copyTo(frameblue, fgt);
    //blue
    /*vector<Mat> imgchanB;
    split(frameblue, imgchanB); //分离颜色通道
    Mat dstblue = imgchanB.at(0) - imgchanB.at(2);

    vector<vector<Point>> contoursblue; //存边界
    cvtColor(frameblue, frameblue, COLOR_BGR2GRAY);
    threshold(frameblue, frameblue, 30, 255, 0);
    findContours(frameblue, contoursblue, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); //找边界
    for (auto contour : contoursblue)
    {
        RotatedRect tmp = fitEllipse(contour);
        PointResultsB.emplace_back(tmp.center);
        RectangleresultB.emplace_back(tmp.boundingRect());
    }

    vector<Mat> imgchanR;
    split(frameblue, imgchanR); //分离颜色通道
    Mat dstblue = imgchanR.at(0) - imgchanR.at(2);
    vector<vector<Point>> contoursred; //存边界
    cvtColor(framered, framered, COLOR_BGR2GRAY);
    threshold(framered, framered, 30, 255, 0);
    findContours(framered, contoursred, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE); //找边界
    for (auto contour : contoursred)
    {
        RotatedRect tmp = fitEllipse(contour);
        PointResultsR.emplace_back(tmp.center);
        RectangleResultsR.emplace_back(tmp.boundingRect());
    }
*/

    waitKey(10);
}