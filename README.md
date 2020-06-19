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

Installation Instructions for Windows 10

Head to https://osdn.net/projects/mingw/releases/ and download the mingw-get-setup.exe.

Run the mingw-get-setup.exe and follow the onscreen prompts to install the Installation Manager.

Once installed, run the MingW installation manager.

Navigate to the basic set up and install the following packages: 
- mingw-developer-toolkit-bin
- mingw32-base-bin
- mingw32-gcc-objc-bin

Locate the MinGW folder on your computer. It is most likely located in C:\ or C:\Program Files (x86).

Once located navigate to the start menu and type "environment" and open Edit the System Environment Variables.

Once open click Environment Variables and under System Variables double click on the Variable "Path".

Click new and type in the directory of the bin folder within the MinGW folder.

Press OK to apply the changes.

To test the MingW installation open command prompt and type mingw32-make. You should get the line - mingw32-make: *** No targets specified and no makefile found.  Stop.

Head to https://www.geany.org/download/releases/ and download geany-1.36_setup.exe.

Run the geany-1.36_setup.exe and follow the onscreen instructions to install geany.

Go to https://www.sfml-dev.org/download/sfml/2.5.1/ and download GCC 7.3.0 MinGW (DW2) - 32-bit.

Unzip the folder into a location of your choosing.

Create a folder for the installation.

On the github repository page, click clone or download then click download ZIP.

Unzip the folder into the installation folder.

Go into AVC_robot and open the file named makefile in a text editor.

In the top two lines change the current directory to the directory path that you installed the SFML file to.

Do the same process for the makefile in the AVC_server folder.

Copy all the .dll files from the SFML\bin folder into the AVC_server folder and when prompted click replace the files in the destination.

Open server.cpp in the AVC_server folder and robot.cpp in the AVC_robot folder with Geany.

Open the build dropdown and click set build commands.

Change the make command to mingw32-make.

Make the robot.cpp and server.cpp by clicking on the drop down next to the brick labelled build and click Make All. Do this for each file.

Navigate to the AVC_server folder and open server.exe.

Navigate to the AVC_robot folder and open robot.exe.

The program should now be running.
