#ifndef _GAMEINFO
#define _GAMEINFO
#include "../../../Referee/include/refereeio.h"
#include "../../../Parameter/include/Parameter.h"
#include <vector>
#pragma pack()
typedef struct
{
    int start;
    int RemainTime;
    int BuffAvailable;
    int RobotHP;
    int AFHP;
    int ASHP;
    int recover;
    int arecover;
    bool isRoad;
    bool inInvasion;
    int index;
    int Mtime;
    int isDangerZone;//偷家
    int SentryDensity;
    int EnermyToDead;
    bool sendToSentry;
    int AHP;
    int FHP;
    int SHP;
    int suggestion;
    vector<int> sendqueue;
    vector<int> showqueue;
    string herodecision;
    string engineerdecision;
    string infantrydecision;
    refereeio* judge;
} GameinfoDef;

extern GameinfoDef gameinfo;

typedef struct
{
    string hero;
    string infantry;
    string engineer;
    string sentry;
    string global;
} MessageDef;


#endif