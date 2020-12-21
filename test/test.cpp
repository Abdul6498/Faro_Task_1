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
void average_fn(vector< Mat >& in_img);

ofstream MyFile("Coordinates.txt");

int main()
{
    unsigned int pixel_values[5];
    int  avg_val = 0, count = 0;
 
    string path = "Test_images/*.bmp";
    vector<Mat> images_fn;
    //Vec3b  color;
    cout << "Starting From Scratch, Hello Dr Rolf From Abdul Rehman!\n";
    
    load_images(path, images_fn);   //Load All bmp images at once  
   // process_images(images_fn);  //Process images and write coordinates to the file
   // average_fn(images_fn);
    cvtColor(images_fn[1], images_fn[1], cv::COLOR_RGB2GRAY);
    //cout << "No of channels: " << images_fn[1].channels() << endl;

    for (int y = 0; y < images_fn[1].rows; y++)
    {
        for (int x = 0; x < images_fn[1].cols; x++)
        {
            //if (images_fn[1].at<uchar>(y, x) > 1)
            //{
                pixel_values[0] = images_fn[1].at<uchar>(y, x);
                count++;
                if (count == 0)
                {
                    pixel_values[0] = images_fn[1].at<uchar>(y, x);
                }
                else if (count == 1)
                {
                    pixel_values[1] = images_fn[1].at<uchar>(y, x);
                }
                else if (count == 2)
                {
                    pixel_values[2] = images_fn[1].at<uchar>(y, x);
                    avg_val = (pixel_values[0] + pixel_values[1] + pixel_values[2]) * 3;
                    images_fn[1].at<uchar>(y, x-1) = avg_val;
                    count = 0;
                }
                //pixel_values[1] = images_fn[1].at<uchar>(y, x);
                //pixel_values[2] = images_fn[1].at<uchar>(y, x + 1);
                //pixel_values[2] = images_fn[1].at<uchar>(y, x + 3);
                //pixel_values[2] = images_fn[1].at<uchar>(y, x + 4);
                //avg_val = (pixel_values[0] + pixel_values[1] + pixel_values[2]) / 3;
                //images_fn[1].at<uchar>(y, x) = avg_val;
            //}
       }
    }
    //images_fn[1].at<uchar>(265, 680) = 255;
    //pixel_vlaue3 = images_fn[1].at<uchar>(265, 680);
    //cout << "Channel 1: " << pixel_vlaue3 << endl;
    //cout << "Channel 2: " << color.val[1] << endl;
    //cout << "Channel 3: " << color.val[2] << endl;
   imwrite("Test_images/new_image.jpg", images_fn[1]);
    //resize(images_fn[1], images_fn[1], Size(1280,1024));

    MyFile.close();

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
        MyFile << "Image No: " << i+1 << endl;
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

void average_fn(vector< Mat >& img_in)
{
    int pixel_value1[3] = { 0,0,0 }, dist = 1;
    for (int i = 0; i < img_in.size(); i++)
    {
        MyFile << "Image No: " << i + 1 << endl;
        cvtColor(img_in[i], img_in[i], cv::COLOR_RGB2GRAY);
        for (int x = 0; x < img_in[i].rows; x++)
        {
            for (int y = 0; y < img_in[i].cols; y = y + dist)
            {
                if (img_in[i].at<uchar>(x, y) > 15)
                {
                    pixel_value1[0] = img_in[i].at<uchar>(x, y);
                    pixel_value1[1] = img_in[i].at<uchar>(x, y+1);
                    pixel_value1[2] = img_in[i].at<uchar>(x, y+2);
                    
                }
            }
        }
    }
}
