//Headers
#include "robot.hpp"
#include <math.h>
#include <windows.h>

//Namespace
using namespace std;

//Function Declarations

//Field Declarations


/**
* Check if white line exists in given image, return 0 (bad) 1 (good)
*/
int HasWhiteLine() {
	int totalWhite = 0;

	for(int row =0 ; row < cameraView.height ; row++){	
		for(int column = 0; column < cameraView.width ; column++){
			int red = (int)get_pixel(cameraView, row, column, 0);
			int green = (int)get_pixel(cameraView, row, column, 1);
			int blue = (int)get_pixel(cameraView, row, column, 2);
			
			//WHITE DETECTION
			//All rgb values greater than 240 indicate a white pixel
			if(red > 240 && green > 240 && blue > 240){
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
	return 0;
}

/**
* Returns coordinates on white line that robot is aiming for
*/
double GetWhiteTarget() {
    int targetCoordinates[2] = {-1, -1};
	
	int xTarget1 = -1;
	int yTarget1 = -1;
	int xTarget2 = -1;	
	int yTarget2 = -1;
	
	for(int row =0 ; row < cameraView.height; row++){
		for(int column = 0; column < cameraView.width ; column++){
			int r = (int)get_pixel(cameraView, row, column, 0);
			int g = (int)get_pixel(cameraView, row, column, 1);
			int b = (int)get_pixel(cameraView, row, column, 2);
			
			//FINDING TARGET POSITION
			if(targetCoordinates[0] == -1 && targetCoordinates[1] == -1){
				//WHITE DETECTION
				//All rgb values greater than 240 indicate a white pixel
				if(r > 240 && g > 240 && b > 240){
					if(xTarget1 == -1 && yTarget1){
						xTarget1 = column;
						yTarget1 = row;
					}
					xTarget2 = column;
					yTarget2 = row;
				}
				targetCoordinates[0] =  (xTarget2 - xTarget1) / 2;
				targetCoordinates[1] =  (yTarget2 - yTarget1) / 2;
			}
		}
	}
	
	int xRobot = cameraView.width / 2;
	int yRobot = cameraView.height -1;
	int xTarget = targetCoordinates[0];
	int yTarget = targetCoordinates[1];
	int distX = xTarget - xRobot;
	int distY = yRobot - yTarget;
	double theta = atan(distX / distY);
	
	return theta;
}

/**
* Returns coordinates on red wall that robot is aiming for
* The coordinates are offset so that the robot moves alongside the wall, not on it
*/
double GetRedTarget() {
    int targetCoordinates[2] = {-1, -1};
	
	int xTarget1 = -1;
	int yTarget1 = -1;
	int xTarget2 = -1;	
	int yTarget2 = -1;
	
	for(int row =0 ; row < cameraView.height; row++){
		for(int column = 0; column < cameraView.width ; column++){
			int r = (int)get_pixel(cameraView, row, column, 0);
			int g = (int)get_pixel(cameraView, row, column, 1);
			int b = (int)get_pixel(cameraView, row, column, 2);
			
			//FINDING TARGET POSITION
			if(targetCoordinates[0] == -1 && targetCoordinates[1] == -1){
				//RED DETECTION
				//Red twice as large as both green and blue indicates a red pixel
				if(r > 2 * b && r > 2 * g){
					if(xTarget1 == -1 && yTarget1){
						xTarget1 = column;
						yTarget1 = row;
					}
					xTarget2 = column;
					yTarget2 = row;
				}
				targetCoordinates[0] =  (xTarget2 - xTarget1) / 2;
				targetCoordinates[1] =  (yTarget2 - yTarget1) / 2;
			}
		}
	}
	targetCoordinates[0] += 20; //Offset
	targetCoordinates[1] += 20; //Offset
	
	int xRobot = cameraView.width / 2;
	int yRobot = cameraView.height -1;
	int xTarget = targetCoordinates[0];
	int yTarget = targetCoordinates[1];
	int distX = xTarget - xRobot;
	int distY = yRobot - yTarget;
	double theta = atan(distX / distY);
	
	return theta;
}

/**
*If HasWhiteLine, GetWhiteTarget, and calculate degree adjustment to center offset to white line
*Else GetRedTarget, and calculate degree adjustment to center robot offset to left red line
*Return direction to adjust by in degrees
* */
double AnalyseImage() {
	if(HasWhiteLine() == 1){
		return GetWhiteTarget();
	}
	else if(HasRedLine() == 1){
		return GetRedTarget();
	}
	else{
	    return 0;
    }
}

/**
*Given input degrees, adjust motor speeds.
*/
void AdjustRobot(double adjustmentdegrees) {
  // theta = adjustmentdegrees
  // Setspeed(x,y)
  //theta = adjustmentdegrees;
  setMotors(adjustmentdegrees, -adjustmentdegrees);
}

/**
*Do "step", drive at current motor speeds
*/
void DriveRobot() {
  // theta = current_direction
  // y = sin theta 
  // x = cos theta
  Setspeed(180,180)
}

/**
*Main loop:
*>AnalyseImage return direction change in degrees
*>AdjustRobot(AnalyseImage)
*>Conditionals, if colliding, win lose
*>DriveRobot()
*/
//int main() {
  // pixel_array = TakePicture();
  // adjustment_degrees = AnalyseImage(pixel_array);
  // AdjustRobot(adjustment_degrees)
  // Conditionals, if(HasFinish()) etc
  // End loop
//}

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
		DriveRobot();
		std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
		sleep(10000);
		if (HasFinish() == 1) {
			running = 0;
		}
	}
}
