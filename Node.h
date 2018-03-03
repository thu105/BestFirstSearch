#ifndef _NODE_H_
#define _NODE_H_

class Node{
public:
	Node(int a, int b,int c);
	bool operator==(const Node& n);
	bool operator<(const Node& n);
	int x, y, type;
	int parentX, parentY;
	double dist, cost;
};

#endif
