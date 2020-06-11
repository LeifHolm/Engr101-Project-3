//Headers
#include "robot.hpp"
#include <math.h>
#include <iostream>

using namespace std;

bool doDrive = true;

/**
* Check if white line exists in camera view, return 1 (true) or 0 (false)
*/
int HasWhiteLine() {
	int totalWhite = 0;

	for(int row =0 ; row < cameraView.height ; row++){	
		for(int column = 0; column < cameraView.width ; column++){
			int red = (int)get_pixel(cameraView, row, column, 0);
			int green = (int)get_pixel(cameraView, row, column, 1);
			int blue = (int)get_pixel(cameraView, row, column, 2);
			
			//WHITE DETECTION
			//All rgb values greater than 250 indicate a white pixel
			if(red > 250 && green > 250 && blue > 250){
				totalWhite += 1;
			}
		}
	}
	//LINE DETECTION
	//If at least 3x height of frame in white pixels, indicates there is a white line
	if(totalWhite >= 3*cameraView.height){
		return 1;
	}
	else{
	    return 1;
	}
}

/**
* Check if red line exists in given image, return 0 (bad) 1 (good)
*/
int HasRedLine() {
	int totalRed = 0;

	for(int row =0 ; row < cameraView.height ; row++){	
		for(int column = 0; column < cameraView.width ; column++){
			int red = (int)get_pixel(cameraView, row, column, 0);
			int green = (int)get_pixel(cameraView, row, column, 1);
			int blue = (int)get_pixel(cameraView, row, column, 2);
			
			//RED DETECTION
			//Red twice as large as both green and blue indicates a red pixel
			if(red > 2 * blue and red > 2 * green){
				totalRed += 1;
			}
		}
	}
	//LINE DETECTION
	//If at least 3x height of frame in red pixels, indicates there is a red line
	if(totalRed >= 3*cameraView.height){
		return 1;
	}
	else{
	    return 0;
	}
}

/**
* Check if checker black flag exists in given image
*/
int HasFinish() {
	return 0;
}

/**
* Returns coordinates on white line that robot is aiming for
*/
double GetWhiteTarget() {
	for(int row =0 ; row < cameraView.height; row++){
		for(int column = 0; column < cameraView.width; column++){
			int r = (int)get_pixel(cameraV/.iew, row, column, 0);
			int g = (int)get_pixel(cameraView, row, column, 1);
			int b = (int)get_pixel(cameraView, row, column, 2);
			
			//WHITE DETECTION
			//All rgb values greater than 240 indicate a white pixel
			if(r > 250 && g > 250 && b > 250){
				int xRobot = cameraView.width / 2;
				int yRobot = cameraView.height -1;
				int xTarget = column;
				int yTarget = row;
				double distX = xTarget - xRobot;
				double distY = yRobot - yTarget;
				double theta = atan(distX / distY) * 180 / M_PI;
				
				return theta;
			}
		}
	}
}

/**
* Returns coordinates on red wall that robot is aiming for
* The coordinates are offset so that the robot moves alongside the wall, not on it
*/
double GetRedTarget() {
	for(int row =0 ; row < cameraView.height; row++){
		for(int column = 0; column < cameraView.width ; column++){
			int r = (int)get_pixel(cameraView, row, column, 0);
			int g = (int)get_pixel(cameraView, row, column, 1);
			int b = (int)get_pixel(cameraView, row, column, 2);
			
			//RED DETECTION
			//Red twice as large as both green and blue indicates a red pixel
			if(r > 2 * b && r > 2 * g){
				int xRobot = cameraView.width / 2;
				int yRobot = cameraView.height -1;
				int xTarget = column + 20; //20px offset from wall
				int yTarget = row + 20; //20px offset from wall
				double distX = xTarget - xRobot;
				double distY = yRobot - yTarget;
				double theta = atan(distX / distY) * 180 / M_PI;
				
				return theta;
			}
		}
	}
}

/**
*If HasWhiteLine, GetWhiteTarget, and calculate degree adjustment to center offset to white line
*Else GetRedTarget, and calculate degree adjustment to center robot offset to left red line
*Return direction to adjust by in degrees
* */
double AnalyseImage() {
	if(HasWhiteLine() == 1){
		doDrive = true;
		return GetWhiteTarget();
	}
	else if(HasRedLine() == 1){
		doDrive = true;
		return GetRedTarget();
	}
	else{
		doDrive = false;
	    return 10;
    }
}

/**
*Given input degrees, adjust motor speeds.
*/
void AdjustRobot(double adjustmentdegrees) {
  setMotors(adjustmentdegrees, adjustmentdegrees * -1);
}

/**
*Do "step", drive at current motor speeds
*/
void DriveRobot() {
  setMotors(50,50);
}

/**
*Main loop:
*>AnalyseImage return direction change in degrees
*>AdjustRobot(AnalyseImage)
*>Conditionals, if colliding, win lose
*>DriveRobot()
*/

int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
	double adjustment_degrees = 0;
	bool running = 1;
	double vLeft = 40.0;
	double vRight = 30.0;
	while(running == 1){
		takePicture();
		SavePPMFile("i0.ppm",cameraView);
		adjustment_degrees = AnalyseImage();
		AdjustRobot(adjustment_degrees);
		sleep(1);
		if(doDrive) {
			DriveRobot();
		}
		std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
		sleep(1);
		if (HasFinish() == 1) {
			running = 0;
		}
	}
}
