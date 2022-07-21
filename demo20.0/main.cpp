#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;

/*void getContours(Mat imgDil, Mat img) {
    vector<vector<Point>> contours;
    vector<Vec4i> hierachy;
    findContours(imgDil, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    //-1: write all the contours
    for (int i = 0; i <contours.size(); i++) {
        int area = contourArea(contours[i]);
        cout << area << endl;
        if (area << 1000) {
            float peri = arcLength(contours[i], true);

            //-1: write all the contours
            drawContours(img, contours, -1, Scalar(255, 0, 255), 2);
        }
    }
}*/
int main()
{
    Mat imghsv, mask, imgcanny, imgdil;
    int hmin = 0, smin = 182, vmin = 83;
    int hmax = 32, smax = 255, vmax = 255;
    Mat img = imread("D:/2022-I/EE445-Q-Proyecto de Fin de Carrera/PreProc_papaya/papaya1.jpg");
   
    cvtColor(img, imghsv, COLOR_BGR2HSV);

    namedWindow("Trackbar", (640, 200));
    createTrackbar("Hue min", "Trackbar", &hmin, 179);
    createTrackbar("Hue max", "Trackbar", &hmax, 179);
    createTrackbar("Sat min", "Trackbar", &smin, 255);
    createTrackbar("Sat max", "Trackbar", &smax, 255);
    createTrackbar("Val min", "Trackbar", &vmin, 255);
    createTrackbar("Val max", "Trackbar", &vmax, 255);

    while(true){
        //Rango de color
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        //Si esta en el rango segmentamos
        inRange(imghsv, lower, upper, mask);
        
        Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(9, 9));
        /*
        dilate(imghsv, imgdil, kernel);

        getContours(imgdil, img);*/

        imshow("Image", img);
        imshow("Image HSV", imghsv);
        imshow("Image HSV", mask);
 
        //imshow("Image Dil", imgdil);
    
        cv::waitKey(1);
    }
    return 0;
}

