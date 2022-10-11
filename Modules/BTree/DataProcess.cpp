#include "include/Btree.h"
#include "include/GameStatus.h"

void dataProcess(int Color, vector<Point> &red, vector<Point> &blue)
{
    (gameinfo.judge)->readRefereeData();
    switch (Color)
    {
    case 0:
        gameinfo.FHP = (gameinfo.judge)->referee.GameRobotHP.blue_outpost_HP;
        gameinfo.SHP = gameinfo.RemainTime = (gameinfo.judge)->referee.GameRobotHP.blue_7_robot_HP;
        //protect
        if (gameinfo.judge->referee.GameRobotHP.red_1_robot_HP < 500)
        {
            gameinfo.RobotHP = 1;
            gameinfo.judge->_PackToGroundRobotStrat.PackToGroundRobotStrat.protect = 0x01;
        }
        else if (gameinfo.judge->referee.GameRobotHP.red_1_robot_HP > 600)
        {
            gameinfo.recover = 1;
        }
        //attack
        /* if (gameinfo.judge->referee.GameRobotHP.blue_1_robot_HP < 500)
        {
            gameinfo.AHP = 1;
            gameinfo.judge->_PackToGroundRobotStrat.PackToGroundRobotStrat.attack = 0x01;
        }
        else if (gameinfo.judge->referee.GameRobotHP.blue_1_robot_HP > 600)
        {
            gameinfo.arecover = 1;
        } */
        break;
    case 1:
        gameinfo.FHP = (gameinfo.judge)->referee.GameRobotHP.red_outpost_HP;
        gameinfo.SHP = gameinfo.RemainTime = (gameinfo.judge)->referee.GameRobotHP.red_7_robot_HP;
        //protect
        if (gameinfo.judge->referee.GameRobotHP.blue_1_robot_HP < 500)
        {
            gameinfo.RobotHP = 1;
            gameinfo.judge->_PackToGroundRobotStrat.PackToGroundRobotStrat.protect = 0x01;
        }
        else if (gameinfo.judge->referee.GameRobotHP.blue_1_robot_HP > 600)
        {
            gameinfo.recover = 1;
        }
        //attack
        /* if (gameinfo.judge->referee.GameRobotHP.red_1_robot_HP < 500)
        {
            gameinfo.AHP = 1;
            gameinfo.judge->_PackToGroundRobotStrat.PackToGroundRobotStrat.attack = 0x01;
        }
        else if (gameinfo.judge->referee.GameRobotHP.red_1_robot_HP > 600)
        {
            gameinfo.arecover = 1;
        } */
        break;
    }
    gameinfo.RemainTime = (gameinfo.judge)->referee.GameState.stage_remain_time;
    bitset<32> event((gameinfo.judge)->referee.EventData.event_type);
    gameinfo.BuffAvailable = 0;
    if ((gameinfo.RemainTime <= 385 && gameinfo.RemainTime >= 380) || (gameinfo.RemainTime <= 305 && gameinfo.RemainTime >= 300) || (gameinfo.RemainTime <= 125 && gameinfo.RemainTime >= 120))
        gameinfo.BuffAvailable = 1;
    //Sentry Process
    (gameinfo.judge)->_PackToSentry.PackToSentry.CarDensityMax = calcDensityandInvasion(Color, red, blue);
    /*     if ((gameinfo.judge)->_PackToSentry.PackToSentry.CarDensityMax != -1)
        gameinfo.sendToSentry = true; */
    /* if ((gameinfo.judge)->_PackToSentry.PackToSentry.CarDensityMax != -1)
    {
        //gameinfo.judge->writeToReferee((gameinfo.judge)->referee.robot_client_ID.sentry);
        // gameinfo.sendToSentry = false;
    }; */
};

