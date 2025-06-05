Thank you for checking out my project.

** STEPS TO PLAY GAME **

1. Download files and open VSCode.
2. In VSCode, select File >> Open Folder then choose the folder that has all the files you downloaded from step 1.
3. Open a new terminal and type "./cardgame.exe" (for MacOS, dont type '.exe' at the end) which will open the game in the console.


**** TROUBLESHOOTING ************************************************************************************

If Step 3 does not work, in the terminal copy and paste:

    g++ cardgame.cpp card.cpp player.cpp display.cpp hand_evaluator.cpp -std=c++17 -Wall -Wextra -g -o cardgame

and run it. That should build the game. Then depending on your system (either 1 or 2 should work):

1) For MacOS, in the terminal type     ./cardgame


2) On Git Bash type:     ./cardgame.exe


and then run again. That should execute the game to function.

**********************************************************************************************************


Description:
This is a project that utilizes course material from Texas A&M's Data Structures and Algorithms course
to showcase what I have learned.

This is a terminal-based poker simulation utilizing C++ with ASCII-based user interface.
Implemented using object-oriented programming principles, including the Rule of Three, dynamic memory allocation, and batch processing.


Made by Brandon Perez. 

I hope you enjoy playing!




