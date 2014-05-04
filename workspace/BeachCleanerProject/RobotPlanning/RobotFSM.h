/*
 * RobotFSM.h
 *
 *  Created on: 02/04/2014
 *      Author: rgap
 */

#ifndef ROBOTFSM_H_
#define ROBOTFSM_H_

#include <opencv2/opencv.hpp>
#include "../DataTransfer/SerialDevice.h"
using namespace cv;
using namespace std;

#define SEND_SIGNALS 0

class RobotFSM {
private:
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	Mat imgObstaclesBin_temp;

public:
	RobotFSM();

	void planWithEnvironment(Point3f *pointNearestCan, Mat &imgObstaclesBin);

	virtual ~RobotFSM();
};

#endif /* ROBOTFSM_H_ */