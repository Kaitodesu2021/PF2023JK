// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT5L 
// Names: ALIF | FARID | 
// IDs: 1211103373 | 1211103085 | 
// Emails: 1211103373@student.mmu.edu.my | 1211103085@student.mmu.edu.my | 
// Phones: 0174622108 | 01120975650 | 
// ********************************************************* 

#include <iostream>
#include <dos.h>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <cstdlib> 
#include <ctime> 
#include <cmath>
#include<bits/stdc++.h>
#include <iomanip> 
using namespace std;

int noOfcolumn = 5 ,noOfrow = 5 , zombies = 1, action;
string name_setting = "Default Settings", title_spaces = "";

class Game //column = column , row = row
{
    private:
        vector<vector<char>> map_; 
        int column_, row_;
    public:
        int x_axis, y_axis;
        int column, row;
        int x, y, x_, y_;
        int oddnum_row, oddnum_column, zombie_num;
        char yesno;
        int action_input;
        int row_true = 0, column_true = 0, zombie_true = 0;
        
        Game(int column = noOfcolumn , int row = noOfrow);
        void init(int column, int row);
        void startup() const, default_settings() const, board_settings() const, zombie_settings() const;
        void zombie() const;
        void display() const, divider() const;
        void action() const;
        void move_alien(char direction);
};

Game::Game(int column, int row)
{
    init(column, row); 
}

