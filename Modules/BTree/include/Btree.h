#ifndef _BT
#define _BT
#include "behaviortree_cpp_v3/bt_factory.h"
#include "../../../Referee/include/refereeio.h"

#include <iostream>
#include <bitset>

using namespace BT;
using namespace std;
// We want to be able to use this custom type


namespace BT
{
} // end namespace BT

Tree init_BT(BehaviorTreeFactory&,refereeio &);
void dataProcess(int, vector<Point> &red, vector<Point> &blue);
void messageselect();
int calcDensityandInvasion(int, vector<Point> &red, vector<Point> &blue);
void printMessage(Mat &, Mat &);
void showdecision();
void messageSelect();
#endif