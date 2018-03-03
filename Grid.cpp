#include "Grid.h"

using namespace std;
Grid::Grid(string name){
  size = 0;
  mode = 0;
  stepCost = 1;
  totalC = 0;
  totalF = 0;
  setGrid(name);
}
Grid::~Grid(){
  start=NULL;
  goal=NULL;
  for(int x=0; x<size; ++x){
    for(int y=0; y<size; ++y){
      delete grid[x][y];
    }
  }
}
Node* Grid::operator()(int x, int y){
  return grid[x][y];
}
void Grid::setGrid(string name){
  // cout<<"Reading "+name+"..."<<endl;
  ifstream finput(name.c_str());
  if (finput.fail()){//if the reading fails, will output an error message and quit
    cerr<<"Error: Invalid Filename"<<endl;
    exit(1);
  }
  char c;
  stringstream s;
  while((c=finput.get())!='\n')
    s<<c;
  s>>size;

  // cout<<"Parsing the grid..."<<endl;
  for(int x= 0; x<size; ++x){
    for(int y= 0; y<size; ++y){
      c = finput.get();
      if(c=='.'){
        grid[x][y]=new Node(x,y,0);
      }
      else if(c=='+'){
        grid[x][y]=new Node(x,y,1);
      }
      else if(c=='g'){
        goal=new Node(x,y,0);
        grid[x][y]=goal;
      }
      else if(c=='i'){
        start=new Node(x,y,0);
        grid[x][y]=start;
      }
    }
    finput.get();//eliminte the null at the end
    finput.get();//eliminate the new line char
  }
  finput.close();
}
void Grid::printGrid(){
  int t;
  for (int x=0; x<size; ++x){
    for (int y=0; y<size; ++y){
      t=grid[x][y]->type;
      if(goal==grid[x][y]){
        cout<<"g";
      }
      else if(start==grid[x][y]){
        cout<<"i";
      }
      else if(t==0){
        cout<<".";
      }
      else if(t==1){
        cout<<"+";
      }
      else if(t==2){
        cout<<"o";
      }
    }
    cout<<endl;
  }
  cout<<endl;
}
bool Grid::search(int m){
  mode=m;
  if(mode==0 || mode==1){
    stepCost=1;
  }
  else{
    stepCost=0;
  }
  // cout<<"Adding "<<start->x<<", "<<start->y<<" to the fringe"<<endl;
  fringe.push_back(*start);
  totalF++;
  while(!fringe.empty()){
    list<Node>::iterator it = min_element(fringe.begin(),fringe.end());
    fringe.erase(it);
    totalC++;
    if (*it == *goal){
      tracePath();
      return true;
    }
    addNeighbors(*it);
  }

  return false;
}
bool Grid::isValid(int x, int y){
  return (x>=0 && x<size && y>=0 && y<size && grid[x][y]->type!=1);
}
void Grid::addNeighbors(Node n){
  Node* neighbor=NULL;
  if(isValid(n.x+1,n.y)){
    neighbor=grid[n.x+1][n.y];
    // cout<<"Cost: "<<neighbor->cost<<" | Dist: "<<neighbor->dist<<" | New cost: "<<n.cost+stepCost<<" | New dist: "<<getDist(n.x+1,n.y)<<endl;
    if(neighbor->cost+neighbor->dist>n.cost+stepCost+getDist(n.x+1,n.y)){
      neighbor->parentX=n.x;
      neighbor->parentY=n.y;
      neighbor->cost=n.cost+stepCost;
      neighbor->dist=getDist(n.x+1,n.y);
      // cout<<"Adding "<<neighbor->x<<", "<<neighbor->y<<" to the fringe"<<endl;
      totalF++;
      fringe.push_front(*neighbor);
    }
  }
  if(isValid(n.x-1,n.y)){
    neighbor=grid[n.x-1][n.y];
    // cout<<"Cost: "<<neighbor->cost<<" | Dist: "<<neighbor->dist<<" | New cost: "<<n.cost+stepCost<<" | New dist: "<<getDist(n.x-1,n.y)<<endl;
    if(neighbor->cost+neighbor->dist>n.cost+stepCost+getDist(n.x-1,n.y)){
    neighbor->parentX=n.x;
    neighbor->parentY=n.y;
    neighbor->cost=n.cost+stepCost;
    neighbor->dist=getDist(n.x-1,n.y);
    // cout<<"Adding "<<neighbor->x<<", "<<neighbor->y<<" to the fringe"<<endl;
    totalF++;
    fringe.push_front(*neighbor);
  }
  }
  if(isValid(n.x,n.y+1)){
    neighbor=grid[n.x][n.y+1];
    // cout<<"Cost: "<<neighbor->cost<<" | Dist: "<<neighbor->dist<<" | New cost: "<<n.cost+stepCost<<" | New dist: "<<getDist(n.x,n.y+1)<<endl;
    if(neighbor->cost+neighbor->dist>n.cost+stepCost+getDist(n.x,n.y+1)){
    neighbor->parentX=n.x;
    neighbor->parentY=n.y;
    neighbor->cost=n.cost+stepCost;
    neighbor->dist=getDist(n.x,n.y+1);
    // cout<<"Adding "<<neighbor->x<<", "<<neighbor->y<<" to the fringe"<<endl;
    totalF++;
    fringe.push_front(*neighbor);
  }
  }
  if(isValid(n.x,n.y-1)){
    neighbor=grid[n.x][n.y-1];
    // cout<<"Cost: "<<neighbor->cost<<" | Dist: "<<neighbor->dist<<" | New cost: "<<n.cost+stepCost<<" | New dist: "<<getDist(n.x,n.y-1)<<endl;
    if(neighbor->cost+neighbor->dist>n.cost+stepCost+getDist(n.x,n.y-1)){
    neighbor->parentX=n.x;
    neighbor->parentY=n.y;
    neighbor->cost=n.cost+stepCost;
    neighbor->dist=getDist(n.x,n.y-1);
    // cout<<"Adding "<<neighbor->x<<", "<<neighbor->y<<" to the fringe"<<endl;
    totalF++;
    fringe.push_front(*neighbor);
  }
  }
  neighbor=NULL;
}
double Grid::getDist(int a, int b){
  double dist;
  double xDif = abs(goal->x - a);
  double yDif = abs(goal->y - b);
  if (mode==0 || mode==2){

    dist = sqrt(yDif*yDif+xDif*xDif);
  }
  else{
    dist = yDif+ xDif;
  }
  return dist;
}
void Grid::tracePath(){
  Node* n = goal;
  int step=1;
  // cout<<n->x<<", "<<n->y<<" -> "<<n->parentX<<", "<<n->parentY<<endl;
  while(n->parentX!=start->x || n->parentY!=start->y){
    step++;
    n = grid[n->parentX][n->parentY];
    // cout<<n->x<<", "<<n->y<<" -> "<<n->parentX<<", "<<n->parentY<<endl;
    n->type=2;
  }
  if(mode==0){
    cout<<"Euclidean + Step Cost"<<endl;
  }
  else if(mode==1){
    cout<<"Manhattan + Step Cost"<<endl;
  }
  else if(mode==2){
    cout<<"Euclidean Only"<<endl;
  }
  else{
    cout<<"Manhattan Only"<<endl;
  }
  cout<<"Total steps: "<<step<<endl;
  cout<<"Times added to the fringe: "<<totalF<<endl;
  cout<<"Times taken out of the fringe: "<<totalC<<endl<<endl;

  n=NULL;
}
