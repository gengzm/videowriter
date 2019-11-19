#include <opencv2/opencv.hpp>
#include <vector>
//#include<cstdio>
///////////////////////////////////////
#include <direct.h>
#include<iostream>
#include<io.h>
#include<cstdio>
#include<cstdlib>
using namespace std;

void Image2Video(std::vector<std::string> files, std::string& out)
{
    //std::string out = "E:/Data/a.avi";
    double fps = 25;
    cv::Mat mat = cv::imread(files[0]);
    cv::Size framesize = cv::Size(mat.cols / 2, mat.rows / 2);
    cv::VideoWriter writer = cv::VideoWriter(out, CV_FOURCC('M', 'J', 'P', 'G'), fps, framesize);
    for (int i = 0; i < files.size(); i++)
    {
        cv::Mat mat = cv::imread(files[i]);
        if (!mat.empty())
        {
            cv::resize(mat, mat, framesize);
            writer.write(mat);
        }
        std::cout << "progress = " << i << "/" << files.size() << std::endl;
    }
    writer.release();
}

void ListFiles(const char * dir, std::vector<std::string>& files, const char * profix)
{
    if (dir == nullptr || strlen(dir) == 0)
    {
        return;
    }
    if (profix == nullptr)
    {
        return;
    }
    using namespace std;

    files.clear();
    long long hFind;
    _finddata_t findData; // 编译器可能不识别
    char finddir[260] = "0";
    sprintf(finddir, "%s%s", dir, (dir[strlen(dir) - 1] == '/') ? "*" : "/*");
    hFind = _findfirst(finddir, &findData);
    if (hFind == -1)
    {
        std::cout << "Failed to find first file!\n";
        return;
    }

    do
    {
        if (findData.attrib == _A_SUBDIR
            &&(
                  strcmp(findData.name, ".") == 0
               || strcmp(findData.name, "..") == 0
                )
            )    // 是否是子目录并且不为"."或".."
        {
            std::cout << findData.name << "\t<dir>\n";
        }
        else
        {
            if (profix == "" || 
                (profix != "" && strstr(findData.name, profix))
            )
            {
                std::string str = std::string(dir) + "/" + findData.name;
                files.push_back(str);
                std::cout << findData.name << "\t"  << std::endl;
            }
            
            
        }
            
    } while (_findnext(hFind, &findData) == 0);
    _findclose(hFind); 

    return;
}

void VideoToFast(std::string video_src, std::string viedo_dst, unsigned int time = 30)
{
    cv::VideoCapture cap;
    cap.open(video_src);
    if (!cap.isOpened())
    {
        return;
    }
    if (time == 0) time = 1;
    int fps = cap.get(CV_CAP_PROP_FPS);
    cv::Mat mat;
    cap >> mat;
    cv::Size framesize = cv::Size(mat.cols, mat.rows);
    cv::VideoWriter writer = cv::VideoWriter(viedo_dst, CV_FOURCC('M', 'J', 'P', 'G'), fps, framesize);
    int i = 0;
    int framenum = cap.get(CV_CAP_PROP_FRAME_COUNT);
    while (i < framenum)
    {
        i++;
        cap >> mat;
        if (i % time == 0)
        {
           writer.write(mat);
           std::cout << "progress = " << i << "/" << framenum << std::endl;
        }
     }
    cap.release();
    writer.release();
}

void ExtractAndDeleteImage(std::vector<std::string>& files, int savepernum)
{
    int ret = 0;
    for (int i = 0; i < files.size(); i++)
    {
        if (i % savepernum != 0)
        {
            std::cout << "removing file: " << files[i] << std::endl;
            ret = remove(files[i].c_str());
        }
    }
    std::cout << "remove file end\n";
}

void ReName(std::vector<std::string>& files, const char* toreplace)
{
    for (int i = 0; i < files.size(); i++)
    {
        if (strstr(files[i].c_str(), toreplace))
        {
            int off = strstr(files[i].c_str(), toreplace) - files[i].c_str();
            std::string str = files[i];
            str.replace(off, strlen(toreplace), strstr(toreplace, "left") ? "right_" : "left_");
            rename(files[i].c_str(), str.c_str());
        }
    }
}


int main()
{
#if 0
    std::vector<std::string> files;
    ListFiles("E:/Data/3D_barcode_light", files, "left");
    std::string out = "E:/Data/3D_barcode_light.avi";
    Image2Video(files, out);
    ListFiles("E:/Data/3D_barcode_light_2", files, "left");
    out = "E:/Data/3D_barcode_light_2.avi";
    Image2Video(files, out);
    ListFiles("E:/Data/3D_barcode_light_3", files, "left");
    out = "E:/Data/3D_barcode_light_3.avi";
    Image2Video(files, out);
    ListFiles("E:/Data/3D_barcode_light_4", files, "left");
    out = "E:/Data/3D_barcode_light_4.avi";
    Image2Video(files, out);
    ListFiles("E:/Data/3D_barcode_light_5", files, "left");
    out = "E:/Data/3D_barcode_light_5.avi";
    Image2Video(files, out);
    ListFiles("E:/Data/real3d_0525_0_railvibration", files, "left");
    out = "E:/Data/real3d_0525_0_railvibration.avi";
    Image2Video(files, out);
    ListFiles("E:/Data/real3d_0525_1_railvibration", files, "left");
    out = "E:/Data/real3d_0525_1_railvibration.avi";
    Image2Video(files, out);
    ListFiles("E:/Data/real3d_0525_2_railvibration", files, "left");
    out = "E:/Data/real3d_0525_2_railvibration.avi";
    Image2Video(files, out);
#endif

    std::vector<std::string> files;

    int r = _access("E:/Data/OpticalPlatTest/3d_outfocus2_20190531/", 00);
    //ListFiles("E:/Data/OpticalPlatTest/ttt", files, "left");
   // ReName(files, "left");

    //ListFiles("F:/Data/20191022_152523", files, "right");
    //ExtractAndDeleteImage(files, 5);

    //ListFiles("E:/Data/OpticalPlatTest/3d_outfocus2_20190531", files, "right");
    //ReName(files, "right");

    VideoToFast("C:/Users/MyPC/Videos/2019-11-01 15-45-49.mp4", "C:/Users/MyPC/Videos/2019-11-01 15-45-49_short.avi", 10);
    //VideoToFast("C:/Users/MyPC/Videos/2019-05-27 14-40-45.mp4", "E:/Data/2019-05-27 14-40-45.avi");
    //VideoToFast("C:/Users/MyPC/Videos/2019-05-27 15-43-09.mp4", "E:/Data/2019-05-27 15-43-09.avi");
    //VideoToFast("C:/Users/MyPC/Videos/2019-05-27 15-56-33.mp4", "E:/Data/2019-05-27 15-56-33.avi");
    //VideoToFast("C:/Users/MyPC/Videos/2019-05-27 16-25-23.mp4", "E:/Data/2019-05-27 16-25-23.avi"); 
    //VideoToFast("C:/Users/MyPC/Videos/2019-05-27 17-02-54.mp4", "E:/Data/2019-05-27 17-02-54.avi");

   // std::vector<std::string> files;
    //ListFiles("E:/Data/OpticalPlatTest/outfocus2_real3d20190603", files, "left");
    //ExtractAndDeleteImage(files, 2);
    return 0;
}