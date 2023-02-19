#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
#include <conio.h> //for press any key
#include <stdlib.h>
#include <fstream>
#include <utility>
using namespace std;

class AVZ
{
private:
    vector<vector<char>> map_; // convention to put trailing underscore
    int numX_, numY_;
    int currentX_, currentY_; // to indicate private data

public:
    AVZ(int rows = 5, int col = 15, int zombie = 2); // constructor with number of rows and columns
    void initArray();                                // function to intialize the array
    void displayArray() const;                       // function to display the array
    void displaySettings() const;                    // to display default game settings
    void insertRandomCharacter(char ch);
    int getDimX() const;
    int getDimY() const;
    void setRows(int rows);
    void setCol(int col);
    void setZombie(int zombie);
    void fightZombies(int zombies);
    void init(int numX, int numY);
    void moveCharacter(int currentX_, int currentY_);
    void displayAlienStatus(int &A_health, int A_attack_damage, int A_attack_range);
    void displayZombieStatus(int numZombies, int Z_health, int Z_attack_damage, int Z_attack_range);
    void resetGrid(vector<vector<char>> &grid, int &currentX, int &currentY);

    int rows_, col_;
    int zombies;
    char save, load, direction, arrow, help, quit;
};

class Alien
{
public:
    int life;
    int attack;

    Alien()
    {
        srand(time(nullptr));      // seed the random number generator
        life = rand() % 101 + 100; // life between 100 and 200
        attack = 0;                // always start from 0
    }
};

class Zombie
{
public:
    int life;
    int attack;
    int range;

    Zombie(int boardSize)
    {
        srand(time(nullptr));                 // seed the random number generator
        life = rand() % 101 + 200;            // life between 200 and 300
        attack = rand() % (life + 1);         // attack between 0 and life
        range = rand() % (boardSize / 2) + 1; // range between 1 and half of boardSize
    }
};
AVZ::AVZ(int rows, int col, int zombie)
{
    rows_ = rows;
    col_ = col;
    zombies = zombie;
    map_.resize(rows_);
    for (int i = 0; i < rows_; i++)
    {
        map_[i].resize(col_);
    }
}

void AVZ::initArray() // initialize array with some values
{
    char characters[] = {' ', ' ', ' ', ' ', ' ', 'r', '^', '>', '<', 'v', 'p', 'h'};
    int noOfObjects = 12;

    for (int i = 0; i < map_.size(); i++)
    {
        for (int j = 0; j < col_; j++)
        {
            map_[i][j] = characters[rand() % 5];
        }
    }

    for (int i = 0; i < map_.size(); i++)
    {
        for (int j = 0; j < col_; j++)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = characters[objNo];
        }
    }
    int centerRow = rows_ / 2;
    int centerCol = col_ / 2;
    map_[centerRow][centerCol] = 'A';
}

void AVZ::displayAlienStatus(int &A_health, int A_attack_damage, int A_attack_range)
{

    cout << "Alien Status  >>>";
    cout << " ";
    cout << "Health: " << A_health;

    cout << " ";
    cout << "| Attack Damage: " << A_attack_damage;
    cout << " ";
    cout << "| Attack Range: " << A_attack_range << endl;
}

void AVZ::displayZombieStatus(int numZombies, int Z_health, int Z_attack_damage, int Z_attack_range)
{

    for (int i = 0; i < numZombies; i++)
    {
        cout << "Zombie Status"
             << " " << i + 1 << ">>>";
        cout << " ";
        cout << "Health: " << Z_health;
        cout << " ";
        cout << "| Attack Damage: " << Z_attack_damage;
        cout << " ";
        cout << "| Attack Range: " << Z_attack_range << endl;
    }
}

void AVZ::fightZombies(int zombies) {
    // Generate the alien's life value
    srand(time(NULL)); // seed the random number generator
    int alienLife = rand() % 101 + 100; // life between 100 and 200
    int alienAttack = 0; // Setting the alien's attack value to zero

    // Loop over the zombies
    for (int i = 1; i <= zombies; i++)
    {
        // Generate the zombie's life, attack, and range values
        int zombieLife = rand() % 101 + 100; // generate random life value between 100 and 200
        int zombieAttack = rand() % 11 + 90; // generate random attack value between 90 and 100
        int zombieRange = rand() % 5 + 1;

        // Output the zombie's information
        cout << "Zombie " << i << "    Life:  " << zombieLife << "    Attack:  " << zombieAttack << " Range:     " << zombieRange << endl;
    }

    // Output the alien's information
    cout << "Alien       Life: " << alienLife << "   Attack:" << alienAttack << endl;
}

