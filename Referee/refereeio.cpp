#include "include/refereeio.h"

/**
 * @description: 车间通信IO口，发的一个是地面兵种通用包，一个是各机器人专属包，
 * 包内容在SerialPort/include/DataStruct.h统一定义
 * @param {uint8_t} Targetid
 * @return {*}
 */
void refereeio::writeToReferee(uint8_t Targetid)
{
    /* this->_PackToReferee.PackToReferee.header = 0x66;
    this->_PackToReferee.PackToReferee.Flag = 0x71;
    this->_PackToReferee.PackToReferee.mapx =0x12;
    this->_PackToReferee.PackToReferee.Robot_id=0x23;
    this->_PackToReferee.PackToReferee.mapy=0x24;
    this->_PackToReferee.PackToReferee.event=0x25;
    this->_PackToReferee.PackToReferee.End=0x27; */

    if (Targetid == referee.robot_client_ID.sentry)
    {
        this->referee.CV_ToOtherRobot(Targetid, this->_PackToSentry.UsartData, sizeof(this->_PackToSentry.UsartData));
    }
    else if (Targetid == referee.robot_client_ID.hero)
    {
        this->referee.CV_ToOtherRobot(Targetid, this->_PackToGroundRobotStrat.UsartData, sizeof(this->_PackToGroundRobotStrat.UsartData));
        this->referee.CV_ToOtherRobot(Targetid, this->_PackToHero.UsartData, sizeof(this->_PackToHero.UsartData));
    }
    else if (Targetid == referee.robot_client_ID.infantry_3 || referee.robot_client_ID.infantry_4 || referee.robot_client_ID.infantry_5)
    {
        this->referee.CV_ToOtherRobot(Targetid, this->_PackToGroundRobotStrat.UsartData, sizeof(this->_PackToGroundRobotStrat.UsartData));
        this->referee.CV_ToOtherRobot(Targetid, this->_PackToInfantry.UsartData, sizeof(this->_PackToInfantry.UsartData));
    }
    else if (Targetid == referee.robot_client_ID.engineer)
    {
        this->referee.CV_ToOtherRobot(Targetid, this->_PackToGroundRobotStrat.UsartData, sizeof(this->_PackToGroundRobotStrat.UsartData));
        this->referee.CV_ToOtherRobot(Targetid, this->_PackToEngineer.UsartData, sizeof(this->_PackToEngineer.UsartData));
    }
};

/**
 * @description: 发送绘制小地图专属包IO口，包括颜色坐标编号，只能显示对方的坐标
 * @param {vector<Point>} &point_mapr, {vector<Point>} &point_mapb, {vector<int>} typer, {vector<int>} typeb
 * @param {int} side
 * @return {*}
 */
