#include "fileselect.h"
#include "ui_fileselect.h"

/**
 * @description: 文件选择窗口构造函数，看到on_xxxx_clicked一律是中断函数，不赘言
 * @param {QWidget} *parent
 * @return {*}
 */
FileSelect::FileSelect(QWidget *parent) : QDialog(parent),
                                          ui(new Ui::FileSelect)
{
    ui->setupUi(this);
    FileStorage fs("/home/robotlab/Radar_2021/Loadings/filepath.yml", FileStorage::READ);
    fs["DetectionCfg"] >> param.cfgfile;
    fs["DetectionWeight"] >> param.weightfile;
    fs["ClassifCfg"] >> param.cfcfgfile;
    fs["ClassifWeight"] >> param.cffile;
    fs["VideoPath"] >> param.videofile;
    fs["MapData"] >> param.mapdatafile;
    fs.release();
}

FileSelect::~FileSelect()
{
    delete ui;
}

void FileSelect::on_DCP_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Path"), QDir::currentPath());
    if (!path.isEmpty())
    {
        if (ui->DCFG->findText(path) == -1)
            ui->DCFG->addItem(path);
        ui->DCFG->setCurrentIndex(ui->DCFG->findText(path));
        param.cfgfile = path.toStdString();
    }
}

void FileSelect::on_DWP_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Path"), QDir::currentPath());
    if (!path.isEmpty())
    {
        if (ui->DWEI->findText(path) == -1)
            ui->DWEI->addItem(path);
        ui->DWEI->setCurrentIndex(ui->DWEI->findText(path));
        param.weightfile = path.toStdString();
    }
}

void FileSelect::on_CCP_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Path"), QDir::currentPath());
    if (!path.isEmpty())
    {
        if (ui->CCFG->findText(path) == -1)
            ui->CCFG->addItem(path);
        ui->CCFG->setCurrentIndex(ui->CCFG->findText(path));
        param.cfcfgfile = path.toStdString();
    }
}

void FileSelect::on_CWP_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Path"), QDir::currentPath());
    if (!path.isEmpty())
    {
        if (ui->CWEI->findText(path) == -1)
            ui->CWEI->addItem(path);
        ui->CWEI->setCurrentIndex(ui->CWEI->findText(path));
        param.cffile = path.toStdString();
    }
}

void FileSelect::on_VP_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Path"), QDir::currentPath());
    if (!path.isEmpty())
    {
        if (ui->VID->findText(path) == -1)
            ui->VID->addItem(path);
        ui->VID->setCurrentIndex(ui->VID->findText(path));
        param.videofile = path.toStdString();
    }
}

void FileSelect::on_MP_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Path"), QDir::currentPath());
    if (!path.isEmpty())
    {
        if (ui->MAPD->findText(path) == -1)
            ui->MAPD->addItem(path);
        ui->MAPD->setCurrentIndex(ui->MAPD->findText(path));
        param.mapdatafile = path.toStdString();
    }
}

void FileSelect::on_Apply_clicked()
{
    FileStorage fs("/home/robotlab/Radar_2021/Loadings/filepath.yml", FileStorage::WRITE);
    fs << "DetectionCfg" << param.cfgfile;
    fs << "DetectionWeight" << param.weightfile;
    fs << "ClassifCfg" << param.cfcfgfile;
    fs << "ClassifWeight" << param.cffile;
    fs << "VideoPath" << param.videofile;
    fs << "MapData" << param.mapdatafile;
    fs.release();
}