void AVZ::resetGrid(vector<vector<char>> &grid, int &currentX, int &currentY)
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] == '.' && (i != currentX || j != currentY))
            {
                grid[i][j] = ' ';

                // Generate new game object (except in the Alien trail)
                srand(time(NULL)); // Initialize the random seed

                int objNo;
                do
                {
                    objNo = rand() % 4; // Generate a random game object index
                } while (objNo == 2);   // Check if the game object is not ' '

                char objects[] = {'p', 'h', 'r', ' ', ' ', ' '}; // Define the game objects
                grid[i][j] = objects[objNo];
            }
        }
    }
}

void AVZ::displayArray() const
{
    cout << " " << endl;
    cout << "~~~~~ᕙ(`▿´)ᕗ~~~~~~" << endl;
    cout << "+. Alien Vs Zombie .+" << endl;
    cout << "~~~~~ᕙ(`▿´)ᕗ~~~~~~" << endl;
    cout << " " << endl;
    // for each row
    for (int i = 0; i < map_.size(); ++i)
    {
        // display upper border of the row
        cout << " ";
        cout << " ";
        for (int j = 0; j < col_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;
        // display row number
        cout << setfill(' ') << (rows_ - i) << " ";
        // display cell content and border of each column
        for (int j = 0; j < col_; ++j)
        {
            cout << "|" << map_[i][j];
        }
        cout << "|" << endl;
    }
    // display lower border of the last row
    cout << " ";
    cout << " ";
    for (int j = 0; j < col_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;
    // display column number
    cout << " ";
    cout << " ";
    for (int j = 0; j < col_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << " ";
    cout << " ";
    for (int j = 0; j < col_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }

    cout << endl
         << endl;
}

void AVZ::insertRandomCharacter(char ch)
{
    for (int i = 0; i < map_.size(); i++)
    {
        for (int j = 0; j < map_[i].size(); j++)
        {
            // if (rand() % 2 == 0)
            //{
            //  map_[i][j] = ch;
            //}
        }
    }
}

void AVZ::displaySettings() const
{
    cout << "Board Rows   : " << rows_ << endl;
    cout << "Board Columns: " << col_ << endl;
    cout << "Zombie Count : " << zombies << endl;
}

void AVZ::setRows(int rows)
{
    rows_ = rows;
}

void AVZ::setCol(int col)
{
    col_ = col;
}

void AVZ::setZombie(int zombies)
{
    int zombiesPlaced = 0;
    while (zombiesPlaced < zombies)
    {
        int x = rand() % rows_;
        int y = rand() % col_;
        if (map_[x][y] == ' ')
        {
            map_[x][y] = '0' + (zombiesPlaced + 1) % 10;
            zombiesPlaced++;
        }
    }
}

void AVZ::moveCharacter(int rows_, int col_)
// *********************************************************
// Course: TCP1101 PROGRAMMING FUNDAMENTALS
// Year: Trimester 1, 2022/23 (T2215)
// Lab: TT5L
// Names: NUR FARAHIYA AIDA  | NUR ALIA AMELISA SYAZREEN | WAN ALIA ADLINA
// IDs: 1211103194 | 1211103602 | 1211103227
// Emails: 1211103194@student.mmu.edu.my | 1211103602@student.mmu.edu.my | 1211103227@student.mmu.edu.my
// Phones: 011-51121620 | 014-2100540 | 019-9935060
// *********************************************************

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()
#include <conio.h> //for press any key
#include <stdlib.h>
#include <fstream>
#include <utility>
using namespace std;

class AVZ
{
private:
    vector<vector<char>> map_; // convention to put trailing underscore
    int numX_, numY_;
    int currentX_, currentY_; // to indicate private data

public:
    AVZ(int rows = 5, int col = 15, int zombie = 2); // constructor with number of rows and columns
    void initArray();                                // function to intialize the array
    void displayArray() const;                       // function to display the array
    void displaySettings() const;                    // to display default game settings
    void insertRandomCharacter(char ch);
    int getDimX() const;
    int getDimY() const;
    void setRows(int rows);
    void setCol(int col);
    void setZombie(int zombie);
    void fightZombies(int zombies);
    void init(int numX, int numY);
    void moveCharacter(int currentX_, int currentY_);
    void displayAlienStatus(int &A_health, int A_attack_damage, int A_attack_range);
    void displayZombieStatus(int numZombies, int Z_health, int Z_attack_damage, int Z_attack_range);
    void resetGrid(vector<vector<char>> &grid, int &currentX, int &currentY);

    int rows_, col_;
    int zombies;
    char save, load, direction, arrow, help, quit;
};

class Alien
{
public:
    int life;
    int attack;

    Alien()
    {
        srand(time(nullptr));      // seed the random number generator
        life = rand() % 101 + 100; // life between 100 and 200
        attack = 0;                // always start from 0
    }
};

class Zombie
{
public:
    int life;
    int attack;
    int range;

    Zombie(int boardSize)
    {
        srand(time(nullptr));                 // seed the random number generator
        life = rand() % 101 + 200;            // life between 200 and 300
        attack = rand() % (life + 1);         // attack between 0 and life
        range = rand() % (boardSize / 2) + 1; // range between 1 and half of boardSize
    }
};
AVZ::AVZ(int rows, int col, int zombie)
{
    rows_ = rows;
    col_ = col;
    zombies = zombie;
    map_.resize(rows_);
    for (int i = 0; i < rows_; i++)
    {
        map_[i].resize(col_);
    }
}

void AVZ::initArray() // initialize array with some values
{
    char characters[] = {' ', ' ', ' ', ' ', ' ', 'r', '^', '>', '<', 'v', 'p', 'h'};
    int noOfObjects = 12;

    for (int i = 0; i < map_.size(); i++)
    {
        for (int j = 0; j < col_; j++)
        {
            map_[i][j] = characters[rand() % 5];
        }
    }

    for (int i = 0; i < map_.size(); i++)
    {
        for (int j = 0; j < col_; j++)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = characters[objNo];
        }
    }
    int centerRow = rows_ / 2;
    int centerCol = col_ / 2;
    map_[centerRow][centerCol] = 'A';
}

void AVZ::displayAlienStatus(int &A_health, int A_attack_damage, int A_attack_range)
{

    cout << "Alien Status  >>>";
    cout << " ";
    cout << "Health: " << A_health;

    cout << " ";
    cout << "| Attack Damage: " << A_attack_damage;
    cout << " ";
    cout << "| Attack Range: " << A_attack_range << endl;
}

void AVZ::displayZombieStatus(int numZombies, int Z_health, int Z_attack_damage, int Z_attack_range)
{

    for (int i = 0; i < numZombies; i++)
    {
        cout << "Zombie Status"
             << " " << i + 1 << ">>>";
        cout << " ";
        cout << "Health: " << Z_health;
        cout << " ";
        cout << "| Attack Damage: " << Z_attack_damage;
        cout << " ";
        cout << "| Attack Range: " << Z_attack_range << endl;
    }
}

void AVZ::fightZombies(int zombies) {
    // Generate the alien's life value
    srand(time(NULL)); // seed the random number generator
    int alienLife = rand() % 101 + 100; // life between 100 and 200
    int alienAttack = 0; // Setting the alien's attack value to zero

    // Loop over the zombies
    for (int i = 1; i <= zombies; i++)
    {
        // Generate the zombie's life, attack, and range values
        int zombieLife = rand() % 101 + 100; // generate random life value between 100 and 200
        int zombieAttack = rand() % 11 + 90; // generate random attack value between 90 and 100
        int zombieRange = rand() % 5 + 1;

        // Output the zombie's information
        cout << "Zombie " << i << "    Life:  " << zombieLife << "    Attack:  " << zombieAttack << " Range:     " << zombieRange << endl;
    }

    // Output the alien's information
    cout << "Alien       Life: " << alienLife << "   Attack:" << alienAttack << endl;
}

void AVZ::resetGrid(vector<vector<char>> &grid, int &currentX, int &currentY)
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] == '.' && (i != currentX || j != currentY))
            {
                grid[i][j] = ' ';

                // Generate new game object (except in the Alien trail)
                srand(time(NULL)); // Initialize the random seed

                int objNo;
                do
                {
                    objNo = rand() % 4; // Generate a random game object index
                } while (objNo == 2);   // Check if the game object is not ' '

                char objects[] = {'p', 'h', 'r', ' ', ' ', ' '}; // Define the game objects
                grid[i][j] = objects[objNo];
            }
        }
    }
}

