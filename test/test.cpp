// test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utility.hpp>

using namespace std;
using namespace cv;

void load_images(const String& dirname, vector< Mat >& img_lst);
int main()
{
    int pixel_value1 = 0, pixel_value2 = 0;

    cout << "Hello World!\n";
    //Load All images at once
    string path = "Test_images/*.bmp";
    vector<Mat> images_fn;


    load_images(path, images_fn);
    imshow("Image window", images_fn[3]);

    //Mat img = imread("Test_images/1.bmp", IMREAD_GRAYSCALE);
    //resize(img, img, Size(), 0.1, 0.1);
    cout << images_fn[3].cols;
  /*  for (int x = 0; x <= img.rows; x++)
    {
        for (int y = 0; y <= img.cols; y++)
        {
            pixel_value2 = img.at<uchar>(x, y);

            cout << "pixel_value2: " << pixel_value2 << endl;
        }
    }*/
    pixel_value2 = images_fn[3].at<uchar>(200, 200);
    cout << "pixel_value2: " << pixel_value2 << endl;
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

