
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