void AVZ::displayArray() const
{
    cout << " " << endl;
    cout << "~~~~~ᕙ(`▿´)ᕗ~~~~~~" << endl;
    cout << "+. Alien Vs Zombie .+" << endl;
    cout << "~~~~~ᕙ(`▿´)ᕗ~~~~~~" << endl;
    cout << " " << endl;
    // for each row
    for (int i = 0; i < map_.size(); ++i)
    {
        // display upper border of the row
        cout << " ";
        cout << " ";
        for (int j = 0; j < col_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;
        // display row number
        cout << setfill(' ') << (rows_ - i) << " ";
        // display cell content and border of each column
        for (int j = 0; j < col_; ++j)
        {
            cout << "|" << map_[i][j];
        }
        cout << "|" << endl;
    }
    // display lower border of the last row
    cout << " ";
    cout << " ";
    for (int j = 0; j < col_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;
    // display column number
    cout << " ";
    cout << " ";
    for (int j = 0; j < col_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << " ";
    cout << " ";
    for (int j = 0; j < col_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }

    cout << endl
         << endl;
}

void AVZ::insertRandomCharacter(char ch)
{
    for (int i = 0; i < map_.size(); i++)
    {
        for (int j = 0; j < map_[i].size(); j++)
        {
            // if (rand() % 2 == 0)
            //{
            //  map_[i][j] = ch;
            //}
        }
    }
}

void AVZ::displaySettings() const
{
    cout << "Board Rows   : " << rows_ << endl;
    cout << "Board Columns: " << col_ << endl;
    cout << "Zombie Count : " << zombies << endl;
}

void AVZ::setRows(int rows)
{
    rows_ = rows;
}

void AVZ::setCol(int col)
{
    col_ = col;
}

void AVZ::setZombie(int zombies)
{
    int zombiesPlaced = 0;
    while (zombiesPlaced < zombies)
    {
        int x = rand() % rows_;
        int y = rand() % col_;
        if (map_[x][y] == ' ')
        {
            map_[x][y] = '0' + (zombiesPlaced + 1) % 10;
            zombiesPlaced++;
        }
    }
}

void AVZ::command(int row, int column)
{
    string command;
    int mapCols;
    int mapRows;
    int dimx;
    int dimy;
    int zombies;
    int alienLife_;
    int alienAttack_;
    int zombieLife_;
    int zombieAttack_;
    char run;
    char choice;
    char direction;
    char help;
    string fileName;
    string savefileName;
    
    // char arrow,
    // save, load, quit;

    int centerRow = row / 2;
    int centerCol = column / 2;
    map_[centerRow][centerCol] = alien;

    cout << "Are you ready to play? (y/n) = ";
    cin >> command;
    system("pause");

    if (command == "y" || command == "Y")
        while (run = true)
        {

            if (centerRow >= 0 && centerRow < row && centerCol >= 0 && centerCol < column)
            {
                map_[centerRow][centerCol] = alien;
            }
            else
            {
                std::cerr << "Error: centerRow and centerCol are out of bounds." << std::endl;
            }

            char directionAlien;
            cout << "\nEnter your command : ";
            cin >> command;

            if (command == "left" || command == "Left")
            {
                system("cls");
                display();
                for (int c = centerCol; c > 0; c--)
                {
                    map_[centerRow][centerCol] = trail;
                    centerCol -= 1;
                    if (map_[centerRow][centerCol] == 'H')
                    {
                        cout << endl;
                        cout << "Health pack is detected" << endl;
                        cout << "Alien finds a health pack." << endl;
                        cout << "Alien's life is increased by 20." << endl;
                        alienLife_ += 20;
                    }
                    else if (map_[centerRow][centerCol] == 'P')
                    {
                        map_[centerRow][centerCol] == 'P';
                        cout << endl;
                        cout << "A Pod is detected" << endl;
                        cout << "Alien finds a Pod" << endl;
                        // cout << zombie mana terdekat kena attack

                        zombieLife_ -= 10;
                    }
                    else if (map_[centerRow][centerCol] == 'R')
                    {
                        cout << endl;
                        cout << "Rock is detected" << endl;
                        cout << "Alien finds a rock" << endl;
                        system("pause");

                        // generate a ranodom number between 0 and 1
                        int random = rand() % 2;
                        if (random == 0)
                        {
                            map_[centerRow][centerCol] == 'P';
                            cout << endl;
                            cout << "A Pod appears on the rock" << endl;
                            cout << "Alien finds a pod" << endl;
                            // cout << zombie mana terdekat kena attack

                            zombieLife_ -= 10;
                        }
                        else
                        {
                            (map_[centerRow][centerCol]== 'H');
                            cout << endl;
                            cout << "A Health pack appears on the rock" << endl;
                            cout << "Alien finds a health pack." << endl;
                            cout << "Alien's life is increased by 20." << endl;

                            alienLife_ += 20;
                        }
                    }
                    else if (map_[centerRow][centerCol] == '^' || map_[centerRow][centerCol] == 'v' || map_[centerRow][centerCol] == '<' || map_[centerRow][centerCol] == '>')
                    {
                        cout << endl;
                        cout << "Arrow is detected" << endl;
                        cout << "Alien finds an arrow." << endl;
                        cout << "Alien's attack is increased by 20." << endl;
                        alienAttack_ += 20;
                        map_[centerRow][centerCol] = trail;
                    }
                    map_[centerRow][centerCol] = alien;
                    system("pause");
                    system("cls");
                    display();
                }
                break;
            }
            else if (command == "right" || command == "Right")
            {
                system("cls");
                display();
                for (int c = centerCol; c < mapCols; c++)
                {
                    map_[centerRow][centerCol] = trail;
                    centerCol += 1;
                    if (map_[centerRow][centerCol] == 'H')
                    {
                        cout << endl;
                        cout << "Health pack is detected" << endl;
                        cout << "Alien finds a health pack." << endl;
                        cout << "Alien's life is increased by 20." << endl;
                        alienLife_ += 20;
                    }
                    else if (map_[centerRow][centerCol] == 'P')
                    {
                        map_[centerRow][centerCol] == 'P';
                        cout << endl;
                        cout << "A Pod is detected" << endl;
                        cout << "Alien finds a Pod" << endl;
                        // cout << zombie mana terdekat kena attack

                        zombieLife_ -= 10;
                    }
                    else if (map_[centerRow][centerCol] == 'R')
                    {
                        cout << endl;
                        cout << "Rock is detected" << endl;
                        cout << "Alien finds a rock" << endl;
                        system("pause");

                        // generate a ranodom number between 0 and 1
                        int random = rand() % 2;
                        if (random == 0)
                        {
                            map_[centerRow][centerCol] == 'P';
                            cout << endl;
                            cout << "A Pod appears on the rock" << endl;
                            cout << "Alien finds a pod" << endl;
                            // cout << zombie mana terdekat kena attack

                            zombieLife_ -= 10;
                        }
                        else
                        {
                            (map_[centerRow][centerCol] == 'H');
                            cout << endl;
                            cout << "A Health pack appears on the rock" << endl;
                            cout << "Alien finds a health pack." << endl;
                            cout << "Alien's life is increased by 20." << endl;

                            alienLife_ += 20;
                        }
                    }
                    else if (map_[centerRow][centerCol] == '^' || map_[centerRow][centerCol] == 'v' || map_[centerRow][centerCol] == '<' || map_[centerRow][centerCol] == '>')
                    {
                        cout << endl;
                        cout << "Arrow is detected" << endl;
                        cout << "Alien finds an arrow." << endl;
                        cout << "Alien's attack is increased by 20." << endl;
                        alienAttack_ += 20;
                        map_[centerRow][centerCol] = trail;
                    }
                    map_[centerRow][centerCol] = alien;
                    system("pause");
                    system("cls");
                    display();
                }
                break;
            }
            else if (command == "up" || command == "Up")
            {
                system("cls");
                display();
                for (int r = centerRow; r > 0; r--)
                {
                    map_[centerRow][centerCol] = trail;
                    centerRow -= 1;
                    if (map_[centerRow][centerCol]  == 'H')
                    {
                        cout << endl;
                        cout << "Health pack is detected" << endl;
                        cout << "Alien finds a health pack." << endl;
                        cout << "Alien's life is increased by 20." << endl;
                        alienLife_ += 20;
                    }
                    else if (map_[centerRow][centerCol] == 'P')
                    {
                        map_[centerRow][centerCol] == 'P';
                        cout << endl;
                        cout << "A Pod is detected" << endl;
                        cout << "Alien finds a Pod" << endl;
                        // cout << zombie mana terdekat kena attack

                        zombieLife_ -= 10;
                    }
                    else if (map_[centerRow][centerCol] == 'R')
                    {
                        cout << endl;
                        cout << "Rock is detected" << endl;
                        cout << "Alien finds a rock" << endl;
                        system("pause");

                        // generate a ranodom number between 0 and 1
                        int random = rand() % 2;
                        if (random == 0)
                        {
                            map_[centerRow][centerCol] == 'P';
                            cout << endl;
                            cout << "A Pod appears on the rock" << endl;
                            cout << "Alien finds a pod" << endl;
                            // cout << zombie mana terdekat kena attack

                            zombieLife_ -= 10;
                        }
                        else
                        {
                            (map_[centerRow][centerCol] == 'H');
                            cout << endl;
                            cout << "A Health pack appears on the rock" << endl;
                            cout << "Alien finds a health pack." << endl;
                            cout << "Alien's life is increased by 20." << endl;

                            alienLife_ += 20;
                        }
                    }
                    else if (map_[centerRow][centerCol] == '^' || map_[centerRow][centerCol]  == 'v' || map_[centerRow][centerCol]  == '<' || map_[centerRow][centerCol] == '>')
                    {
                        cout << endl;
                        cout << "Arrow is detected" << endl;
                        cout << "Alien finds an arrow." << endl;
                        cout << "Alien's attack is increased by 20." << endl;
                        alienAttack_ += 20;
                        map_[centerRow][centerCol] = trail;
                    }
                    map_[centerRow][centerCol] = alien;
                    system("pause");
                    system("cls");
                    display();
                }
                break;
            }
            else if (command == "down" || command == "Down")
            {
                system("cls");
                display();
                for (int r = centerRow; r < mapRows; r++)
                {
                    map_[centerRow][centerCol] = trail;
                    centerRow += 1;
                    if (map_[centerRow][centerCol] == 'H')
                    {
                        cout << endl;
                        cout << "Health pack is detected" << endl;
                        cout << "Alien finds a health pack." << endl;
                        cout << "Alien's life is increased by 20." << endl;
                        alienLife_ += 20;
                    }
                    else if (map_[centerRow][centerCol] == 'P')
                    {
                        map_[centerRow][centerCol] == 'P';
                        cout << endl;
                        cout << "A Pod is detected" << endl;
                        cout << "Alien finds a Pod" << endl;
                        // cout << zombie mana terdekat kena attack

                        zombieLife_ -= 10;
                    }
                    else if (map_[centerRow][centerCol] == 'R')
                    {
                        cout << endl;
                        cout << "Rock is detected" << endl;
                        cout << "Alien finds a rock" << endl;
                        system("pause");

                        // generate a ranodom number between 0 and 1
                        int random = rand() % 2;
                        if (random == 0)
                        {
                            map_[centerRow][centerCol] == 'P';
                            cout << endl;
                            cout << "A Pod appears on the rock" << endl;
                            cout << "Alien finds a pod" << endl;
                            // cout << zombie mana terdekat kena attack

                            zombieLife_ -= 10;
                        }
                        else
                        {
                            (map_[centerRow][centerCol] == 'H');
                            cout << endl;
                            cout << "A Health pack appears on the rock" << endl;
                            cout << "Alien finds a health pack." << endl;
                            cout << "Alien's life is increased by 20." << endl;

                            alienLife_ += 20;
                        }
                    }
                    else if (map_[centerRow][centerCol] == '^' || map_[centerRow][centerCol] == 'v' || map_[centerRow][centerCol] == '<' || map_[centerRow][centerCol] == '>')
                    {
                        cout << endl;
                        cout << "Arrow is detected" << endl;
                        cout << "Alien finds an arrow." << endl;
                        cout << "Alien's attack is increased by 20." << endl;
                        alienAttack_ += 20;
                        map_[centerRow][centerCol]  = trail;
                    }
                    map_[centerRow][centerCol]  = alien;
                    system("pause");
                    system("cls");
                    display();
                }
                break;
            }
            else if (command == "save" || command == "Save")
            {
                save_game(vector<vector<char>> &map_, dimY_, dimX_, alienLife_, alienAttack_, zombies, zombieLife_, zombieAttack_, zombieRange_, string &saveFileName)
            }

            else if (command == "load" || command == "Load")
            {
                load_game(game_state);
            }

            else if (command == "help" || command == "Help")
            {
                howtoplay();
            }

            else if (command == "quit" || command == "Quit")
            {
                break;
            }

            else
            {
                cout << "Alien try to get out of border" << endl;
                run = false;
            }

            // system("cls");
            display();
        }
}

void generateValues(int &life, int &attack)
{
    life = rand() % 100 + 1;  // generates a random number between 1 and 100
    attack = rand() % 10 + 1; // generates a random number between 1 and 10
                              // range = rand() % 10 + 1; // generate a random number between 1 to 10
}

int main()
{
    AVZ game; // create object of AVZ class with default number of rows and columns
    Zombie zombie(10);

    char characters[] = {' ', ' ', ' ', ' ', ' ', 'r', '^', '>', '<', 'v', 'p', 'h', '1', '2'};
    game.initArray();
    for (int i = 0; i < 14; i++)
    {
        game.insertRandomCharacter(characters[i]);
    }
    srand(time(NULL));
    cout << "Assignment (Part 1)" << endl;
    cout << "Let's Get Started!" << endl;
    cout << "Default game setting:" << endl;
    cout << "---------------------" << endl;
    game.displaySettings();
    cout << " " << endl;
    {
        cout << "Do you wish to change the game settings (y/n)?: ";
        char choice;
        cin >> choice;
        int rows_, col_, zombies;
        if (choice == 'y' || choice == 'Y')
        {
            cout << endl;
            cout << "--------------------------" << endl;
            cout << "Enter the number of rows: ";
            cin >> rows_;
            if (rows_ % 2 == 0)
            {
                cout << "Attention! Please insert odd number! " << endl;
                cout << endl;
                cout << "Enter the number of rows: ";
                cin >> rows_;
            }

            cout << "Enter the number of columns: ";
            cin >> col_;
            if (col_ % 2 == 0)
            {
                cout << "Attention! Please insert odd number! " << endl;
                cout << endl;
                cout << "Enter the number of columns: ";
                cin >> col_;
            }

            cout << "Enter number of zombies:";
            cin >> zombies;
            if (zombies > 9)
            {
                cout << "Too many zombies! max number of zombies is 9 " << endl;
                cout << "Enter number of zombies:";
                cin >> zombies;
                return zombies; 
            }

            cout << "Settings Updated. " << endl;
            cout << "Press any key to continue... " << endl;
            getch();
            game.setRows(rows_);
            game.setCol(col_);
            game = AVZ(rows_, col_, zombies);
            game.initArray();
            game.setZombie(zombies);

            for (int i = 0; i < 14; i++)
            {
                game.insertRandomCharacter(characters[i]);
            }
            game.displayArray();
        }
        else
        {
            cout << "Press any key to continue..." << endl;
            getch();
            game.initArray();
            for (int i = 0; i < 14; i++)
            {
                game.insertRandomCharacter(characters[i]);
            }
            game.displayArray();
        }
    
    for (int i = 0; i < 1; i++){
        game.fightZombies(zombies);
    }
    }
    
    
   
   

    while (true)
    {
        cout << "Please Enter Command: ";
        string command;
        cin >> command;
        char choice;
        char save_, load_, direction_, arrow_, help_, quit_;
        int rows_, col_, zombies;
        int currentX_, currentY_;
        if (command == "save" || command == "Save")
        {
            ofstream saveFile;
            saveFile.open("savedGame.txt");
            // write the current game state to the file
            saveFile.close();
            cout << "Game saved successfully." << endl;
        }

        if (command == "load" || command == "Load")
        {
            cout << " Do you want to save the current game? (y/n): ";
            string fileName;
            if (choice == 'n' or 'N')
            {
                cout << "Enter the file name to load: ";
                cin >> fileName;
                cout << "Game Loaded" << endl;
            }
        }
        if (command == "help" || command == "Help")
        {
            cout << "help" << endl;
            cout << "Commands" << endl;
            cout << "1.  direction:(state any of the below) " << endl;
            cout << "    up      - Move up." << endl;
            cout << "    down    - Move down." << endl;
            cout << "    left    - Move left." << endl;
            cout << "    right   - Move right." << endl;
            cout << "2.  arrow   - Change the direction of an arrow." << endl;
            cout << "3.  help    - Display these user commands." << endl;
            cout << "4.  save    - Save the game." << endl;
            cout << "5.  load    - Load a game." << endl;
            cout << "6.  quit    - Quit the game. " << endl;
        }
        if (command == "arrow" || command == "Arrow")
        {
            // cin << arrow_
        }
        if (command == "direction" || command == "Direction")
        {
            game.moveCharacter(currentX_, currentY_);
        }
        if (command == "quit" || command == "Quit")
        {
            cout << "Are you sure you want to quit the game? (y/n):";
            char choice;
            cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                cout << "Thank you for playing. See you again!" << endl;
            }
            else
            {
                cout << "Please Enter Command: ";
                string command;
                cin >> command;
            }
            break; // exit or terminate program
        }
    }

    return 0;
}

void generateValues(int &life, int &attack)
{
    life = rand() % 100 + 1;  // generates a random number between 1 and 100
    attack = rand() % 10 + 1; // generates a random number between 1 and 10
                              // range = rand() % 10 + 1; // generate a random number between 1 to 10
}

int main()
{
    AVZ game; // create object of AVZ class with default number of rows and columns
    Zombie zombie(10);

    char characters[] = {' ', ' ', ' ', ' ', ' ', 'r', '^', '>', '<', 'v', 'p', 'h', '1', '2'};
    game.initArray();
    for (int i = 0; i < 14; i++)
    {
        game.insertRandomCharacter(characters[i]);
    }
    srand(time(NULL));
    cout << "Assignment (Part 1)" << endl;
    cout << "Let's Get Started!" << endl;
    cout << "Default game setting:" << endl;
    cout << "---------------------" << endl;
    game.displaySettings();
    cout << " " << endl;
    {
        cout << "Do you wish to change the game settings (y/n)?: ";
        char choice;
        cin >> choice;
        int rows_, col_, zombies;
        if (choice == 'y' || choice == 'Y')
        {
            cout << endl;
            cout << "--------------------------" << endl;
            cout << "Enter the number of rows: ";
            cin >> rows_;
            if (rows_ % 2 == 0)
            {
                cout << "Attention! Please insert odd number! " << endl;
                cout << endl;
                cout << "Enter the number of rows: ";
                cin >> rows_;
            }

            cout << "Enter the number of columns: ";
            cin >> col_;
            if (col_ % 2 == 0)
            {
                cout << "Attention! Please insert odd number! " << endl;
                cout << endl;
                cout << "Enter the number of columns: ";
                cin >> col_;
            }

            cout << "Enter number of zombies:";
            cin >> zombies;
            if (zombies > 9)
            {
                cout << "Too many zombies! max number of zombies is 9 " << endl;
                cout << "Enter number of zombies:";
                cin >> zombies;
                return zombies; 
            }

            cout << "Settings Updated. " << endl;
            cout << "Press any key to continue... " << endl;
            getch();
            game.setRows(rows_);
            game.setCol(col_);
            game = AVZ(rows_, col_, zombies);
            game.initArray();
            game.setZombie(zombies);

            for (int i = 0; i < 14; i++)
            {
                game.insertRandomCharacter(characters[i]);
            }
            game.displayArray();
        }
        else
        {
            cout << "Press any key to continue..." << endl;
            getch();
            game.initArray();
            for (int i = 0; i < 14; i++)
            {
                game.insertRandomCharacter(characters[i]);
            }
            game.displayArray();
        }
    
    for (int i = 0; i < 1; i++){
        game.fightZombies(zombies);
    }
    }
    
    while (true)
    {
        cout << "Please Enter Command: ";
        string command;
        cin >> command;
        char choice;
        char save_, load_, direction_, arrow_, help_, quit_;
        int rows_, col_, zombies;
        int currentX_, currentY_;
        if (command == "save" || command == "Save")
        {
            ofstream saveFile;
            saveFile.open("savedGame.txt");
            // write the current game state to the file
            saveFile.close();
            cout << "Game saved successfully." << endl;
        }

        if (command == "load" || command == "Load")
        {
            cout << " Do you want to save the current game? (y/n): ";
            string fileName;
            if (choice == 'n' or 'N')
            {
                cout << "Enter the file name to load: ";
                cin >> fileName;
                cout << "Game Loaded" << endl;
            }
        }
        if (command == "help" || command == "Help")
        {
            cout << "help" << endl;
            cout << "Commands" << endl;
            cout << "1.  direction:(state any of the below) " << endl;
            cout << "    up      - Move up." << endl;
            cout << "    down    - Move down." << endl;
            cout << "    left    - Move left." << endl;
            cout << "    right   - Move right." << endl;
            cout << "2.  arrow   - Change the direction of an arrow." << endl;
            cout << "3.  help    - Display these user commands." << endl;
            cout << "4.  save    - Save the game." << endl;
            cout << "5.  load    - Load a game." << endl;
            cout << "6.  quit    - Quit the game. " << endl;
        }
        if (command == "arrow" || command == "Arrow")
        {
            // cin << arrow_
        }
        if (command == "direction" || command == "Direction")
        {
            game.moveCharacter(currentX_, currentY_);
        }
        if (command == "quit" || command == "Quit")
        {
            cout << "Are you sure you want to quit the game? (y/n):";
            char choice;
            cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                cout << "Thank you for playing. See you again!" << endl;
            }
            else
            {
                cout << "Please Enter Command: ";
                string command;
                cin >> command;
            }
            break; // exit or terminate program
        }
    }

    return 0;
}