void messageselect()
{
    switch (gameinfo.index)
    {
    case 1:
    {
        gameinfo.judge->_PackToEngineer.PackToEngineer.suggestion = 0x01;
        gameinfo.judge->_PackToHero.PackToHero.suggestion = 0x02;
        gameinfo.judge->_PackToInfantry.PackToInfantry.suggestion = 0x04;
        break;
    }
    case 2:
    {
        gameinfo.judge->_PackToEngineer.PackToEngineer.suggestion = 0x01;
        gameinfo.judge->_PackToHero.PackToHero.suggestion = 0x02;
        gameinfo.judge->_PackToInfantry.PackToInfantry.suggestion = 0x02;
        break;
    }
    case 3:
    {
        gameinfo.judge->_PackToEngineer.PackToEngineer.suggestion = 0x00;
        gameinfo.judge->_PackToHero.PackToHero.suggestion = 0x04;
        gameinfo.judge->_PackToInfantry.PackToInfantry.suggestion = 0x08;
        break;
    }
    case 4:
    {
        gameinfo.judge->_PackToEngineer.PackToEngineer.suggestion = 0x02;
        break;
        /*         gameinfo.judge->_PackToHero.PackToHero.suggestion = 0x02;
        gameinfo.judge->_PackToInfantry.PackToInfantry.suggestion = 0x04; */
    }
    case 5:
    {
        gameinfo.judge->_PackToEngineer.PackToEngineer.suggestion = 0x02;
        break;
        /*         gameinfo.judge->_PackToHero.PackToHero.suggestion = 0x02;
        gameinfo.judge->_PackToInfantry.PackToInfantry.suggestion = 0x04; */
    }
    case 6:
    {
        gameinfo.judge->_PackToGroundRobotStrat.PackToGroundRobotStrat.event = 0x04;
        break;
    }

    case 7:
    {
        gameinfo.judge->_PackToGroundRobotStrat.PackToGroundRobotStrat.event = 0x08;
        break;
    }
    case 8:
    {
        gameinfo.judge->_PackToEngineer.PackToEngineer.suggestion = 0x02;
        gameinfo.judge->_PackToHero.PackToHero.suggestion = 0x02;
        gameinfo.judge->_PackToInfantry.PackToInfantry.suggestion = 0x04;
        break;
    }
    case 9:
    {
        gameinfo.judge->_PackToGroundRobotStrat.PackToGroundRobotStrat.event = 0x02;
        break;
    }
    case 10:
    {
        gameinfo.judge->_PackToGroundRobotStrat.PackToGroundRobotStrat.event = 0x01;
        break;
    }
    case 11:
    {
        gameinfo.judge->_PackToEngineer.PackToEngineer.suggestion = 0x02;
        gameinfo.judge->_PackToHero.PackToHero.suggestion = 0x02;
        gameinfo.judge->_PackToInfantry.PackToInfantry.suggestion = 0x04;
        break;
    }
    case 12:
    {
        gameinfo.judge->_PackToInfantry.PackToInfantry.suggestion = 0x01;
        break;
    }
    };
}

