// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT5L 
// Names: MEMBER_NAME_1 | MEMBER_NAME_2 | MEMBER_NAME_3 
// IDs: MEMBER_ID_1 | MEMBER_ID_2 | MEMBER_ID_3 
// Emails: MEMBER_EMAIL_1 | MEMBER_EMAIL_2 | MEMBER_EMAIL_3 
// Phones: MEMBER_PHONE_1 | MEMBER_PHONE_2 | MEMBER_PHONE_3 
// ********************************************************* 

#include "pf/helper.h"
#include <iostream>
#include <dos.h>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <iomanip> // for setw()
using namespace std;

class game //column = column , row = row
{
    private:
        vector< vector<char> > map_; // convention to put trailing underscore
        int column_, row_; // to indicate private data
    public:
        int column, row;
        int x, y, x_, y_;
        int zombies = 1;
        char yesno;

        game(int column = 5, int row = 5);
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

    char objects[] = { '^', 'v', '>', '<', 'h', 'p', 'r', ' ', ' ', ' '};
    int noOfObjects = 10; // number of objects in the objects array

    // create dynamic 2D array using vector
    map_.resize(row_); // create empty rows
    for (int i = 0; i < row_; ++i)
    {
        map_[i].resize(column_); // resize each row
    }

    // put random characters into the vector array
    for (int i = 0; i < row_; ++i)
    {
        for (int j = 0; j < column_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }
}

void startup() 
{
    game info;
    cout << "Assignment (Part 1)" << endl;
    cout << "===================" << endl;
    cout << "Launching Alien VS Zombies...\n" << endl;

    std::cout << "Press Enter to Continue <";
    std::cin.get();
    cout << "\n" << endl;

    cout << "================================" << endl;
    cout << "        Default Settings" << endl;
    cout << "================================" << endl;
    cout << "Board Rows      : "<< info.row << endl;
    cout << "Board Columns   : "<< info.column << endl;
    cout << "Zombie(s) Count : "<< info.zombies << endl;
    cout << "================================" << endl;
}

void settings()
{

    game info;
    game go;

    cout << "Change Settings? (y/n) : ";
    cin >> info.yesno;

    if (info.yesno == 'y') {
        cout << "How many row(s)? :" << endl;
        cin >> info.y_;


        cout << "How many column(s)? :" << endl;
        cin >> info.x_;

        go.game::display();
    }
    else if (info.yesno == 'n') {
        cout << "Launching Game...\n" << endl;
        go.game::display();
    }
}

void game::display() const
{
    // header
    game info;
    for (int j = 0; j < column_; ++j)
    {
        cout << "====";
    }
    cout << "====" << endl;
    cout << "> Alien Vs Zombies" << endl;

    // divider
    for (int j = 0; j < column_; ++j)
    {
        cout << "====";
    }
    cout << "====" << endl;

    // for each row
    for (int i = 0; i < row_; ++i)
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
    cout << "  ";
    for (int j = 0; j < column_; ++j)
    {
        cout << "   " << (j + 1) % 10;
    }
    cout << endl;

    // divider
    for (int j = 0; j < column_; ++j)
    {
        cout << "====";
    }
    cout << "====" << endl;
}

int main()
{
    startup();
    settings();
}