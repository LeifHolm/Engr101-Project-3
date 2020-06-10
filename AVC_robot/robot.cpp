//Headers
#include "robot.hpp"
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
  // for pixels in pixel_array, find red/white continuous row
  // if continuous row, 1, else 0
  return 0;
}

/**
* Returns pixel distance from center of given image to nearest white line, as xy
*/
double GetWhiteTarget() {
  // for pixels in pixel_array, find center pixel of each row of white
  // find center of center of white, get degrees to change by
  return 0;
}

/**
* Returns pixel distance from center of given image to nearest red line
*/
double GetRedTarget() {
  // for pixels in pixel_array, find first center pixel of each row of red (to find leftmost)
  // find center of center of red, get degrees to change by (with offset)
  return 0;
}

/**
*If HasWhiteLine, GetWhiteTarget, and calculate degree adjustment to center offset to white line
*Else GetRedTarget, and calculate degree adjustment to center robot offset to left red line
*Return direction to adjust by in degrees
* */
double AnalyseImage() {
  // If HasWhiteLine, theta = GetWhiteTarget
  // Else theta = GetRedTarget
  // return theta
  ///Target detection logic here
  if(HasWhiteLine()) {
	  return GetWhiteTarget();
  } else {
	  return GetRedTarget();
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
  // Setspeed(x,y)
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
	while(running = 1){
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
