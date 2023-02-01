// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT5L 
// Names: ALIF | FARID | 
// IDs: 1211103373 | 1211103085 | 
// Emails: 1211103373@student.mmu.edu.my | 1211103085@student.mmu.edu.my | 
// Phones: 0174622108 | 01120975650 | 
// ********************************************************* 

#include "pf/helper.h"
#include <iostream>
#include <dos.h>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <cstdlib> 
#include <iomanip> 
using namespace std;

int noOfcolumn = 5 ,noOfrow = 5 , zombies = 1;
string name_setting = "Default Settings", title_spaces = "";

class game //column = column , row = row
{
    private:
        vector<vector<char>> map_; 
        int column_, row_; 
    public:
        int column, row;
        int x, y, x_, y_;
        int oddnum_row, oddnum_column, zombie_num;
        char yesno;
        int row_true = 0, column_true = 0, zombie_true = 0;
        
        game(int column = noOfcolumn , int row = noOfrow);
        void init(int column, int row);
        void display() const;
};

game::game(int column, int row)
{
    init(column, row); 
}

void game::init(int column, int row)
{
    column_ = column;
    row_ = row;

    char objects[] = { '^', 'v', '>', '<', 'h', 'p', 'r', ' ', ' ', ' '}; //objects
    int noOfObjects = 10; // number of objects in the objects array

    // create dynamic 2D array using vector
    map_.resize(row_); // to create empty rows
    for (int i = 0; i < row_; ++i)
    {
        map_[i].resize(column_); // we resize each row
    }

    // put random characters in the board
    for (int i = 0; i < row_; ++i)
    {
        for (int j = 0; j < column_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }
}

void startup() // startup interface
{
    game info;
    cout << "Assignment (Part 1)" << endl;
    cout << "===================" << endl;
    cout << "Launching Alien VS Zombies...\n" << endl;

    std::cout << "Press Enter to Continue <";
    std::cin.get();
    cout << "\n" << endl;
}

void board_settings() // board size input
{
    game info;
    
    cout << "================================" << endl;
    cout << "         Board Settings" << endl;
    cout << "================================" << endl;

    while (info.row_true < 1) { // checking whether row input is odd
        cout << "How many row(s) (min. 3)? : ";
        cin >> info.oddnum_row;
        if ((info.oddnum_row % 2 == 1) && (info.oddnum_row >= 3) && (info.oddnum_row <= 21)) {
            noOfrow = info.oddnum_row;
            info.row_true = 1;
        }
         else {
            cout << "Please enter odd numbers only (minimum 3)!!!" << endl << endl; // if user input is even number
        }
    }
    while (info.column_true < 1) { // checking whether column input is odd
        cout << "How many column(s)? (min. 3): ";
        cin >> info.oddnum_column;
        if ((info.oddnum_column % 2 == 1) && (info.oddnum_column >= 3) && (info.oddnum_column <= 21)) {
            noOfcolumn = info.oddnum_column;
            info.column_true = 1;
        } else {
            cout << "Please enter odd numbers only (minimum 3)!!!" << endl << endl; // if user input is even number
        }
    }
}

void zombie_settings() // zombie input
{
    game info;
    
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

void default_settings() // display default setting interface
{
    game info;
    game go;

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
        board_settings();
        zombie_settings();
        name_setting = "Current Settings";

        default_settings();
    }
    else if (info.yesno == 'n') { // if input is no
        cout << "Launching Game...\n" << endl;
        go.game::display();
    }
}

void game::display() const
{
    game info;
    for (int j = 0; j < column_; ++j) // header
    {
        cout << "====";
    }
    cout << "========" << endl;
    
    cout << "  Alien Vs Zombies" << endl;

    for (int j = 0; j < column_; ++j) // divider
    {
        cout << "====";
    }
    cout << "========" << endl;

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
        for (int j = 0; j < column_; ++j)
        {
            cout << " | " << map_[i][j];
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

    // divider
    for (int j = 0; j < column_; ++j)
    {
        cout << "====";
    }
    cout << "========" << endl;
}

int main()
{
    startup();
    default_settings();
}