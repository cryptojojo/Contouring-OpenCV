#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include <opencv2\features2d\features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>

#include "Tensile.h"

using namespace cv;
using namespace std;




Tensile::Tensile(int frameCount)
{
	Tensile::totalFrameNumber = frameCount;

}

Mat Tensile::imageToBinary(Mat start)
{
	Mat gray_image, thresh_image;
	cvtColor(start, gray_image, CV_BGR2GRAY);
	threshold(gray_image, thresh_image, 100, 255, THRESH_BINARY);

	medianBlur(thresh_image, thresh_image, 5);

	return thresh_image;
}

vector<vector<Point>> Tensile::getContours(Mat start) {

	Mat dst = Mat::zeros(start.rows, start.cols, CV_8UC3);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	start = start > 1;

	findContours(start, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	return contours;
}


vector<Point2f> Tensile::getMassCenters(vector<vector<Point>> contours) {

	vector<Moments> mu(contours.size());
	vector<Point2f> mc(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
	}

	for (int i = 0; i < contours.size(); i++) {
		mc[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
	}

	return mc;
}


void Tensile::printMassCenters(vector<Point2f> mc, vector<vector<Point>> contours) {
	cout << "Mass Centers:" << endl;

	for (int i = 0; i < contours.size(); i++)
	{
		cout << mc[i] << endl;
	}

}



int Tensile::getFrameNumber()
{
	return Tensile::totalFrameNumber;
}

void Tensile::setCurrentFrame(Mat frame)
{
	Tensile::currentFrame = frame;
}

Mat Tensile::getCurrentFrame()
{
	return Tensile::currentFrame;
}



