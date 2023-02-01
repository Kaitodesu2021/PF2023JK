# Part 1

## Video Demo

Please provide the YouTube link to your [Video Demo](https://youtube.com).

### Completed

1. Display Default Settings
2. Allow users to change default settings as many times
3. Title changes from default settings to board settings
4. Display row, column, and zombie numbers from users input
5. Display board dimension from users input
6. Display borders that suits the board
7. Display row numbers and column on board
8. Randomize object spawned on board

### To Do

1. Alien features
2. Zombie attack and movement features
3. Arrow features
4. Pod features
5. Rock features
6. Health features
7. Stat display features
8. Load & Save features

## Additional Features

No additional features yet.

## Contributions

### Alif

1. Created github repository
2. Manage to display board dimension from users input
3. Manage to display row, column, and zombie numbers from users input
4. Created the algorithm for randomizing object spawned on board
5. Manage to display row numbers on the board
6. Record and upload video demo to Youtube
### Farid

1. Created the display for Default Settings & Board Settings
2. Created the algorithm board settings
3. Created the algorithm to allow users to change settings as many times
4. Improved setting title interface i.e Default Settings to Current Settings 
5. Manage to display borders that suits the boards column
6. Manage to display column numbers on the board

## Problems Encountered & Solutions

## Current Problem Encountered and plan for solution

1. Alien

One of the problem that our team encountered now is on how to implement the Alien inside the board. We already have everything else set up like 
board dimension and etc, but we are still finding ways to implement the Alien. First, we have to find a way to put the Alien in the middle of the 
board. Our plan to solve this problem is to take users row and column input, and try to divide each by 2 to the power of ceiling. This will give
us the middle part of row and column, the coordinate of the Alien to spawn.

## Past Problem Encountered and Solved

1. Displaying row, column and zombies numbers on the settings

First, we were confused on why when running the program, it display a really strange numbers eventhough we have define a starting variable for
row, column and zombies in the class. We tried many ways to get the result we want while also make it flexible for users to implement their input 
and manipulate the variable. We then find a way by just defining it not in class but outside of it. This simple changeshelped us get the result 
we wanted.