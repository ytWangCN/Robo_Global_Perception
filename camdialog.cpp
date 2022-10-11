#include "camdialog.h"
#include "ui_camdialog.h"

/**
 * @description: 相机参数调节窗口构造函数，带On_xxx_Clicked为中断函数
 * @param {QWidget} *parent
 * @return {*}
 */
CamDialog::CamDialog(QWidget *parent) : QDialog(parent),
                                        ui(new Ui::CamDialog)
{
    ui->setupUi(this);
    FileStorage fs(param.zedparamfile, FileStorage::READ);
    fs["gain"] >> ZEDgain;
    fs["exposure"] >> ZEDexposure;
    fs["gamma"] >> ZEDGamma;
    fs["brightness"] >> ZEDbrightness;
    fs["saturation"] >> ZEDSat;
    fs["contrast"] >> ZEDcontrast;
    fs["AEC_AGC"] >> ZEDaec_agc;
    fs.release();
    ui->Brightness->setValue(ZEDbrightness);
    ui->Gain->setValue(ZEDgain);
    ui->Exposure->setValue(ZEDexposure);
    ui->Contrast->setValue(ZEDcontrast);
    ui->Gamma->setValue(ZEDGamma);
    ui->Saturation->setValue(ZEDSat);
    connect(ui->AEC_AGC, SIGNAL(stateChanged(int)), this, SLOT(on_AEC_AGC_stateChanged(int)));
    connect(ui->Exposure, SIGNAL(valueChanged(int)), this, SLOT(on_Exposure_valueChanged(int)));
    connect(ui->Gain, SIGNAL(valueChanged(int)), this, SLOT(on_Gain_valueChanged(int)));
    connect(ui->Saturation, SIGNAL(valueChanged(int)), this, SLOT(on_Saturation_valueChanged(int)));
    connect(ui->Contrast, SIGNAL(valueChanged(int)), this, SLOT(on_Contrast_valueChanged(int)));
    connect(ui->Gamma, SIGNAL(valueChanged(int)), this, SLOT(on_Gamma_valueChanged(int)));
    connect(ui->Brightness, SIGNAL(valueChanged(int)), this, SLOT(on_Brightness_valueChanged(int)));
    connect(ui->APPLY, SIGNAL(clicked()), this, SLOT(on_APPLY_clicked()));
    connect(ui->CANCEL, SIGNAL(clicked()), this, SLOT(on_CANCEL_clicked()));
    init = false;
}

CamDialog::~CamDialog()
{
    delete ui;
}

void CamDialog::on_Exposure_valueChanged(int value)
{

    if (init == false)
    { /* zedc->setCameraSettings(sl::VIDEO_SETTINGS::EXPOSURE, value); */
        capc->set(CAP_PROP_EXPOSURE, value);
    }
}

void CamDialog::on_Gain_valueChanged(int value)
{

    if (init == false)
    {
        /* zedc->setCameraSettings(sl::VIDEO_SETTINGS::GAIN, value); */
        capc->set(CAP_PROP_GAIN, value);
    }
}

void CamDialog::on_Contrast_valueChanged(int value)
{

    if (init == false)
    {
        // zedc->setCameraSettings(sl::VIDEO_SETTINGS::CONTRAST, value);
        capc->set(CAP_PROP_CONTRAST, value);
    }
}

void CamDialog::on_Saturation_valueChanged(int value)
{

    if (init == false)
    {
        // zedc->setCameraSettings(sl::VIDEO_SETTINGS::SATURATION, value);
        capc->set(CAP_PROP_SATURATION, value);
    }
}

void CamDialog::on_Brightness_valueChanged(int value)
{

    if (init == false)
    {
        // zedc->setCameraSettings(sl::VIDEO_SETTINGS::BRIGHTNESS, value);
        capc->set(CAP_PROP_BRIGHTNESS, value);
    }
}

void CamDialog::on_Gamma_valueChanged(int value)
{

    if (init == false)
    {
        // zedc->setCameraSettings(sl::VIDEO_SETTINGS::GAMMA, value);
        capc->set(CAP_PROP_GAMMA, value);
    }
}

void CamDialog::on_APPLY_clicked()
{
    ZEDexposure = ui->Exposure->value();
    ZEDgain = ui->Gain->value();
    ZEDcontrast = ui->Contrast->value();
    ZEDSat = ui->Saturation->value();
    ZEDbrightness = ui->Brightness->value();
    ZEDGamma = ui->Gamma->value();
    ZEDaec_agc = ui->AEC_AGC->isChecked();
    FileStorage fs(param.zedparamfile, FileStorage::WRITE);
    fs << "gain" << ZEDgain;
    fs << "exposure" << ZEDexposure;
    fs << "gamma" << ZEDGamma;
    fs << "brightness" << ZEDbrightness;
    fs << "saturation" << ZEDSat;
    fs << "contrast" << ZEDcontrast;
    fs << "AEC_AGC" << ZEDaec_agc;
    fs.release();
}

void CamDialog::on_CANCEL_clicked()

{
    ui->Brightness->setValue(ZEDbrightness);
    ui->Gain->setValue(ZEDgain);
    ui->Exposure->setValue(ZEDexposure);
    ui->Contrast->setValue(ZEDcontrast);
    ui->Gamma->setValue(ZEDGamma);
    ui->Saturation->setValue(ZEDSat);
}

void CamDialog::on_AEC_AGC_stateChanged(int arg1)
{
    zedc->setCameraSettings(sl::VIDEO_SETTINGS::AEC_AGC, arg1);
    cout << arg1 << '\n';
}
