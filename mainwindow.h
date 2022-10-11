/*
 * @Author: your name
 * @Date: 2021-08-25 07:31:57
 * @LastEditTime: 2021-08-25 12:04:33
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \Desktop\Radar_2021\mainwindow.h
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
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
#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QSignalMapper>
#include "ui_mainwindow.h"
#include "camdialog.h"
#include "fileselect.h"
using namespace cv;
using namespace BT;
QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    sl::Camera zed;
    Ptr<VideoCapture> cap1;
    Ptr<VideoCapture> cap2;
    Mat ZEDframe, SHORTframe, LONGframe, MAP;
    Mat FframeZED, FframeSH, FframeLO;
    Mat _REFSTA;
    Mat Dectresults,Decision;
    bool isDect = false;
    mapping map;
    QTimer *timerZED;
    QTimer *timerDECISION;
    QTimer *timerLONG;
    QTimer *timerMAP;
    filepath file;
    refereeio judge;
    BehaviorTreeFactory factory;
    Tree tree;
    VideoWriter writer,writerl;
private slots:
    void on_ZEDCAM_clicked();

    void on_LONGCAM_clicked();

    void on_MAP_clicked();
    void on_CamConf_clicked();
    void display(int);

    void on_ModelConf_clicked();

    void on_G_T_clicked();

    void on_DecisionB_clicked();

public:
    Ui::MainWindow *ui;

private:
    QAction *openAction;
    CamDialog *dialog1;
    FileSelect *fileselect;
};
#endif // MAINWINDOW_H
