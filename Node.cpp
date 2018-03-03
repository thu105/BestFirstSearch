#include "Node.h"

Node::Node(int a, int b, int c){
  x=a;
  y=b;
  type=c;
	parentX=-1;
  parentY=-1;
	dist=500.0;
  cost=0.0;
}
bool Node::operator==(const Node& n){
  return (x==n.x && y==n.y);
}
bool Node::operator<(const Node& n){
  return dist + cost < n.dist + n.cost;
}
