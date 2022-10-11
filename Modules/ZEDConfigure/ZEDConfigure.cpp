
#include "include/ZEDConfigure.h"

//注意sl::和cv::同名的混淆！！

void init(sl::Camera &zed)
{
    sl::InitParameters init_parameters;
    init_parameters.camera_resolution = sl::RESOLUTION::HD1080; // Use HD1080 video mode
    init_parameters.camera_fps = 30;                            // Set fps at 30
    init_parameters.coordinate_units = sl::UNIT::MILLIMETER;
    init_parameters.depth_mode = sl::DEPTH_MODE::ULTRA;
    init_parameters.sdk_verbose = true;
    init_parameters.depth_maximum_distance = 18.0f * 1000.0f;
    init_parameters.coordinate_system = sl::COORDINATE_SYSTEM::RIGHT_HANDED_Y_UP;
    // Open the camera
    auto returned_state = zed.open(init_parameters);
    if (returned_state != sl::ERROR_CODE::SUCCESS)
    {
        cout << "Error " << returned_state << ", exit program." << endl;
    }
    auto camera_config = zed.getCameraInformation().camera_configuration;

    sl::PositionalTrackingParameters positional_tracking_parameters;
    // If the camera is static in space, enabling this settings below provides better depth quality and faster computation
    positional_tracking_parameters.set_as_static = true;
    zed.enablePositionalTracking(positional_tracking_parameters);

    time_t timep;
    time(&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d-%H_%M_%S.svo", localtime(&timep));
    sl::String path(tmp);
    zed.enableRecording(sl::RecordingParameters(path, sl::SVO_COMPRESSION_MODE::H264));
    // enable Positional Tracking
    //zed.enablePositionalTracking(tracking_param);
}

cv::Mat getFrame(sl::Camera &zed)
{
    zed.grab();
    sl::Mat zed_image;
    zed.retrieveImage(zed_image, sl::VIEW::LEFT);
    // Convert sl::Mat to cv::Mat (share buffer)
    cv::Mat cvImage = cv::Mat((int)zed_image.getHeight(), (int)zed_image.getWidth(), CV_8UC4, zed_image.getPtr<sl::uchar1>(sl::MEM::CPU));
    Mat cvImage3C;
    cvtColor(cvImage, cvImage3C, COLOR_RGBA2RGB);
    cvtColor(cvImage3C, cvImage3C, COLOR_RGB2BGR);
    return cvImage3C;
}

void getDepth(sl::Camera &zed, sl::Mat &point_cloud)
{
    auto camera_config = zed.getCameraInformation().camera_configuration;
    sl::RuntimeParameters runParameters;
    // Setting the depth confidence parameters
    runParameters.confidence_threshold = 100;
    runParameters.texture_confidence_threshold = 100;
    runParameters.measure3D_reference_frame = sl::REFERENCE_FRAME::WORLD;
    sl::Resolution pc_resolution(min((int)camera_config.resolution.width, 720), min((int)camera_config.resolution.height, 404));
    // Allocation of 4 channels of float on GPU
    if (zed.grab(runParameters) == sl::ERROR_CODE::SUCCESS)
    {
        zed.retrieveMeasure(point_cloud, sl::MEASURE::XYZ, sl::MEM::GPU, pc_resolution);
    }
    //point_cloud.free();
}

void ROI_AEC(sl::Camera &zed, sl::Rect Area)
{
    zed.setCameraSettings(sl::VIDEO_SETTINGS::AEC_AGC_ROI, Area, sl::SIDE::BOTH);
}
void zedclose(sl::Camera &zed)
{
    zed.close();
}
