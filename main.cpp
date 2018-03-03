#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "Node.cpp"
#include "Grid.cpp"
using namespace std;

string getName(){
  string temp;
  cout <<"Please enter the filename: ";
  getline(cin, temp);
  return temp;
}

int main(){
  // Grid g(getName());
  // Grid g("test.txt");
  // g.printGrid();
  // if (g.search(0))
  //   g.printGrid();
  string name= getName();
  for(int m=0; m<4; ++m){
    Grid g(name);
    if(g.search(m))
      g.printGrid();
  }
}
