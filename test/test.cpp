// test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utility.hpp>

using namespace std;
using namespace cv;

void load_images(const String& dirname, vector< Mat >& img_lst);
int main()
{
    int pixel_value1 = 0, pixel_value2=0, pixel_value[100][100], count=0;
    
    cout << "Hello World!\n";
    //Load All images at once
    string path = "Test_images/*.bmp";
    vector<Mat> images_fn;

    load_images(path, images_fn);
    cout << "Size of Mat: " << images_fn[1].channels() << endl;
    resize(images_fn[1], images_fn[1], Size(1280,1024));
    //Mat img = imread("Test_images/2.bmp");
    cvtColor(images_fn[1], images_fn[1], cv::COLOR_BGR2GRAY);
    imshow("Image window", images_fn[1]);

    //Mat img = imread("Test_images/1.bmp", IMREAD_GRAYSCALE);
    //cout << "Cols: "<<images_fn[1].cols << "\n";
    //cout << "Rows: " << images_fn[1].rows << "\n";

    //pixel_value = new int[images_fn[1].rows][images_fn[1].cols];

    for (int x = 0; x < images_fn[1].rows; x++)
    {
        //cout << "Row" << x << "\n";
        for (int y = 0; y < images_fn[1].cols; y++)
        { 
            //pixel_value[x][y] = images_fn[1].at<uchar>(x, y);

            if (images_fn[1].at<uchar>(x, y) > 15)
            {
                pixel_value2 = images_fn[1].at<uchar>(x, y);
                //cout << "pixel_value: " << pixel_value2 << endl;
                //cout << "x:" << x << "-- y:" << y << endl;
                count++;
            }

            //cout << "pixel_value: " << pixel_value[x][y] << endl;
        }
    }

    cout << "Count: " << count << endl;

    for (int x = 0; x <= count; x++)
    {
        //cout << "pixel_value2: " << pixel_value[9][x] << endl;
    }
    pixel_value1 = images_fn[1].at<uchar>(513-1, 642-1);
    cout << "pixel_value1: " << pixel_value1 << endl;
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

