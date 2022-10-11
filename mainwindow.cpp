#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextCodec>
#include <QAction>
#include <QImage>
RegParam param = RegParam();
using namespace cv;
DetectionModel dect(param.weightfile, param.cfgfile);
ClassificationModel classif(param.cffile, param.cfcfgfile);
/**
 * @description: 将cv::Mat转换为QImage进行前端显示，不用动
 * @param {Mat} &mat
 * @return {QImage} QImage
 */
QImage cvMat_to_QImage(const cv::Mat &mat)
{
    switch (mat.type())
    {
    // 8-bit, 4 channel
    case CV_8UC4:
    {
        QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB32);
        return image;
    }

    // 8-bit, 3 channel
    case CV_8UC3:
    {
        QImage image((const unsigned char *)(mat.data), mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    }

    // 8-bit, 1 channel
    case CV_8UC1:
    {
        static QVector<QRgb> sColorTable;
        // only create our color table once
        if (sColorTable.isEmpty())
        {
            for (int i = 0; i < 256; ++i)
                sColorTable.push_back(qRgb(i, i, i));
        }
        QImage image(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
        image.setColorTable(sColorTable);
        return image;
    }

    default:
        qDebug("Image format is not supported: depth=%d and %d channels\n", mat.depth(), mat.channels());
        break;
    }
    return QImage();
}

/**
 * @description: 主窗口初始化的构造函数
 * @param {QWidget} *parent
 * @return {*}
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /**开主窗口前弹3秒的提示标定窗口**/
    QMessageBox *m_box = new QMessageBox(QMessageBox::Information, QString("Note!"), QString("Did you Calibrate?"));
    QTimer::singleShot(3000, m_box, SLOT(accept()));
    m_box->exec();

    /**读颜色和比赛/调试状态**/
    FileStorage fs(param.gamestatefile, FileStorage::READ);
    int gamestate;
    fs["game"] >> gamestate;
    fs["side"] >> param.Side;
    fs.release();
    param.game = gamestate;

    /**设置信号与槽 主画面一个 长焦一个 地图显示一个 决策面板一个**/
    QSignalMapper *sm = new QSignalMapper(this);
    timerZED = new QTimer(this);
    timerLONG = new QTimer(this);
    timerMAP = new QTimer(this);
    timerDECISION = new QTimer(this);
    connect(timerZED, SIGNAL(timeout()), sm, SLOT(map()));
    connect(timerLONG, SIGNAL(timeout()), sm, SLOT(map()));
    connect(timerMAP, SIGNAL(timeout()), sm, SLOT(map()));
    connect(timerDECISION, SIGNAL(timeout()), sm, SLOT(map()));
    sm->setMapping(timerMAP, 1);
    sm->setMapping(timerLONG, 2);
    sm->setMapping(timerZED, 3);
    sm->setMapping(timerDECISION, 4);
    connect(sm, SIGNAL(mapped(int)), this, SLOT(display(int)));

    /**为了做文件路径选择界面而写的传递**/
    file.classifiercfg = param.cfcfgfile;
    file.classifierweight = param.cffile;
    file.detectcfg = param.cfgfile;
    file.detectweight = param.weightfile;
    file.mapdata = param.mapdatafile;
    file.video = param.videofile;

    getClasses();
    loadModel(dect, classif);
    tree = init_BT(factory, judge);
    map.mappingpre(param.mapdatafile, param.mapareafile);

    //如果比赛自动按按钮启动
    if (param.game == 1)
    {
        on_ZEDCAM_clicked();
        on_LONGCAM_clicked();
        on_MAP_clicked();
        on_DecisionB_clicked();
    }
}


/**
 * @description: 主窗口析构函数
 * @param {*}
 * @return {*}
 */
MainWindow::~MainWindow()
{

    writer.release();
    delete ui;
}

/**
 * @description: 几个Label的显示集合在此函数完成，用信号槽的映射关系完成函数参数的传递
 * @param {int} index
 * @return {*}
 */
