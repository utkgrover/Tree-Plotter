#ifndef TREE_H
#define TREE_H

// node of tree
typedef struct node {
	int val;
	struct node *LLINK, *RLINK;
	int XCOORD, YCOORD;
	int OFFSET;
	bool THREAD;
} node;


typedef struct extreme{
	struct node *ADDR;
	int OFF;
	int LEV;
} extreme;

class Tree{
    public:
    static void initTree(int*, char**);
	static void inorder(node*);
	static void setup(node*, int, extreme*, extreme*);
	static void convert(node*, int);
	void drawTree(node*, Circle, Line);
};

#endif
