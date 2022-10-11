#include "include/Btree.h"
#include "include/GameStatus.h"
#include <string>
static MessageDef message;
void showdecision(){
    // switch(gameinfo.showqueue)
};

void printMessage(Mat &img, Mat &frame)
{
    gameinfo.judge->readRefereeData();
    messageSelect();
    //决策信息
    putText(img, "Global", Point(0, 40), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 1);
    putText(img, "Hero", Point(0, 80), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 1);
    putText(img, "Infantry", Point(0, 120), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 1);
    putText(img, "Engineer", Point(0, 160), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 1);
    putText(img, "Sentry", Point(0, 200), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 1);

    putText(img, message.global, Point(160, 40), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 1);
    putText(img, message.hero, Point(160, 80), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 1);
    putText(img, message.infantry, Point(160, 120), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 1);
    putText(img, message.engineer, Point(160, 160), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 1);
    putText(img, message.sentry, Point(160, 200), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 1);

    switch (gameinfo.index)
    {
    case 4:
        param.warningStatus = 2;
        break;
    case 5:
        param.warningStatus = 2;
        break;
    case 7:
        param.warningStatus = 1;
        break;
    case 9:
        param.warningStatus = 3;
        break;
    case 12:
        param.warningStatus = 0;
        break;
    case 13:
        param.warningStatus = 4;
        break;
    default:
        param.warningStatus = -1;
        break;
    }
}

void messageSelect()
{
    switch (gameinfo.index)
    {
    case 1:
    {
        message.engineer = "Protect Outpost";
        message.hero = "Attack Outpost";
        message.infantry = "Defend";
        break;
    }
    case 2:
    {
        message.engineer = "Protect Outpost";
        message.hero = "Attack Outpost";
        message.infantry = "Attack Sentry";
        break;
    }
    case 3:
    {
        message.engineer = "None";
        message.hero = "Grasp Blood!";
        message.infantry = "Grasp Blood!";
        break;
    }
    case 4:
    {
        message.engineer = "1MINERAL";
        break;
    }
    case 5:
    {
        message.engineer = "2MINERAL";
        break;
    }
    case 6:
    {
        message.global = "Missile Launch";
        break;
    }

    case 7:
    {
        message.global = "BASE!!";
        break;
    }
    case 8:
    {
        message.global = "HEROLOW";
        break;
    }
    case 9:
    {
        message.global = "SENLOW";
        break;
    }
    case 10:
    {
        message.global = "OUTLOW";
        break;
    }
    case 11:
    {
        message.global = "EHEROLOW";
        break;
    }
    case 12:
    {
        message.global = "BUFF";
        break;
    }
    case 13:
    {
        message.global = "E ON ROAD";
        break;
    }
    }
}