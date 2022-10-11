#include "include/Mapping.h"

bool mapping::isPointInRect(int x, int y, vector<Point> choosePoints)
{ //判断是否在矩形框内
    //四个点要顺时针排列
    Point A = choosePoints[0];
    Point B = choosePoints[1];
    Point C = choosePoints[3];
    Point D = choosePoints[2];
    int a = (B.x - A.x) * (y - A.y) - (B.y - A.y) * (x - A.x);
    int b = (C.x - B.x) * (y - B.y) - (C.y - B.y) * (x - B.x);
    int c = (D.x - C.x) * (y - C.y) - (D.y - C.y) * (x - C.x);
    int d = (A.x - D.x) * (y - D.y) - (A.y - D.y) * (x - D.x);
    if ((a > 0 && b > 0 && c > 0 && d > 0) || (a < 0 && b < 0 && c < 0 && d < 0))
    {
        return true;
    }

    return false;
}

mapping::mapping()
{
    mappingpre(param.mapdatafile, param.mapareafile);
    this->RMMap = imread(param.mapfile);
    //cv::cvtColor(this->RMMap,this->RMMap,COLOR_BGR2GRAY);
    /*cam_pose.pose_data.setIdentity();

    // invert Z due to Y axis of ocv windows
    z_min = -18.0f * 1000.0f;
    x_min = z_min / 2.0f;
    x_max = -x_min;
    //conversion
    x_step = (x_max - x_min) /748;
    z_step = abs(z_min) / 898;//pixel map size longest 18m */
}
void mapping::mappingpre(cv::String file, cv::String filea)
{
    FileStorage fs(file, FileStorage::READ);
    fs["Camera_height"] >> camera_height;
    fs["Camera_width"] >> camera_width;
    fs["Map_height"] >> map_height;
    fs["Map_width"] >> map_width;
    fs["Warpmatrix"] >> warpmatrix;
    fs["SelectedPoints"] >> SelectedPoints;
    fs.release();
    /* FileStorage fsa(filea, FileStorage::READ);
    cv::FileNode areas = fsa["Areas"];
    // 遍历查看
    cv::FileNodeIterator it = areas.begin();
    for (; it != areas.end(); it++)
    {
        vector<Point> tl;
        tl.emplace_back((*it)["tl"]);
        vector<Point> br;
        br.emplace_back((*it)["br"]);
        maparea.emplace_back(cv::Rect(tl[0],br[0]));
    } */
}

void mapping::mappingpost(vector<Point> point_dect, vector<Point> &point_map)
{
    for (vector<Point>::size_type j = 0; j < point_dect.size(); j++)
    {
        for (vector<Mat>::size_type i = 0; i < warpmatrix.size(); i++)
        {
            if (pointPolygonTest(SelectedPoints[i],point_dect[j],false))
            {
            Mat org = (Mat_<double>(3, 1) << point_dect[j].x, point_dect[j].y, 1);
            Mat res = warpmatrix[i] * org;
            double *x = res.ptr<double>(0, 0);
            double *y = res.ptr<double>(0, 1);
            double *z = res.ptr<double>(0, 2);
            double xmap = *x / *z;
            double ymap = *y / *z;
            //cout << Point(xmap, ymap) << '\n';
            cout << i <<'\n';
            point_map.emplace_back(Point(xmap, ymap));
            break;
            }
        };
    }
}

void mapping::point_cloud_mapping(vector<Point> point_dect, vector<Point> &point_map, sl::Camera &zed)
{
    getDepth(zed, point_cloud);
    zed.getPosition(cam_pose, sl::REFERENCE_FRAME::CAMERA);

    for (vector<Point>::size_type j = 0; j < point_dect.size(); j++)
    {
        sl::float3 tmp;
        this->point_cloud.getValue(point_dect[j].x, point_dect[j].y, &tmp);
        sl::Translation pos = tmp;
        sl::Translation new_pos = pos * cam_pose.getOrientation() + cam_pose.getTranslation();
        tmp = sl::float3(new_pos.x, new_pos.y, new_pos.z);
        /* sl::Rotation rotation = cam_pose.getRotationMatrix();
        rotation.inverse();
        sl::Translation new_position = sl::Translation(tmp - cam_pose.getTranslation()) * rotation.getOrientation(); */
        point_map.emplace_back(cv::Point(static_cast<int>(748.0f - (tmp.tz - z_min) / z_step + .5f), static_cast<int>((tmp.tx - x_min) / x_step + .5f - 60.0f)));
        /* float px = tmp.x;
        float py = tmp.z;
        cout << "(" << px << "," << py << ")" << '\n';
        point_map.emplace_back(Point(((int)px + 5358), ((int)py))); */
    }
}

void mapping::drawmap(vector<Point> &point_map, bool red, Mat map_copy)
{
    if (red)
    {
        for (vector<Point>::size_type i = 0; i < point_map.size(); i++)
        {
            circle(map_copy, point_map[i], 20, Scalar(0, 0, 255), -1); //写出画出信息
        }
    }
    else
    {
        for (vector<Point>::size_type i = 0; i < point_map.size(); i++)
        {
            circle(map_copy, point_map[i], 20, Scalar(255, 0, 0), -1); //写出画出信息
        }
    }
}

void mapping::drawmap(vector<Point> &point_map, vector<int> type, bool red, int typenum, Mat map_copy)
{
    if (red)
    {

        for (int i = 0; i < typenum; i++)
        {
            circle(map_copy, point_map[i], 20, Scalar(0, 0, 255), -1); //写出画出信息
            cv::putText(map_copy, to_string(type[i]), point_map[i], FONT_HERSHEY_SIMPLEX, 3, Scalar(0, 0, 255), 6);
            //cv::putText(map_copy, to_string(type[i]), point_map[i], FONT_HERSHEY_SIMPLEX, 3, Scalar(255, 255, 255), 1);
        };
        for (vector<Point>::size_type i = typenum; i < point_map.size(); i++)
        {
            circle(map_copy, point_map[i], 20, Scalar(0, 0, 255), -1); //写出画出信息
        }
    }
    else
    {
        for (int i = 0; i < typenum; i++)
        {
            circle(map_copy, point_map[i], 20, Scalar(255, 0, 0), -1); //写出画出信息
            cv::putText(map_copy, to_string(type[i]), point_map[i], FONT_HERSHEY_SIMPLEX, 3, Scalar(255, 0, 0), 6);
            //cv::putText(map_copy, to_string(type[i]), point_map[i], FONT_HERSHEY_SIMPLEX, 3, Scalar(255, 255, 255), 1);
        };
        for (vector<Point>::size_type i = typenum; i < point_map.size(); i++)
        {
            circle(map_copy, point_map[i], 20, Scalar(255, 0, 0), -1); //写出画出信息
        }
    };
}