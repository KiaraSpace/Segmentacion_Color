#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;

int main()
{
    Mat imghsv, mask, imgcanny, imgdil;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    string objectType;
    vector<vector<Point>> conPoly(contours.size());
    vector<Rect>boundRect(contours.size());

    int hmin = 0, smin = 182, vmin = 83;
    int hmax = 32, smax = 255, vmax = 255;

    Mat img = imread("D:/2022-I/EE445-Q-Proyecto de Fin de Carrera/PreProc_papaya/papaya1.jpg");
   
    /*Trackbar to find the color of the object 

    namedWindow("Trackbar", (640, 200));
    createTrackbar("Hue min", "Trackbar", &hmin, 179);
    createTrackbar("Hue max", "Trackbar", &hmax, 179);
    createTrackbar("Sat min", "Trackbar", &smin, 255);
    createTrackbar("Sat max", "Trackbar", &smax, 255);
    createTrackbar("Val min", "Trackbar", &vmin, 255);
    createTrackbar("Val max", "Trackbar", &vmax, 255);
    */

    //Rango de color
    Scalar lower(hmin, smin, vmin);
    Scalar upper(hmax, smax, vmax);
    //Si esta en el rango segmentamos
    cvtColor(img, imghsv, COLOR_BGR2HSV);
    inRange(imghsv, lower, upper, mask);
       
    int morph_size = 8;
    Mat element = getStructuringElement(
        MORPH_ELLIPSE,
        Size(2 * morph_size + 1,
            2 * morph_size + 1),
        Point(morph_size,
            morph_size));
    Mat output;
    morphologyEx(mask, output,
        MORPH_OPEN, element,
        Point(-1, -1), 2);    imshow("Image", img);

    findContours(output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
    // draw contours on the original image
    Mat image_copy = img.clone();
    objectType = "Madura";
    drawContours(image_copy, contours, -1, Scalar(0, 255, 0), 2);
   
    putText(image_copy, objectType, Point(255, 262), FONT_HERSHEY_DUPLEX, 1.20, Scalar(100, 69, 255), 3);
    imshow("Image", img);
    imshow("Image HSV", imghsv);
    imshow("Image Mask", mask);
    imshow("Contours", image_copy);
         
    cv::waitKey(0);

    return 0;
}

