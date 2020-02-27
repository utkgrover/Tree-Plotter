#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include"helper.h"
#include"circle.h"
#include"line.h"
#include<GL/glut.h>
using namespace std;

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;
const int DISTANCE_LEVEL = 100;
const int TOP_MARGIN = 50;
const int MINSEP = 100;
const int RADIUS=20;

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

static node *treeRoot;

void setup(node *T, int LEVEL, extreme *RMOST, extreme *LMOST);
void convert(node *T, int XPOS);

void inorder(node *root){
	if(root==NULL) return;
	inorder(root->LLINK);
	printf("Node: %d X-coord %d Ycoord %d\n", root->val, root->XCOORD, root-> YCOORD);
	inorder(root->RLINK);
}

int cur_val=0;
string s3="ynnyyynynnnyynnyyynynnnyynynnyynnn";
string s2 = "ynynynnyyynnnynynn";
string s1="yyyyynnyynnyynnyynnynnynnynnynnyynnyynnyynnyyyyynnynnynnynnynn";
string s4="ynynynynynnynn";
int string_pos=0;

void func(node* root){

    root->val=cur_val++;
    root->XCOORD=0;
	root->YCOORD=0;
	root->OFFSET=0;
    
    char c=s1[string_pos++];
    
    if(c=='y'){
        root->LLINK=(node*) malloc(sizeof(node));
        func(root->LLINK);
    }else{
        root->LLINK=NULL;
    }
    c=s1[string_pos++];
    if(c=='y'){
        root->RLINK=(node*) malloc(sizeof(node));
        func(root->RLINK);
    }else{
        root->RLINK=NULL;
    }
    
}

node* getSampleTree(){
	node* root =(node*) malloc(sizeof(node));
    func(root);
    return root;
}

void drawTree(node *root){
	Circle::drawCircle(root->XCOORD, root->YCOORD, RADIUS);
	if(root->LLINK!=NULL){
		Line::drawLine(root->XCOORD, root->YCOORD, root->LLINK->XCOORD, root->LLINK->YCOORD, RADIUS+2);
		drawTree(root->LLINK);
	}
	if(root->RLINK!=NULL){
		Line::drawLine(root->XCOORD, root->YCOORD, root->RLINK->XCOORD, root->RLINK->YCOORD, RADIUS+2);
		drawTree(root->RLINK);
	}
}

void draw(){
    drawTree(treeRoot);
	glFlush();
}

int main(int argc, char **argv){
    extreme *a = (extreme*)malloc(sizeof(extreme)); 
    extreme *b = (extreme*)malloc(sizeof(extreme)); 

    treeRoot = getSampleTree();
    setup(treeRoot, 0, a, b);
    convert(treeRoot, WINDOW_WIDTH/2);
	printf("\nInorder traversal of Tree :\n");
    inorder(treeRoot);
	Helper::createWindow(&argc, argv);
	Helper::clearScreen();
    glutDisplayFunc(draw);
    // glutIdleFunc(idle);
    glutMainLoop();
}

void convert(node *T, int XPOS){
	if (T != NULL){
		T->XCOORD = XPOS;
		// if (T->THREAD==true){
		// 	T->THREAD = false;
		// 	T->RLINK = NULL;
		// 	T->LLINK = NULL;
		// }
		convert( T->LLINK, XPOS - T->OFFSET);
		convert( T->RLINK, XPOS + T->OFFSET);
	}
}