void MainWindow::display(int index)
{
    switch (index)
    {
    case 1:  //绘制小地图
    {
        //检测主函数
        cv::Mat Map = Cardetection(ZEDframe, FframeZED, Dectresults, Decision, dect, classif, map, zed, tree, judge, writer, param.Side);
        //size是Label大小
        cv::resize(Map, Map, Size(881, 341));
        //转换与显示
        QImage img, img1;
        img = cvMat_to_QImage(Map);
        ui->Map->setPixmap(QPixmap::fromImage(img));
        ui->Map->show();

        //显示裁判系统连接状态，连接成功绿否则红
        if (gameinfo.start == 0)
            _REFSTA = Mat(71, 41, CV_8UC3, Scalar(0, 0, 255));
        else
            _REFSTA = Mat(71, 41, CV_8UC3, Scalar(0, 255, 0));
        img1 = cvMat_to_QImage(_REFSTA);
        ui->RefereeStatus->setPixmap(QPixmap::fromImage(img1));
        ui->RefereeStatus->show();
        break;
    }
    case 2:  //长焦显示
    {
        cap2->read(LONGframe);
        if (param.game == 1 && !LONGframe.empty())
        {
            //cv::resize(tmp, tmp, Size(800, 600));
            //putText(tmp, to_string(gameinfo.RemainTime), Point(10, 10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);
            writerl << LONGframe;
        }
        cv::resize(LONGframe, LONGframe, Size(871, 441));

        //这里主要是切换视角，在落矿时间将长焦放到大一点的显示区域，但后来修坏了
        if (gameinfo.Mtime != 1)
        {
            QImage img;
            img = cvMat_to_QImage(LONGframe);
            ui->LONG->setPixmap(QPixmap::fromImage(img));
            //ui->LONG->resize(ui->LONG->pixmap()->size());
            ui->LONG->show();
            break;
        }
        else
        {

            QImage img;
            img = cvMat_to_QImage(ZEDframe);
            ui->LONG->setPixmap(QPixmap::fromImage(img));
            //ui->LONG->resize(ui->LONG->pixmap()->size());
            ui->LONG->show();
            break;
        }
    case 3:  //主画面显示
    {
        cap1->read(ZEDframe);
        if (param.game == 1)
            rotate(ZEDframe, ZEDframe, ROTATE_180);
        if (param.game == 1 && !ZEDframe.empty())
        {
            Mat tmp;
            ZEDframe.copyTo(tmp);
            //cv::resize(tmp, tmp, Size(800, 600));
            putText(tmp, to_string(gameinfo.RemainTime), Point(10, 10), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255), 1);
            writer << tmp;
        }
        //ZEDframe = getFrame(zed);
        if (gameinfo.Mtime != 1)
        {
            QImage img;
            img = cvMat_to_QImage(ZEDframe);
            if (isDect)
                img = cvMat_to_QImage(Dectresults);
            ui->ZED->setPixmap(QPixmap::fromImage(img));
            //ui->ZED->resize(ui->ZED->pixmap()->size());
            ui->ZED->show();
        }
        else
        {
            QImage img;
            img = cvMat_to_QImage(LONGframe);
            ui->ZED->setPixmap(QPixmap::fromImage(img));
            //ui->ZED->resize(ui->ZED->pixmap()->size());
            ui->ZED->show();
        }
        break;
    }
    case 4:  //决策信息显示
    {
        QImage imgD;
        QImage imgW;
        imgD = cvMat_to_QImage(Decision);
        ui->Decision->setPixmap(QPixmap::fromImage(imgD));
        ui->Decision->show();
        if (param.warningStatus != -1)
        {
            imgW = cvMat_to_QImage(param.Warnings[param.warningStatus]);
            ui->Warning->setPixmap(QPixmap::fromImage(imgW));
            ui->Warning->show();
            break;
        }
        else
        {
            imgW = cvMat_to_QImage(param.Warnings[5]);
            ui->Warning->setPixmap(QPixmap::fromImage(imgW));
            ui->Warning->show();
            break;
        }
    }
    }
    }
}

/**
 * @description: ZEDCAM 按钮中断函数
 * @param {*}
 * @return {*}
 */
void MainWindow::on_ZEDCAM_clicked()
{

    if (param.game == 1)
    {
        cap1 = (new VideoCapture(0));
        cap1->read(FframeZED);
        if (FframeZED.empty())
            cap1 = (new VideoCapture(1));
    }
    else if (param.game == 0)
        cap1 = (new VideoCapture(param.videofile));
    cap1->set(CAP_PROP_FRAME_WIDTH, 1920.0);
    cap1->set(CAP_PROP_FRAME_HEIGHT, 2560.0);
    /*cap1->set(CAP_PROP_AUTO_EXPOSURE,false);
    cap1->set(CAP_PROP_EXPOSURE, 6000);*/
    cap1->read(FframeZED);
    if (param.game == 1)
        CameraRecordinit(writer, FframeZED, 1);
    ui->ZED->setScaledContents(true);
    timerZED->start(25);
}

/**
 * @description: LONGCAM 按钮中断函数
 * @param {*}
 * @return {*}
 */
void MainWindow::on_LONGCAM_clicked()
{
    cap2 = (new RMVideoCapture());
    cap2->set(CAP_PROP_EXPOSURE, 22297);
    cap2->set(CAP_PROP_GAIN, 10000);
    cap2->read(FframeLO);
    CameraRecordinit(writerl, FframeLO, 2);
    timerLONG->start(25);
}

/**
 * @description: MAP 按钮中断函数
 * @param {*}
 * @return {*}
 */
void MainWindow::on_MAP_clicked()
{
    timerMAP->start(25);
    isDect = true;
}

/**
 * @description: 相机参数设定 按钮中断函数
 * @param {*}
 * @return {*}
 */
void MainWindow::on_CamConf_clicked()
{
    dialog1 = new CamDialog(this);
    dialog1->zedc = &(zed);
    dialog1->capc = cap1;
    dialog1->caplc = cap2;
    dialog1->show();
}

/**
 * @description: 文件路径设定 按钮中断函数
 * @param {*}
 * @return {*}
 */
void MainWindow::on_ModelConf_clicked()
{
    fileselect = new FileSelect(this);
    fileselect->file = &(file);
    fileselect->show();
}

/**
 * @description: 比赛/调试 按钮中断函数
 * @param {*}
 * @return {*}
 */
void MainWindow::on_G_T_clicked()
{
    param.game == 1 ? param.game = 0 : param.game = 1;
    FileStorage fs(param.gamestatefile, FileStorage::WRITE);
    fs << "game" << param.game;
    fs << "side" << param.Side;
    fs.release();
}

/**
 * @description: 决策面板按钮中断函数
 * @param {*}
 * @return {*}
 */
void MainWindow::on_DecisionB_clicked()
{
    ui->Decision->setScaledContents(true);
    timerDECISION->start(25);
}
