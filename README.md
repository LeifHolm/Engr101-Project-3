# Engr101-Project-3

PROJECT PLAN

Group Members:

Aslan Bennington-Barr
Joel Crampton
Leif Holm
Rhys Kill

Communication is done through Facebook Messenger

Group Roles:

Project Manager - Rhys
Software Architect - Aslan
Software Writing, Testing and Documentation - Joel
Software Writing, Testing and Documentation - Leif

GitHub link - https://github.com/LeifHolm/Engr101-Project-3

Major Milestones will be every Friday

Thursday 4th June - Rhys will finish the plan in the readme.
Friday 5th June - Everyone will have the SFML Libraries set up and ready for use. Aslan will create the initial commits in the repository for the necessary files.
Friday 12th June - Core/Completion code to be completed. Aslan will have finished planning the architecture of the code. The weekly wiki discussion will be completed on the 12th.
Friday 19th June - Challenge code to be completed and all code and related content will be submitted. The weekly wiki discussion will be completed on the 19th.
Wednesday 24th June - All individual logs, team logs and the final report.

Installation Instructions for Windows

Install Mingw and Geany
Go to https://www.sfml-dev.org/download/sfml/2.5.1/ and download GCC 7.3.0 MinGW (DW2) - 32-bit.
Unzip the folder into a location of your choosing.
Create a folder for the installation.
On the github repository page, click clone or download then click download ZIP.
Unzip the folder into the installation folder.
Go into AVC_robot and open the file named makefile in a text editor.
In the top two lines change the current directory to the directory that you installed the SFML file to.
Do the same process for the makefile in the AVC_server folder.
Open server.cpp in the AVC_server folder and robot.cpp in the AVC_robot folder with Geany.
Open the build dropdown and click set build commands.
Change the make command to mingw32-make.
Make both the robot.cpp and server.cpp.
Navigate to the AVC_server folder and open server.exe.
Navigate to the AVC_robot folder and open robot.exe.
The program should now be running.