void setup(node *T, int LEVEL, extreme *RMOST, extreme *LMOST){
	int CURSEP; // SEPARATION ON CURRENT LEVEL
	int ROOTSEP; //CURRENT SEPARATION AT NODE T
	int LOFFSUM, ROFFSUM; // OFPSET FROM L & R TO T

	node *L,* R; // LEFT AND RIGHT SONS
	extreme *LR, *LL, *RR, *RL; //LR - RIGHTMOST NODE ON LOWEST LEVEL OF LEFT SUBTREE AND SO ON

	LL = (extreme*)malloc(sizeof(extreme));
    LR = (extreme*)malloc(sizeof(extreme));
    RR = (extreme*)malloc(sizeof(extreme));
    RL = (extreme*)malloc(sizeof(extreme));

	if (T == NULL){// AVOID SELECTING AS EXTREME
		LMOST->LEV = -1;
		RMOST->LEV = -1;
	}
	else{
		T->YCOORD =WINDOW_HEIGHT-TOP_MARGIN-LEVEL*DISTANCE_LEVEL;
		L = T->LLINK; //FOLLOWS CONTOUR OF LEFT SUBTREE
		R = T->RLINK; // FOLLOWS CONTOUR OP RIGNT SUBTREE
		setup(L, LEVEL+1, LR, LL); //POSITION SUBTREES RECURSIVELY
		setup(R, LEVEL+1, RR, RL);
		if ((R==NULL) && (L==NULL)){
			RMOST->ADDR = T; // A LEAF IS BOTH THE LEPTMOST
			LMOST->ADDR = T; //AND RIGHTMOST NODE ON THE
			RMOST->LEV = LEVEL; // LOWEST LEVEL OF THE SUBTREE
			LMOST->LEV = LEVEL; // CONSISTING OF ITSELF
			RMOST->OFF = 0;
			LMOST->OFF = 0;
			T->OFFSET = 0;
		}
		else{
			//T NOT A LEAF 
			//SET UP FOR SUBTREE PUSHING. PLACE ROOTS OF SUBTREES MINIMUM DISTANCE APART
			CURSEP  = MINSEP;
			ROOTSEP = MINSEP;
			LOFFSUM = 0;
			ROFFSUM = 0;
			while (L!=NULL && R!=NULL){
				if (CURSEP < MINSEP){
					ROOTSEP = ROOTSEP + (MINSEP - CURSEP);
					CURSEP = MINSEP;
				}
				//ADVANCE L & R
				if (L->RLINK != NULL) {
					LOFFSUM = LOFFSUM + L->OFFSET;
					CURSEP = CURSEP - L->OFFSET;
					L = L->RLINK;
				} 
				else{ 
					LOFFSUM = LOFFSUM - L->OFFSET;
					CURSEP = CURSEP + L->OFFSET;
					L = L->LLINK;
				}
				if (R->LLINK !=NULL){
					ROFFSUM = ROFFSUM - R->OFFSET;
					CURSEP = CURSEP - R->OFFSET;
					R = R->LLINK;
				}
				else{
					ROFFSUM = ROFFSUM + R->OFFSET;
					CURSEP = CURSEP + R->OFFSET;
					R =R->RLINK;
				}
			}
			// SET THE OFFSET IN NODE T, AND INCLUDE IT IN
			// ACCUMULATED OFFSETS FOR L AND R
			T->OFFSET = (ROOTSEP + 1)/2;
			LOFFSUM = LOFFSUM - T->OFFSET;
			ROFFSUM = ROFFSUM + T->OFFSET;
			// UPDATE EXTREME DESCENDANTS INFOREMATIOS
			if (RL->LEV > LL->LEV || T->LLINK == NULL){
				LMOST = RL;
				LMOST->OFF = LMOST->OFF + T->OFFSET;
			}
			else{
				LMOST = LL;
				LMOST->OFF = LMOST->OFF - T->OFFSET;
			}
			if (LR->LEV > RR->LEV || T->RLINK == NULL){
				RMOST = LR;
				RMOST->OFF = RMOST->OFF - T->OFFSET;
			}
			else{
				RMOST = RR;
				RMOST->OFF = RMOST->OFF + T->OFFSET;
			}
			// IF SUBTREES OF T WERE OF UNEVEN HEIGHTS, CHECK
			// TO SEE IF THREADING IS NHECESSARY. AT MOST ONE
			// THREAD NEEDS TO BE INSERTED.
			if (L != NULL && L != T->LLINK){
				RR->ADDR = (node*)malloc(sizeof(node));
				RR->ADDR->THREAD = true;
				RR->ADDR->OFFSET = abs(( RR->OFF + T->OFFSET) - LOFFSUM );
				if (LOFFSUM - T->OFFSET <= RR->OFF) RR->ADDR->LLINK=L;
				else RR->ADDR->RLINK = L;
			}
			else if(R !=NULL && R != T->RLINK) {
				LL->ADDR = (node*)malloc(sizeof(node));
				LL->ADDR->THREAD = true;
				LL->ADDR->OFFSET = abs(( LL->OFF - T->OFFSET ) - ROFFSUM );
				if (ROFFSUM + T->OFFSET >= LL->OFF) LL->ADDR->RLINK = R;
				else LL->ADDR->LLINK = R;
			}
		}
	}
}