void refereeio::wrapMapData(vector<Point> &point_mapr, vector<Point> &point_mapb, vector<int> typer, vector<int> typeb, int side)
{
    switch (side)
    {
    case 1: //red
    {
        for (int i = 0; i < typer.size(); i++)
        {
            switch (typer[i])
            {
            case 1:
            {
                this->_PackToGroundRobot.PackToGroundRobot.R1x = point_mapr[i].x;
                this->_PackToGroundRobot.PackToGroundRobot.R1y = point_mapr[i].y;
                this->referee.Radar_dataTransmit(referee.robot_client_ID.hero, (float)(((point_mapr[i].x) / 1396.f) * 28.f), (float)(15.f - (((point_mapr[i].y) / 751.f) * 15.f)), .0f);
                //左下原点，m为单位
                break;
            }
            case 2:
            {
                this->_PackToGroundRobot.PackToGroundRobot.R2x = point_mapr[i].x;
                this->_PackToGroundRobot.PackToGroundRobot.R2y = point_mapr[i].y;
                this->referee.Radar_dataTransmit(referee.robot_client_ID.engineer, (float)(((point_mapr[i].x) / 1394.f) * 28.f), (float)(15.f - (((point_mapr[i].y) / 751.f) * 15.f)), .0f);
                break;
            }
            case 3:
            {
                this->_PackToGroundRobot.PackToGroundRobot.R3x = point_mapr[i].x;
                this->_PackToGroundRobot.PackToGroundRobot.R3y = point_mapr[i].y;
                this->referee.Radar_dataTransmit(referee.robot_client_ID.infantry_3, (float)(((point_mapr[i].x) / 1394.f) * 28.f), (float)(15.f - (((point_mapr[i].y) / 751.f) * 15.f)), .0f);
                break;
            }
            case 4:
            {
                this->_PackToGroundRobot.PackToGroundRobot.R4x = point_mapr[i].x;
                this->_PackToGroundRobot.PackToGroundRobot.R4y = point_mapr[i].y;
                this->referee.Radar_dataTransmit(referee.robot_client_ID.infantry_4, (float)(((point_mapr[i].x) / 1394.f) * 28.f), (float)(15.f - (((point_mapr[i].y) / 751.f) * 15.f)), .0f);
                break;
            }
            case 5:
            {
                this->_PackToGroundRobot.PackToGroundRobot.R5x = point_mapr[i].x;
                this->_PackToGroundRobot.PackToGroundRobot.R5y = point_mapr[i].y;
                this->referee.Radar_dataTransmit(referee.robot_client_ID.infantry_5, (float)(((point_mapr[i].x) / 1394.f) * 28.f), (float)(15.f - (((point_mapr[i].y) / 751.f) * 15.f)), .0f);
                break;
            }
            }
        }
    }
    case 0: //blue
    {
        for (int i = 0; i < typeb.size(); i++)
        {
            switch (typeb[i])
            {
            case 1:
            {
                this->_PackToGroundRobot.PackToGroundRobot.R1x = point_mapb[i].x;
                this->_PackToGroundRobot.PackToGroundRobot.R1y = point_mapb[i].y;
                this->referee.Radar_dataTransmit(referee.robot_client_ID.hero, (float)(-((((point_mapb[i].x) / 1396.f) * 28.f) - 28.f)), (float)(15.f - (((point_mapb[i].y) / 751.f) * 15.f)), .0f);
                //左下原点m为单位
                break;
            }
            case 2:
            {
                this->_PackToGroundRobot.PackToGroundRobot.R2x = point_mapb[i].x;
                this->_PackToGroundRobot.PackToGroundRobot.R2y = point_mapb[i].y;
                this->referee.Radar_dataTransmit(referee.robot_client_ID.engineer, (float)(-((((point_mapb[i].x) / 1396.f) * 28.f) - 28.f)), (float)(15.f - (((point_mapb[i].y) / 751.f) * 15.f)), .0f);
                break;
            }
            case 3:
            {
                this->_PackToGroundRobot.PackToGroundRobot.R3x = point_mapb[i].x;
                this->_PackToGroundRobot.PackToGroundRobot.R3y = point_mapb[i].y;
                this->referee.Radar_dataTransmit(referee.robot_client_ID.infantry_3, (float)(-((((point_mapb[i].x) / 1396.f) * 28.f) - 28.f)), (float)(15.f - (((point_mapb[i].y) / 751.f) * 15.f)), .0f);
                break;
            }
            case 4:
            {
                this->_PackToGroundRobot.PackToGroundRobot.R4x = point_mapb[i].x;
                this->_PackToGroundRobot.PackToGroundRobot.R4y = point_mapb[i].y;
                this->referee.Radar_dataTransmit(referee.robot_client_ID.infantry_4, (float)(-((((point_mapb[i].x) / 1396.f) * 28.f) - 28.f)), (float)(15.f - (((point_mapb[i].y) / 751.f) * 15.f)), .0f);
                break;
            }
            case 5:
            {
                this->_PackToGroundRobot.PackToGroundRobot.R5x = point_mapb[i].x;
                this->_PackToGroundRobot.PackToGroundRobot.R5y = point_mapb[i].y;
                this->referee.Radar_dataTransmit(referee.robot_client_ID.infantry_5, (float)(-((((point_mapb[i].x) / 1396.f) * 28.f) - 28.f)), (float)(15.f - (((point_mapb[i].y) / 751.f) * 15.f)), .0f);
                break;
            }
            }
        }
    }
    }
};
