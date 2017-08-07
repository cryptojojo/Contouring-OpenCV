#ifndef TENSILE_H
#define TENSILE_H

class Tensile
{
	bool if_first = true;
	int totalFrameNumber = 0;
	vector<Mat> frame;
	float gage_length = 0;
	Mat currentFrame;

public:
	Tensile(int);
	Mat imageToBinary(Mat);
	vector<vector<Point>> getContours(Mat);
	vector<Point2f> getMassCenters(vector<vector<Point>>);
	void printMassCenters(vector<Point2f> , vector<vector<Point>> );

	int getFrameNumber();
	void setCurrentFrame(Mat);
	Mat getCurrentFrame();

};

#endif