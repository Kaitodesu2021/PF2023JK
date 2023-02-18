#include <iostream>
#include <dos.h>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <cstdlib> 
#include <ctime> 
#include <cmath>
#include <iomanip> 

using namespace std;

int noOfcolumn = 5, noOfrow = 5, zombies = 1, action;
string name_setting = "Default Settings", title_spaces = "";

class Game //column = column , row = row
{
    private:
        vector<vector<char>> map_; 
        int column, row; 
    public:
        int column_, row_;
        int x, y, x_, y_;
        int oddnum_row, oddnum_column, zombie_num;
        char yesno;
        int action_input;
        int row_true = 0, column_true = 0, zombie_true = 0;

        Game(int column = noOfcolumn, int row = noOfrow);
        void init(int column, int row);
        void startup() const, default_settings() const, board_settings() const, zombie_settings() const;
        void mergeArrays(int objects[], int zombies_array[], int noOfobjects, int zombies, int new_objects[]);
        void zombie() const;
        void display() const, divider() const;
        void action() const;
};

class Alien
{
    private:
        vector<vector<char>> map2; 
        int x_, y_;
    public:
        char heading_; //either '^', '>', '<', 'v'
        Alien();
        void land(Game &game);
        void moveUp(Game &game);
        void moveDown(Game &game);
        void moveLeft(Game &game);
        void moveRight(Game &game);
        int getX() const;
        int getY() const;
        char getHeading() const;
};

Alien::Alien()
{    
}

void Alien::land(Game &game)
{
    Alien info;
    x_ = game.row_ / 2;
    y_ = game.column_ / 2;
    info.heading_ = '^';
    map2[x_][y_] = heading_;
}

void Alien::moveUp(Game &game)
{
    if (x_ > 0) {
        map2[x_][y_] = ' ';
        x_--;
        map2[x_][y_] = heading_;
    }
}

void Alien::moveDown(Game &game)
{
    if (x_ < game.row_ - 1) {
        map2[x_][y_] = ' ';
        x_++;
        map2[x_][y_] = heading_;
    }
}

void Alien::moveLeft(Game &game)
{
    if (y_ > 0) {
        map2[x_][y_] = ' ';
        y_--;
        map2[x_][y_] = heading_;
    }
}

void Alien::moveRight(Game &game)
{
    if (y_ < game.column_ - 1) {
        map2[x_][y_] = ' ';
        y_++;
        map2[x_][y_] = heading_;
    }
}

int Alien::getX() const
{
    return x_;
}

int Alien::getY() const
{
    return y_;
}

char Alien::getHeading() const
{
    return heading_;
}

Game::Game(int column, int row)
{
    init(column, row); 
}

void Game::init(int column, int row)
{
    column_ = column;
    row_ = row;
    map_.resize(row_, vector<char>(column_, ' '));
}


void Game::mergeArrays(int objects[], int zombies_array[], int noOfobjects, int zombies, int new_objects[]) // merge arrays for randomisation
{
for (int i = 0; i < noOfobjects; i++)
{
new_objects[i] = objects[i];
}
for (int i = noOfobjects; i < zombies + noOfobjects; i++)
{
new_objects[i] = zombies_array[i - noOfobjects];
}
}

void Game::zombie() const // create zombies randomly
{
srand(time(0));
int zombies_array[9];
int new_objects[19];
}

void Game::display() const // display the map
{
for (int i = 0; i < row_; ++i)
{
for (int j = 0; j < column_; ++j)
{
cout << setw(3) << map_[i][j];
}
cout << endl;
}
}

void Game::divider() const // create divider for better interface
{
cout << "\n";
cout << "==========================================" << endl;
cout << "\n";
}

void Game::action() const // action interface
{
Game info;
cout << "================================" << endl;
cout << " Alien Actions" << endl;
cout << "================================" << endl;
cout << "(1) Move Up" << endl;
cout << "(2) Move Down" << endl;
cout << "(3) Move Left" << endl;
cout << "(4) Move Right" << endl;
cout << "(5) Exit Game" << endl;
cout << "\n" << endl;
}