#ifndef CAMDIALOG_H
#define CAMDIALOG_H

#include <QDialog>
#include <opencv2/opencv.hpp>
#include <sl/Camera.hpp>
#include <iostream>
#include "Parameter/include/Parameter.h"
#include "Modules/CarDetection/include/CarDetection.h"
#include "Modules/Mapping/include/Mapping.h"
#include "Modules/Preprocess/include/Preprocess.h"
#include "Referee/include/refereeio.h"
#include "Modules/ZEDConfigure/include/ZEDConfigure.h"
/* #include "SerialPort/include/SerialPort.h" */
#include "RMVideoCapture.h"
#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QSignalMapper>
using namespace cv;

namespace Ui
{
    class CamDialog;
}

class CamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CamDialog(QWidget *parent = nullptr);
    ~CamDialog();
    int ZEDbrightness, ZEDcontrast, ZEDSat, ZEDGamma, ZEDgain, ZEDexposure, ZEDaec_agc;
    sl::Camera *zedc;
    VideoCapture *capc;
    VideoCapture *caplc;
    bool init = true;

private slots:

    void on_Exposure_valueChanged(int value);

    void on_Gain_valueChanged(int value);

    void on_Contrast_valueChanged(int value);

    void on_Saturation_valueChanged(int value);

    void on_Brightness_valueChanged(int value);

    void on_Gamma_valueChanged(int value);

    void on_APPLY_clicked();

    void on_CANCEL_clicked();

    void on_AEC_AGC_stateChanged(int arg1);

private:
    Ui::CamDialog *ui;
};

#endif // CAMDIALOG_H
