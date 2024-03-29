/*
 * RobotFSM.cpp
 *
 *  Created on: 02/04/2014
 *      Author: rgap
 */

#include "RobotFSM.h"
#include <boost/thread/thread.hpp>

using namespace cv;
using namespace std;

RobotFSM::RobotFSM() {
}

void RobotFSM::initializeDevice(std::string devicePath) {
	control.initialize(devicePath);
	control.send(INICIAL_PALA);
	boost::this_thread::sleep( boost::posix_time::milliseconds(100) );
}

void RobotFSM::setParameters(ModelParameters* P_) {
	P = P_;
}

void RobotFSM::moveStraight(Rect *rectNearestCan, int H) {
	if (rectNearestCan->br().y > P->distanceCollectCan) { //4855 seg
		control.send(RECOGER_LATA);
		boost::this_thread::sleep(boost::posix_time::milliseconds(5200));
	} else {
		control.send(AVANZAR);
		boost::this_thread::sleep(boost::posix_time::milliseconds(100));
	}
}

void RobotFSM::searchCan(Rect *rectNearestCan, int canCenterX, int W, int H) {
	//cout << "searchCan" << endl;
	int tol = 70;
	if (canCenterX > (W / 3 + tol) && canCenterX <= (2 * W / 3 - tol)) {
		moveStraight(rectNearestCan, H);
	} else if (canCenterX >= 0 && canCenterX <= (W / 3 + tol)) {
		control.send(GIRO_IZQ);
		boost::this_thread::sleep(boost::posix_time::milliseconds(100));
	} else {
		control.send(GIRO_DER);
		boost::this_thread::sleep(boost::posix_time::milliseconds(100));
	}
}

void RobotFSM::planWithEnvironment(Rect *rectNearestCan, Mat &imgColor) {

	int W = imgColor.cols, H = imgColor.rows;
	int canCenterX = (rectNearestCan->tl().x + rectNearestCan->br().x) / 2;

	if (rectNearestCan->br().x == -2) { // any obstacle & any can
		moveStraight(rectNearestCan, H);
	} else if (rectNearestCan->br().x != -2) { // any obstacle & can detected
		searchCan(rectNearestCan, canCenterX, W, H);
	}
}

RobotFSM::~RobotFSM() {
}