void Game::init(int column, int row)
{
    column_ = column;
    row_ = row;

    char objects[] = {'^', 'v', '>', '<', 'h', 'p', 'r', ' ', ' ', ' '}; //objects
    char zombies_array[] = {'1'}; //zombies

    int noOfObjects = 10; // number of objects in the objects array

    // create dynamic 2D array using vector
    map_.resize(row_); // to create empty rows
    for (int i = 0; i < row_; ++i)
    {
        map_[i].resize(column_); // we resize each row
    }

    // put random characters into dimensional vector array
    for (int i = 0; i < row_; ++i)
    {
        for (int j = 0; j < column_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }

    x_axis = column_ / 2;
    y_axis = row_ / 2;
    map_[y_axis][x_axis] = 'A';
}

void Game::startup() const // startup interface
{
    Game info;
    cout << "Assignment (Part 1)" << endl;
    cout << "===================" << endl;
    cout << "Launching Alien VS Zombies...\n" << endl;

    std::cout << "Press Enter to Continue <";
    std::cin.get();
    cout << "\n" << endl;
}

void Game::board_settings() const // board size input
{
    Game info;
    
    cout << "================================" << endl;
    cout << "         Board Settings" << endl;
    cout << "================================" << endl;

    while (info.row_true < 1) { // checking whether row input is odd
        cout << "How many row(s) (min. 3)? : ";
        cin >> info.oddnum_row;
        if ((info.oddnum_row % 2 == 1) && (info.oddnum_row >= 3) && (info.oddnum_row <= 13)) {
            noOfrow = info.oddnum_row;
            info.row_true = 1;
        }
         else {
            cout << "Please enter odd numbers only (min 3/max 13)!!!" << endl << endl; // if user input is even number
        }
    }
    while (info.column_true < 1) { // checking whether column input is odd
        cout << "How many column(s)? (min. 3): ";
        cin >> info.oddnum_column;
        if ((info.oddnum_column % 2 == 1) && (info.oddnum_column >= 3) && (info.oddnum_column <= 13)) {
            noOfcolumn = info.oddnum_column;
            info.column_true = 1;
        } else {
            cout << "Please enter odd numbers only (min 3/max 13)!!!" << endl << endl; // if user input is even number
        }
    }
}

void Game::move_alien(char direction) 
{
    Game game;
    map_[y_axis][x_axis] = '.'; // change the original coordinates to '.'

    if ((direction == 'w') && (y_axis > 0)) {
        while (y_axis > 0)
        {
        y_axis--; //go up
        }
    }
    else if ((direction == 's') && (y_axis < noOfcolumn - 1)) {
        while (y_axis < noOfcolumn - 1) {
        y_axis++; //go down
        }
    }
    else if ((direction == 'a') && (x_axis > 0)) {
        while (x_axis > 0) {
        x_axis--; //go left
        }
    }
    else if ((direction == 'd') && (x_axis < noOfrow - 1)) {
        while (x_axis < noOfrow - 1) {
        x_axis++; //go right
        }
    }
    else {
        cout << "Please enter accepted input only!!! (w/a/s/d)" << endl;
        game.display();
    }

    map_[y_axis][x_axis] = 'A';
}

void Game::zombie_settings() const // zombie input
{
    Game info;
    
    cout << "================================" << endl;
    cout << "         Zombie Settings" << endl;
    cout << "================================" << endl;

    while (info.zombie_true < 1) { // checking whether input is between 1-9
        cout << "How many Zombie(s) (1-9)? : ";
        cin >> info.zombie_num;
        if ((0 < info.zombie_num) && (info.zombie_num < 10)) {
            zombies = info.zombie_num;
            info.zombie_true = 1;
        } else {
            cout << "Please enter betweeen 1-9 only!!!" << endl << endl; //range for number of zombies
        }
    }
}

void Game::default_settings() const // display default setting interface
{
    Game info;

    cout << "================================" << endl;
    cout << "        " << name_setting << endl;
    cout << "================================" << endl;
    cout << "Board Rows      : "<< noOfrow << endl;
    cout << "Board Columns   : "<< noOfcolumn << endl;
    cout << "Zombie(s) Count : "<< zombies << endl;
    cout << "================================" << endl;

    cout << "Change " << name_setting << "? (y/n) : ";
    cin >> info.yesno;

    if (info.yesno == 'y') { // if input is yes
        Game::board_settings();
        Game::zombie_settings();
        name_setting = "Current Settings";

        Game::default_settings();
    }
    else if (info.yesno == 'n') { // if input is no
        cout << "Launching Game...\n" << endl;
        info.Game::display();
    }
}

void Game::divider() const
{
    for (int j = 0; j < column_; ++j)
    {
        cout << "====";
    }
    cout << "========" << endl;
}

void Game::action() const //asking player to pick action
{
    Game game;
    char direction;
    int choices;
    cout << "1. Move Alien" << endl;
    cout << "2. Move Arrow" << endl;
    cout << "3. Exit Game" << endl;
    cout << "Pick action: ";
    cin >> choices;
    Game::divider();

    if (choices == 1) {
        cout << "Enter direction (w, a, s, d): ";
        cin >> direction;
        cout << endl;
        game.move_alien(direction);
        game.display();
    }
    else if (choices == 2) {
        cout << "Not Updated for option 2\n";
        Game::divider();
        Game::action();
    }
    else if (choices == 3){
        cout << "Exiting game...\n";
        exit(0);
        Game::divider();
    }
    else {
        cout << "Not Updated\n";
    }
}

void Game::display() const
{
    Game info;

    Game::divider();
    cout << "  Alien Vs Zombies" << endl;
    Game::divider();

    for (int i = 0; i < row_; ++i) // for each row
    {
        // display upper border of the row
        cout << "   ";
        for (int j = 0; j < column_; ++j)
        {
            cout << "+---";
        }
        cout << "+" << endl;

        // display row number
        cout << setw(2) << (row_ - i);

        // display cell content and border of each column
        cout << "";

        int midrow = noOfrow / 2;
        int midcolumn = noOfcolumn / 2;

        for (int j = 0; j < column_; ++j)
        {
            cout << " | ";
            // if ((i == midrow) && (j == midcolumn)) { // alien spawnpoint
            //     cout << "A";
            // }
            // else {
            cout << map_[i][j]; // other objects
            // }  
        }
        cout << " |" << endl;
    }

    // display lower border of the last row
    cout << "   ";
    for (int j = 0; j < column_; ++j)
    {
        cout << "+---";
    }
    cout << "+" << endl;

    // display column number
    if (noOfcolumn > 9) { // changing spacing when column > 9
    cout << "  "; 
    for (int j = 0; j < column_; ++j) // first row
    {
        int digit = (j + 1) / 10;
        cout << "   ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << "  ";
    for (int j = 0; j < column_; ++j) // second row
    {
        cout << "   " << (j + 1) % 10;
    }
    cout << endl;
    }
    else { // when column < 9
    cout << "  ";
    for (int j = 0; j < column_; ++j) // first row 
    {
        cout << "   " << (j + 1) % 10;
    }
    cout << endl;
    }

    Game::divider();

    Game::action(); //go to action tab
}

int main()
{
    srand(time(NULL));

    Game game;
    game.startup();
    game.default_settings();
}