//Headers
#include "robot.hpp"
#include <math.h>

using namespace std;

bool doDrive = true;
bool challenge = false;

/**
* Check if white line exists in camera view, return 1 (true) or 0 (false)
*/
int HasWhiteLine() {
	int totalWhite = 0;

	for(int row = cameraView.height - 1 ; row > ((3 * cameraView.height) / 4) - 1; row -= 1){
		for(int column = ((3 * cameraView.width) / 8); column < ((5 * cameraView.width) / 8); column++){
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
	if(totalWhite >= cameraView.height / 4){
		return 1;
	}
	else{
	    return 0;
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
	int black = 0;
	//If more than 100 black pixels in centre half of frame, then indicates black checker flag is present
	for(int row = cameraView.height / 4; row < (3*cameraView.height)/4; row++){	
		for(int column = cameraView.width / 4; column < (3*cameraView.width) / 4; column++){
			int r = (int)get_pixel(cameraView, row, column, 0);
			int g = (int)get_pixel(cameraView, row, column, 1);
			int b = (int)get_pixel(cameraView, row, column, 2);
			//BLACK DETECTION
			if(r < 10 && g < 10 && b < 10){
				black++;
				if(black > 200){
					return 1;
				}
			}
		}
	}
	return 0;
}

/**
* Returns angle (theta) that robot should turn by based of part of line it is targeting
* First find the target, then finds angle
*/
double GetWhiteTarget() {
	int xTarget = cameraView.width / 2;
	int yTarget = cameraView.height - 1;
	for(int row = cameraView.height - 1; row > (3 * cameraView.height) / 4; row -= 1){
		for(int column = ((3 * cameraView.width) / 8); column < ((5 * cameraView.width) / 8); column++){
			int r = (int)get_pixel(cameraView, row, column, 0);
			int g = (int)get_pixel(cameraView, row, column, 1);
			int b = (int)get_pixel(cameraView, row, column, 2);
			
			//WHITE DETECTION
			//All rgb values greater than 250 indicate a white pixel
			if(r > 250 && g > 250 && b > 250){
				if(column < xTarget || column > (cameraView.width - xTarget)){
					xTarget = column;
					yTarget = row;
				}
			}
		}
	}
	int xRobot = cameraView.width / 2;
	int yRobot = cameraView.height + 20 - 1;
	double distX = xTarget - xRobot;
	double distY = yRobot - yTarget;
	if(abs(distX) < 5){
		distX = 0;
	}
	double theta = atan(distX / distY) * 180 / M_PI;
	
	return theta;
}

/**
* Returns single digit number that corrsponds to a certain maze scenario based on what is in the camerView. 
* There are 5 scenarios; left corner/hairpin (4), right corner (3), dead end (2), straight (1), empty (0)
* The method AnalyseImage() gets the returned number, and adjusts/drives the robot based on scenario
*/
int GetRedTarget() {
	bool redTop = false;
	bool redLeft = false;
	bool redLeftTurn = false;
	//TOP DETECTION
	for(int row = cameraView.height / 2; row < cameraView.height; row++){
		bool redFound = false;
		int redRow  = 0;
		int columnRange = cameraView.width / 2;
		for(int column = 0; column < columnRange; column++){
			int red = (int)get_pixel(cameraView, row, column, 0);
			int green = (int)get_pixel(cameraView, row, column, 1);
			int blue = (int)get_pixel(cameraView, row, column, 2);
			
			//RED DETECTION
			//Red twice as large as both green and blue indicates a red pixel
			if(red > 2 * blue && red > 2 * green){
				redFound = true;
				if(redFound == true){
					redRow += 1;
				}
			}
			else{
				redFound = false;
				redRow = 0;
			}
		}
		//Top
		if(redRow > cameraView.width / 4){
			redTop = true;
		}
	}
	
	//LEFT DETECTION
	for(int column = 0; column < (cameraView.width / 2); column++){
		int redCol  = 0;
		for(int row = cameraView.height / 2; row < cameraView.height; row++){
			int red = (int)get_pixel(cameraView, row, column, 0);
			int green = (int)get_pixel(cameraView, row, column, 1);
			int blue = (int)get_pixel(cameraView, row, column, 2);
			
			//RED DETECTION
			//Red twice as large as both green and blue indicates a red pixel
			if(red > 2 * blue && red > 2 * green){
				redCol += 1;
			}
		}
		//Left edge full
		if(redCol == cameraView.height / 2){
			redLeft = true;
		}
		//Left edge partial
		else if(redCol > 20){
			redLeftTurn = true;
		}
	}
	
	//SCENARIO DETECTION
	if(redLeftTurn == true){
		return 4; //Left Corner
	}
	else if(redTop == true && redLeft == true){
		return 3; //Right Corner
	}
	else if(redTop == true){
		return 2; //Dead end
	}
	else if(redTop == false && redLeft == false){
		setMotors(-168.75, 168.75);
		setMotors(50, 50);
		setMotors(168.75, -168.75);
		return 1;
	}
	else{
		return 0;
	}
}

/**
*If HasWhiteLine, GetWhiteTarget, and calculate degree adjustment to center offset to white line
*Else if GetRedTarget, and find the angle of adjustment or the actiopn to perform based on scenario
*Else, for core and completion doDrive - which pivots the robot until it finds the line. 
*For challenege the robot does use doDrive so does not pivot
* */
double AnalyseImage() {
	if(HasWhiteLine() == 1){
		doDrive = true;
		return GetWhiteTarget();
	}
	else if(HasRedLine() == 1){
		challenge = true;
		if(GetRedTarget() == 4){
			doDrive = false;
			setMotors(600, 600);
			for(int i = 0; i < 20; i++){
				setMotors(-337.5 / 20, 337.5 / 20);
				setMotors(70, 70);
			}
			return 0;
		}
		if(GetRedTarget() == 3){
			doDrive = false;
			return 84.375;
		}
		else if(GetRedTarget() == 2){
			doDrive = false;
			return -84.375;
		}
		else if(GetRedTarget() == 1){
			return 0;
		}
		else{
			doDrive = true;
			return 0;
		}
	}
	else{
		if(challenge == true){
			doDrive = true;
			return 0;
		}
		else{
			doDrive = false;
			return 10;
		}
    }
}

/**
*Given input degrees, adjust motor speeds.
*/
void AdjustRobot(double adjustmentdegrees) {
  setMotors((675 / 360) * adjustmentdegrees, (675 / 360) * adjustmentdegrees * -1);
}

/**
*Do "step", drive at current motor speeds
*/
void DriveRobot() {
  setMotors(50, 50);
}

/**
*Main loop:
*>AnalyseImage return direction change in degrees
*>AdjustRobot(AnalyseImage)
*>Conditionals, if colliding, win lose
*>DriveRobot()
*/

int main(){
	if(initClientRobot() !=0){
		cout<<" Error initializing robot"<<endl;
	}
	
	bool running = 1;
	while(running == 1){
		takePicture();
		SavePPMFile("i0.ppm",cameraView);
		double adjustmentDegrees = AnalyseImage();
		AdjustRobot(adjustmentDegrees);
		if(doDrive) {
			DriveRobot();
		}
		if(HasFinish() == 1) {
			running = 0;
		}
	}
	cout<<"Robot has completed the maze!"<<endl;
	setMotors(0,0);
}