int calcDensityandInvasion(int Color, vector<Point> &red, vector<Point> &blue)
{
    Rect home = Rect(Point(0, 0), Point(251, 750));
    Rect road = Rect(Point(459, 0), Point(1109, 61));
    gameinfo.inInvasion = false;
    gameinfo.isRoad = false;
    if (Color == 0)
    { //0==red
        for (auto b : blue)
        {
            if (home.contains(b))
                gameinfo.inInvasion = true;
            if (road.contains(b))
                gameinfo.isRoad = true;
        }
    }
    if (Color == 1)
    { //1==blue
        for (auto r : red)
        {
            if (home.contains(r))
                gameinfo.inInvasion = true;
            if (road.contains(r))
                gameinfo.isRoad = true;
        }
    }
    return 0;

    /* vector<cv::Point2f> red;
    vector<cv::Point2f> blue;
    vector<Rect> areared;
    vector<Rect> areablue;
    int area[6] = {0};
    areared.emplace_back(Rect(Point(542, 460), Point(688, 509)));
    areared.emplace_back(Rect(Point(542, 411), Point(688, 460)));
    areared.emplace_back(Rect(Point(542, 362), Point(688, 411)));
    areared.emplace_back(Rect(Point(542, 314), Point(688, 362)));
    areared.emplace_back(Rect(Point(264, 378), Point(465, 795)));
    areared.emplace_back(Rect(Point(264, 38), Point(465, 378)));
    areablue.emplace_back(Rect(Point(1238, 314), Point(1381, 363)));
    areablue.emplace_back(Rect(Point(1238, 363), Point(1381, 412)));
    areablue.emplace_back(Rect(Point(1238, 412), Point(1381, 461)));
    areablue.emplace_back(Rect(Point(1238, 461), Point(1381, 510)));
    areablue.emplace_back(Rect(Point(1449, 38), Point(1658, 373)));
    areablue.emplace_back(Rect(Point(1449, 373), Point(1658, 784))); //按小地图坐标尺，可能需要放缩)！
    red.emplace_back(cv::Point2f(((gameinfo.judge)->_PackToGroundRobot.PackToGroundRobot.R1x), ((gameinfo.judge)->_PackToGroundRobot.PackToGroundRobot.R1y)));
    red.emplace_back(cv::Point2f(((gameinfo.judge)->_PackToGroundRobot.PackToGroundRobot.R2x), ((gameinfo.judge)->_PackToGroundRobot.PackToGroundRobot.R2y)));
    red.emplace_back(cv::Point2f(((gameinfo.judge)->_PackToGroundRobot.PackToGroundRobot.R3x), ((gameinfo.judge)->_PackToGroundRobot.PackToGroundRobot.R3y)));
    red.emplace_back(cv::Point2f(((gameinfo.judge)->_PackToGroundRobot.PackToGroundRobot.R4x), ((gameinfo.judge)->_PackToGroundRobot.PackToGroundRobot.R4y)));
    red.emplace_back(cv::Point2f(((gameinfo.judge)->_PackToGroundRobot.PackToGroundRobot.R5x), ((gameinfo.judge)->_PackToGroundRobot.PackToGroundRobot.R5y)));
    blue.emplace_back(cv::Point2f(((gameinfo.judge)->_PackToGroundRobot.PackToGroundRobot.B1x), ((gameinfo.judge)->_PackToGroundRobot.PackToGroundRobot.B1y)));
    blue.emplace_back(cv::Point2f(((gameinfo.judge)->_PackToGroundRobot.PackToGroundRobot.B2x), ((gameinfo.judge)->_PackToGroundRobot.PackToGroundRobot.B2y)));
    blue.emplace_back(cv::Point2f(((gameinfo.judge)->_PackToGroundRobot.PackToGroundRobot.B3x), ((gameinfo.judge)->_PackToGroundRobot.PackToGroundRobot.B3y)));
    blue.emplace_back(cv::Point2f(((gameinfo.judge)->_PackToGroundRobot.PackToGroundRobot.B4x), ((gameinfo.judge)->_PackToGroundRobot.PackToGroundRobot.B4y)));
    blue.emplace_back(cv::Point2f(((gameinfo.judge)->_PackToGroundRobot.PackToGroundRobot.B5x), ((gameinfo.judge)->_PackToGroundRobot.PackToGroundRobot.B5y)));
    if (Color == 0)
    { //0==red
        for (auto b : blue)
        {
            for (auto idx = 0; idx <= 5; idx++)
            {
                if (areared[idx].contains(b))
                    area[idx]++;
                if ((idx == 5 || idx == 6) && areared[idx].contains(b))
                {
                    gameinfo.inInvasion = true;
                    gameinfo.judge->_PackToSentry.PackToSentry.carnum++;
                }
            }
        }
    }
    if (Color == 1)
    { //1==blue
        for (auto r : red)
        {
            for (auto idx = 0; idx <= 5; idx++)
            {
                if (areablue[idx].contains(r))
                    area[idx]++;
                if ((idx == 5 || idx == 6) && areablue[idx].contains(r))
                {
                    gameinfo.inInvasion = true;
                    gameinfo.judge->_PackToSentry.PackToSentry.carnum++;
                }
            }
        }
    }
    int max = 0;
    int maxid = 0;
    for (auto idx = 0; idx <= 5; idx++)
    {
        if (area[idx] > max)
        {
            max = area[idx];
            maxid = idx;
        }
    }
    if (max == 0)
        return -1;
    return maxid + 1; */
}
