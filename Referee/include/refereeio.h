#ifndef _REFEREE
#define _REFEREE

#include "referee.h"
#include "opencv2/opencv.hpp"
#include "../../Parameter/include/Parameter.h"
#include <vector>
using namespace cv;
class refereeio
{
public:
    //裁判系统类
    referee_Classdef referee;
    //通信包定义
    PackToGroundRobotUnionDef _PackToGroundRobot;
    PackToSentryUnionDef _PackToSentry;
    PackToGroundRobotStratUnionDef _PackToGroundRobotStrat;
    PackToEngineerUnionDef _PackToEngineer;
    PackToHeroUnionDef _PackToHero;
    PackToInfantryUnionDef _PackToInfantry;

    void writeToReferee(uint8_t Targetid);
    bool readRefereeData()  //读取裁判系统数据的IO口，读取之后直接读referee中对应成员值即可
    {
        const int LENGTH = 255;
        unsigned char read_buffer[LENGTH] = {0};
        ssize_t len_result = referee._SerialPort.read(read_buffer, LENGTH);
        referee.unPackDataFromRF(read_buffer, len_result);
        if (referee.GameState.game_progress != 15)
            return true;
        else
            return false;
    };
    void wrapMapData(vector<Point> &point_mapr, vector<Point> &point_mapb, vector<int> typer, vector<int> typeb, int side);
};
#endif