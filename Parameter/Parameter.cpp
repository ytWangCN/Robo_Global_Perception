#include "include/Parameter.h"

RegParam::RegParam()
{
    //检测
    //yolov4的阈值和scale
    confThreshold = 0.25;
    nmsThreshold = 0.4;
    scale = 0.00392; //1/255
    //送进yolov4的图像
    inpWidth = 832;
    inpHeight = 832;
    classfile = "/home/robotlab/Radar_2021/Loadings/DetectionClasses.txt";
    weightfile = "/home/robotlab/Radar_2021/Loadings/yolov4-obj-608.weights";
    cfgfile = "/home/robotlab/Radar_2021/Loadings/yolov4-obj-608-now.cfg";

    //分类
    carclassfile = "/home/robotlab/Radar_2021/Loadings/CarClasses.txt";
    cffile = "/home/robotlab/Radar_2021/Loadings/efficientnet_b0_70000.weights";
    cfcfgfile = "/home/robotlab/Radar_2021/Loadings/efficientnet_b0.cfg";

    //地图
    mapfile = "/home/robotlab/Radar_2021/Loadings/battlefield.jpg";
    mapdatafile = "/home/robotlab/Radar_2021/Loadings/MappingCalib.yml";
    mapareafile = "/home/robotlab/Radar_2021/Loadings/MapArea.yml";

    //
    gamestatefile = "/home/robotlab/Radar_2021/Loadings/GameState.yml";
    zedparamfile = "/home/robotlab/Radar_2021/Loadings/ZEDParam.yml";
    btreefile = "/home/robotlab/Radar_2021/Loadings/BTnow.xml";
    //测试
    videofile = "/media/robotlab/WD/730/4.avi";

    param.Side = 1;//0 red 1 blue
    warningStatus = -1;
}

void getClasses()
{
    std::ifstream ifs(param.classfile);
    std::string line;
    while (std::getline(ifs, line))
    {
        param.classes.push_back(line);
    }
    std::ifstream ifcs(param.carclassfile);
    std::string carline;
    while (std::getline(ifcs, carline))
    {
        param.carclasses.push_back(carline);
    };
    Mat tmp;
    tmp = imread("/home/robotlab/Radar_2021/Loadings/Warnings/B.JPG");
    resize(tmp, tmp, Size(881, 381));
    param.Warnings.emplace_back(tmp);
    tmp = imread("/home/robotlab/Radar_2021/Loadings/Warnings/E.JPG");
    resize(tmp, tmp, Size(881, 381));
    param.Warnings.emplace_back(tmp);
    tmp = imread("/home/robotlab/Radar_2021/Loadings/Warnings/M.JPG");
    resize(tmp, tmp, Size(881, 381));
    param.Warnings.emplace_back(tmp);
    tmp = imread("/home/robotlab/Radar_2021/Loadings/Warnings/S.JPG");
    resize(tmp, tmp, Size(881, 381));
    param.Warnings.emplace_back(tmp);
    tmp = imread("/home/robotlab/Radar_2021/Loadings/Warnings/R.png");
    resize(tmp, tmp, Size(881, 381));
    param.Warnings.emplace_back(tmp);
    tmp = imread("/home/robotlab/Radar_2021/Loadings/Warnings/bg.jpeg");
    resize(tmp, tmp, Size(881, 381));
    param.Warnings.emplace_back(tmp);
}

void loadModel(DetectionModel &dect, ClassificationModel &classif)
{

    dect.setPreferableBackend(DNN_BACKEND_CUDA);
    dect.setPreferableTarget(DNN_TARGET_CUDA);
    dect.setInputSize(param.inpWidth, param.inpHeight); ///预处理，输入图像缩放
    dect.setInputSwapRB(true);                          ///RB通道数据交换
    dect.setInputCrop(false);
    dect.setInputScale(param.scale); ///输入数据归一化

    classif.setPreferableBackend(DNN_BACKEND_CUDA);
    classif.setPreferableTarget(DNN_TARGET_CUDA);
    classif.setInputSize(224, 224); ///预处理，输入图像缩放
    classif.setInputSwapRB(true);   ///RB通道数据交换
    classif.setInputCrop(false);
    classif.setInputScale(param.scale); ///输入数据归一化
};
