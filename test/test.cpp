/* test.cpp : This file contains the 'main' function. Program execution begins and ends there.
Description : Loads all image files within a folder into memory and processes one after the other. 
Convert the attached Loaded files to gray scale. Get the positions of the lines in 
the image. The processing deliver all image pixel coordinates where the pixel brightness 
of the image after it has been averaged over +/-5 pixels horizontally is maximal within a neighbourhood of
horizontally +/- 10 pixels.
Author Name : Abdul Rehman
contact: abdulrehman6498@outlook.com
Version : 3.0
*/

#include <iostream>
#include <array>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/utility.hpp>

using namespace std;
using namespace cv;

unsigned volatile kernel_size = 11;     //Kernel Size for averging filter
unsigned volatile kernel_size_max = 10; //Kernel Size for maximal filter
unsigned volatile kernel_size_U = 21;   //Upper Limit of Kernel Size for maximal filter (-/+ 10 pixels = 10 Neighbors from left + 1 Centre pixel + 10 Neighbors from Right)
unsigned volatile dist = 1;             //Distance for maximum filter

void load_images(const String& dirname, vector< Mat >& img_lst);    //Function to load images
void process_images(vector< Mat >& img_in);                         //Function to Process images. For finding the maximum pixel value
void average_fn(vector< Mat >& in_img);                             //Function to find the average

ofstream MyFile("Coordinates.txt");                                 //File name to record the coordinates and pixel values

int main()
{
    string path_test = "Test_images/*.bmp";                         //Path for input raw images
    string path_prc = "Prepared_images/*.bmp";                      //Path for averaged images 

    vector<Mat> images_avg;
    vector<Mat> images_prc;

    cout << "Starting From Scratch, Hello Dr Rolf From Abdul Rehman!\n";

    load_images(path_test, images_avg);   //Load All bmp images at once
    average_fn(images_avg);               //Take average

    load_images(path_prc, images_prc);   //Load All bmp images at once
    process_images(images_prc);  //Process images and write coordinates to the file
    

    MyFile.close();             //Close the file after recording

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
    int pxl_prv = 0, pxl_crnt = 0, pxl_prv_U = 0, pxl_crnt_U = 0, pxl_center = 0;

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~Processing Images~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Please wait software is Processing test images." << endl;

    for (int i = 0; i < img_in.size(); i++)                                                     //Most outer loop to process images one by one
    {
        pxl_prv = 0, pxl_crnt = 0, pxl_prv_U = 0, pxl_crnt_U = 0, pxl_center = 0;

        cout << "Processing of image no " << i + 1 << " has started..................." << endl;

        MyFile << "Image No: " << i + 1 << endl;                                               //Data input to file

        cvtColor(img_in[i], img_in[i], cv::COLOR_RGB2GRAY);                                    //Change the image format 3 channels to Gray scale

        for (int x = 0; x < img_in[i].rows; x++)                                               //First inner loop(Nested Loop) for Rows in the image(Iteration size: 0 to No. of Rows)
        {
            for (int y = 0; y < img_in[i].cols- kernel_size_U; y = y + dist)                   //Second inner loop(Nested Loop) for Coloumns in the image(Iteration size: 0 to No. of cols-upper limit of kernel)
            {
                for (int p = y; p < kernel_size_max + y; p++)                                  //Find the maximum number from the first 10 pixels
                {
                    pxl_crnt = img_in[i].at<uchar>(x, p);
                    if (pxl_crnt >= pxl_prv)
                    {
                        pxl_prv = pxl_crnt;
                    }
                }

                for (int p = kernel_size_max+y+1; p < kernel_size_U + y; p++)                  //Find the maximum number from the last 10 pixels
                {
                    pxl_crnt_U = img_in[i].at<uchar>(x, p);
                    if (pxl_crnt_U >= pxl_prv_U)
                    {
                        pxl_prv_U = pxl_crnt_U;
                    }
                }

                if (pxl_prv_U > 15 && pxl_prv > 15)                                             //Find local maxima
                {
                    pxl_center = img_in[i].at<uchar>(x, abs(kernel_size_max + y));
                     if (pxl_center >= pxl_prv_U && pxl_center >= pxl_prv)
                    {
                        MyFile << "Row: " << x + 1 << " --   Col: " << y + kernel_size << " --    Pixel Value: " << pxl_center << endl;
                    }
                }               
            }
        }
        cout << "Processing of image no " << i + 1 << " has finished.!!!!!!!!!!!!!!!!!!!!!!" << endl;
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~Processing completed~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
}

void average_fn(vector< Mat >& img_in)
{
    unsigned int pixel_values;
    unsigned int  avg_val = 0, count = 0, sum_pxl = 0, k = 0;

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~Avergae Started~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Please wait software is taking average of the test images." << endl;

    for (int t = 0; t < img_in.size(); t++)                                                 //Most outer loop to process images one by one
    {
        cout << "Calculating the average of image no "<< t+1 << " has started........" << endl;

        cvtColor(img_in[t], img_in[t], cv::COLOR_RGB2GRAY);                                 //Change the image format 3 channels to Gray scale

        for (int y = 0; y < img_in[t].rows; y++)                                            //First inner loop(Nested Loop) for Rows in the image(Iteration size: 0 to No. of Rows)
        {
            for (int i = 0; i < img_in[t].cols - kernel_size; i++)                          //Second inner loop(Nested Loop) for Coloumns in the image(Iteration size: 0 to No. of cols - kernel size)
            {
                for (int x = i; x < i + kernel_size; x++)                                   //Apply moving average
                {

                    pixel_values = img_in[t].at<uchar>(y, x);
                    sum_pxl = pixel_values + sum_pxl;

                    if (count == (kernel_size - 1))
                    {
                        k = abs(x - (kernel_size/2));
                        avg_val = sum_pxl / kernel_size;
                        img_in[t].at<uchar>(y, k) = avg_val;                                //Change the brightness of pixel according to the average
                        sum_pxl = 0;
                        avg_val = 0;
                        count = 0;
                    }
                    else
                    {
                        count++;
                    }
                }
            }

        }
        cout << "Avergae Completed for image no " << t + 1 << " has finished!!!!!!!!!!!" << endl;
        imwrite("Prepared_images/image_" + to_string(t+1) + ".bmp", img_in[t]);
    }
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~Avergae completed~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
   // process_images(img_in);   //Process the images without saving(Optional)//Don't uncomment without the permission of Author. 
}
