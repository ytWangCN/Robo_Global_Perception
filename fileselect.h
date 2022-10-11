#ifndef FILESELECT_H
#define FILESELECT_H

#include <QDialog>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "Parameter/include/Parameter.h"
#include "Modules/CarDetection/include/CarDetection.h"
#include "Modules/Mapping/include/Mapping.h"
#include "Modules/Preprocess/include/Preprocess.h"
#include "Referee/include/referee.h"
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
#include <QFileDialog>
using namespace cv;


namespace Ui {
class FileSelect;
}

class FileSelect : public QDialog
{
    Q_OBJECT

public:
    explicit FileSelect(QWidget *parent = nullptr);
    filepath* file;
    ~FileSelect();

private slots:
    void on_DCP_clicked();

    void on_DWP_clicked();

    void on_CCP_clicked();

    void on_CWP_clicked();

    void on_VP_clicked();

    void on_MP_clicked();

    void on_Apply_clicked();

private:
    Ui::FileSelect *ui;
};

#endif // FILESELECT_H
