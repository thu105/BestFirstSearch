#include <list>
#include <algorithm>
#include <cmath>
#ifndef _GRID_H_
#define _GRID_H_

using namespace std;
class Grid{
private:
  Node* grid[80][80];
public:
    Grid(string name);
    ~Grid();
    void setGrid(string name);
    void printGrid();
    void addNeighbors(Node n);
    void tracePath();
    bool search(int m);
    bool isValid(int x, int y);
    double getDist(int a, int b);
    Node* operator()(int x, int y);
    int size;
    int mode;
    int stepCost;
    int totalF;
    int totalC;
    Node* start;
    Node* goal;
    list<Node> fringe;
};
#endif
