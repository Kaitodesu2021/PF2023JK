# Part 2

## Video Demo

Please provide the YouTube link to your [Video Demo](https://youtube.com).

## Minimum Requirements

### Completed

List all the features completed.

1. Display Default Settings
2. Allow users to change default settings as many times
3. Title changes from default settings to board settings
4. Display row, column, and zombie numbers from users input
5. Display board dimension from users input
6. Display borders that suits the board
7. Display row numbers and column on board
8. Randomize object spawned on board
9. Display correct spacing for Title in gameboard
10. Display Alien in the middle
11. Alien being able to move in 1 straight line but once

### To Do

List all the features not yet done. Remove this section if there is no incomplete requirements.

1. Full Alien features
2. Zombie attack and movement features
3. Arrow features
4. Pod features
5. Rock features
6. Health features
7. Stat display features
8. Load & Save features

## Additional Features

No additional features.

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
7. Manage to display correct spacing for Title on gameboard
8. Created the algorithm to move Alien once and leave trails
9. Created algorithm for action choices

## Problems Encountered & Solutions

1. Alien & Board

For the Alien, we manage to insert and display the Alien correctly in the middle part of our map and manage to make it move in one straight lines 
while also leaving trails behind. However, after we make the second move to the Alien, it revert itself to the middle once again and then it moves.
This causes the alien to reset it position and move from the middle once again and not from the new coordination it was in from previous action.
We have found the problem, the culprit comes from the init function that kept on initializing everytime a function was called. In the init function,
lies our algorithm to put Alien in the middle. Because this init function kept on repeating, so does the Alien kept on moving back to the middle
every single function execution. We have tried many ways to counter the problem but failed. The idea was to move this Alien spawnpoint algorithm
from the init function but we still have not figure how. We have tried many ways but to no prevail.

For the board, since this problem also correlates with the problem above, the initialization always kept on repeating itself so it kept on changing
the objects on the map everytime we execute a new movement (or a function to be precise). Thus, changing the map objects everytime. We have tried
to find a way to stop the new shuffling of randomize object but we failed to figure how to do it.