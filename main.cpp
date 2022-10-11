#include <opencv2/opencv.hpp>
#include <sl/Camera.hpp>
#include <iostream>
#include "Parameter/include/Parameter.h"
#include "Modules/CarDetection/include/CarDetection.h"
#include "Modules/Mapping/include/Mapping.h"
#include "Modules/Preprocess/include/Preprocess.h"
#include "Modules/ZEDConfigure/include/ZEDConfigure.h"
#include "RMVideoCapture.h"
#include <opencv2/tracking.hpp>
#include "behaviortree_cpp_v3/bt_factory.h"
#include "Modules/BTree/include/Btree.h"
#include "Modules/BTree/include/GameStatus.h"
#include "Referee/include/refereeio.h"
using namespace cv;
using namespace BT;
#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>

//RegParam param = RegParam();

int main(int argc, char *argv[])
{
    //QT入口，在QT界面下的控制权交给mainwindow.cpp管理，main就退出了
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

//这个是调试代码

//定义变量 初始化变量
/*     Mat ZEDframe, SHORTframe, LONGframe, Camframe;
    Mat FframeZED, FframeSH, FframeLO, Firstframe;
    DetectionModel dect(param.weightfile, param.cfgfile);
    ClassificationModel classif(param.cffile, param.cfcfgfile);
    getClasses();
    loadModel(dect, classif);
    mapping map;
    map.mappingpre(param.mapdatafile, param.mapareafile);
    refereeio judge;
    BehaviorTreeFactory factory;
    Tree tree = init_BT(factory, judge);

    //ZED调试
    sl::Camera zed; */
    /* init(zed);
    Firstframe = getFrame(zed);

    //MindVision调试
    Ptr<VideoCapture> cap1;
    cap1 = (new RMVideoCapture());
    cap1->set(CAP_PROP_EXPOSURE, 10000); //设置曝光//
    cap1->set(CAP_PROP_GAIN, 100);
    cap1->read(Firstframe); */
/*     VideoWriter writer;
    CameraRecordinit(writer,Firstframe); */
    //读视频调试
    /*     VideoCapture cap;
    cap.open("/media//WD2/ZEDTS/12.avi");
    cap >> Firstframe;
 */
    /* char key = ' ';
    while (key != 'q')
    { */
        /* Camframe = getFrame(zed);
        cap1->read(Camframe); */

        //裁判系统等比赛开始

        // while(1){if(judge.referee.GameState.game_progress==4)break;};
       /*  while (1)
        {
            judge.readRefereeData();
            judge._PackToSentry.PackToSentry.CarDensityMax = 2;
            judge.writeToReferee(judge.referee.robot_client_ID.sentry);
        } */
        /* judge._PackToSentry.PackToSentry.carnum=2;
        judge.writeToReferee(judge.referee.robot_client_ID.sentry);
        judge._PackToSentry.PackToSentry.EnermyToDead=1;
        judge.writeToReferee(judge.referee.robot_client_ID.sentry); */

        /* cap >> Camframe;
        Mat result;
        Cardetection(Camframe, Firstframe, Camframe, dect, classif, map, zed,tree,judge,param.Side).copyTo(result);
        //返回的是地图
        imshow("result", result);
        waitKey(30);
        imshow("frame", Camframe);
        key = waitKey(30); */
        //Camframe=MOGProcess(Camframe);
        //NDProcess(Camframe);
        //Put efficiency information.
        /*std::vector<double> layersTimes;
        double freq = getTickFrequency() / 1000;
        double t = classif.getPerfProfile(layersTimes) / freq;
        auto fps = cap.get(5);
        std::string label = format("Inference time: %.2f ms; FPS: %.2f", t, fps);
        putText(Camframe, label, Point(0, 15), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));
        imshow("result", Camframe);*/
        // waitKey(30);
        //};
        //zed.disableRecording();
        //zed.close();
    //}
