//Headers
#include "robot.hpp"

//Namespace
using namespace std;

//Function Declarations

//Field Declarations


/**
* Check if white line exists in given image, return 0 (bad) 1 (good)
*/
int HasWhiteLine(pixel_array) {
  // for pixels in pixel_array, find white continuous row
  // if continuous row, 1, else 0
}

/**
* Check if checker black flag exists in given image
*/
int HasFinish(pixel_array) {
  // for pixels in pixel_array, find red/white continuous row
  // if continuous row, 1, else 0
}

/**
* Returns pixel distance from center of given image to nearest white line, as xy
*/
int[] GetWhiteTarget(pixel_array) {
  // for pixels in pixel_array, find center pixel of each row of white
  // find center of center of white, get degrees to change by
}

/**
* Returns pixel distance from center of given image to nearest red line
*/
int GetRedTarget(pixel_array) {
  // for pixels in pixel_array, find first center pixel of each row of red (to find leftmost)
  // find center of center of red, get degrees to change by (with offset)
}

/**
*If HasWhiteLine, GetWhiteTarget, and calculate degree adjustment to center offset to white line
*Else GetRedTarget, and calculate degree adjustment to center robot offset to left red line
*Return direction to adjust by in degrees
* */
double AnalyseImage(pixel_array) {
  // If HasWhiteLine, theta = GetWhiteTarget
  // Else theta = GetRedTarget
  // return theta
}

/**
*Given input degrees, adjust motor speeds.
*/
void AdjustRobot(double adjustmentdegrees) {
  theta = adjustmentdegrees;
  if (theta <= 180) {
	  set_Motors(1, 0);
  } 
  else {
	  set_Motors(0,1);
  }
}

/**
*Do "step", drive at current motor speeds
*/
void DriveRobot() {
  set_Motors(1, 1);
  
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
    double vLeft = 40.0;
    double vRight = 30.0;
    takePicture();
    SavePPMFile("i0.ppm",cameraView);
    while(1){
      setMotors(vLeft,vRight);   
      std::cout<<" vLeft="<<vLeft<<"  vRight="<<vRight<<std::endl;
       usleep(10000);
  } //while

} // main
