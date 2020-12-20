// test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utility.hpp>

using namespace std;
using namespace cv;

void load_images(const String& dirname, vector< Mat >& img_lst);
void process_images(vector< Mat >& img_in);

ofstream MyFile("Coordinates.txt");

int main()
{
    int pixel_value1[3] = {0,0,0}, pixel_value2 = 0, pixel_value3 = 0, pixel_value[100][100], count = 0, dist = 1, count_nb = 0;
    string path = "Test_images/*.bmp";
    vector<Mat> images_fn;

    cout << "Hello World!\n";
    //Load All images at once
  

    load_images(path, images_fn);
    process_images(images_fn);
    //resize(images_fn[1], images_fn[1], Size(1280,1024));

   // cout << "No of Channels in grey: " << images_fn[1].channels() << endl;
   // imshow("Image window", images_fn[1]);

    MyFile.close();
    //rows,cloumns
    waitKey(0);
    return 0;
}

void load_images(const String& dirname, vector< Mat >& img_lst)
{
    vector<String> files;
    glob(dirname, files);

    size_t count = files.size(); //number of bmp files in test images folder
    for (size_t i = 0; i < count; i++)
        img_lst.push_back(imread(files[i]));

}

void process_images(vector< Mat >& img_in)
{
    int pixel_value1[3] = { 0,0,0 }, dist = 1;
    for (int i = 0; i < img_in.size(); i++)
    {
        MyFile << "Image No: " << i << endl;
        cvtColor(img_in[i], img_in[i], cv::COLOR_RGB2GRAY);
        for (int x = 0; x < img_in[i].rows; x++)
        {
            for (int y = 0; y < img_in[i].cols; y = y + dist)
            {
                if (img_in[i].at<uchar>(x, y) > 15)
                {
                    pixel_value1[0] = img_in[i].at<uchar>(x, y);
                    pixel_value1[1] = img_in[i].at<uchar>(x, y + 1);
                    pixel_value1[2] = img_in[i].at<uchar>(x, y + 2);
                    if (pixel_value1[1] >= pixel_value1[0] && pixel_value1[1] >= pixel_value1[2])
                    {
                        MyFile << "Row: " << x + 1 << " --   Col: " << y + 2 << " --    Pixel Value: " << pixel_value1[1] << endl;
                    }
                }
            }
        }
    }
}
