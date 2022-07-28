#include <iostream>
using namespace std;

class Hanoi
{
public:
    int* tower1;
    int* tower2;
    int* tower3;
    int* towerArray[3];
    unsigned int tower1StackSize;
    unsigned int tower2StackSize;
    unsigned int tower3StackSize;
    unsigned int towerStackSizes[3];
    unsigned int towerSize;
    Hanoi(unsigned int _towerSize = 3) :towerSize(_towerSize), towerStackSizes{ _towerSize , 0, 0 }
    {
        tower1 = new int[_towerSize];
        tower2 = new int[_towerSize];
        tower3 = new int[_towerSize];
        towerArray[0] = tower1;
        towerArray[1] = tower2;
        towerArray[2] = tower3;
        for (int i = 0; i < _towerSize; i++)
        {
            tower1[i] = _towerSize - i;
        }
    }
    void MoveTopPiece(unsigned int startTower, unsigned int endTower)
    {
        if (startTower <= 0 || startTower > 3 || endTower <= 0 || endTower > 3 || startTower == endTower)
        {
            cout << "Error: Invalid Entries for this move" << endl;
            return;
        }
        //Value of tower need to equal array values in towerArray;
        startTower--;
        endTower--;
        //A value holder for the top value of the tower being pulled from
        unsigned int startTopValue;
        //Pointers to the tower arrays in use
        int* startTowerP = towerArray[startTower];
        int* endTowerP = towerArray[endTower];
        unsigned int startTowerSize = towerStackSizes[startTower];;
        unsigned int endTowerSize = towerStackSizes[endTower];
        //Check if pulling from an empty tower, else set the top value
        if (startTowerSize == 0)
        {
            cout << "Error: Pulling a tile from an Empty Tower" << endl;
            return;
        }
        startTopValue = startTowerP[startTowerSize - 1];
        //If the end result has a higher tile, give error
        if (endTowerSize != 0 &&
            startTopValue > endTowerP[endTowerSize - 1])
        {
            cout << "Error: The moving tile is bigger than the tile it will be placed on" << endl;
            return;
        }
        cout << "Moving tile " << startTopValue << " from tower " << startTower + 1 << " to tower " << endTower + 1 << endl;
        //Place the tile on the highest, currently unmarked array slot representing the next highest point of the tower
        endTowerP[endTowerSize] = startTopValue;
        towerStackSizes[endTower] += 1; //Highest tile is now the new tile, as the highest tile is read as (endTowerSize-1)
        towerStackSizes[startTower] -= 1; //Decrement the start tower. Data does not need to be cleared as it won't be considered.

    }
    void PrintTowers()
    {
        cout << "Tower1: ";
        for (unsigned int i = 0; i < towerStackSizes[0]; i++)
        {
            cout << tower1[i] << " ";
        }
        cout << endl << "Tower2: ";
        for (unsigned int i = 0; i < towerStackSizes[1]; i++)
        {
            cout << tower2[i] << " ";
        }
        cout << endl << "Tower3: ";
        for (unsigned int i = 0; i < towerStackSizes[2]; i++)
        {
            cout << tower3[i] << " ";
        }
        cout << endl;
    }
};

void SolveTower(Hanoi& tower, int n, int stack1 = 1, int stack2 = 3, int stack3 = 2)
{
    if (n == 0)
        return;
    SolveTower(tower, n - 1, stack1, stack3, stack2);
    tower.MoveTopPiece(stack1, stack2);
    tower.PrintTowers();
    SolveTower(tower, n - 1, stack3, stack2, stack1);
}

int main()
{
    int towerSize;
    cout << "Give me the size of your Hanoi Tower: ";
    cin >> towerSize;
    Hanoi tower(towerSize);
    tower.PrintTowers();
    SolveTower(tower, tower.towerSize);
}