#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cstring>

#define SIZE 10

using namespace std;

class Node
{
public:
	Node() : Node(0, 0){}
	Node(int r, int c)
	{
		row = r;
		col = c;
	}
	int getRow() { return row; }
	int getCol() { return col; }
	void setRow(int r)
	{
		if(r >= 0 && r < SIZE)
			row = r;
	}
	void setCol(int c)
	{
		if(c >= 0 && c < SIZE)
			col = c;
	}
private:
	int col, row;
};

class List
{
public:
	List()
	{
		top = 0;
	}
	/*
	function addElement
	Insert an element from list
	*/
	void addElement(int r, int c){
        data[top] = Node(r,c);
        top++;
	}
	/*
	function removeElement
	remove an element from list and return a pointer point to the element.
	If list is empty, return NULL.
	*/
	Node *removeElement(){
        if(top>0){
            top--;
            return &data[top];
        }
        return nullptr;
	}
	void printList()
	{
		int j;
		for(j = top-1;j >=0 ;j --){
			cout<<"("<<data[j].getRow()<<", "<<data[j].getCol()<<")"<<endl;
		}
	}
private:
	Node data[SIZE * SIZE];
	int top;
};

class Maze
{
public:
	Maze()
	{
		initMaze(SIZE);
	}
	
	void initMaze(int s){
        //動態陣列分配
        maze = new int *[s];
        for(int i=0;i<s;i++){
            maze[i] = new int[s];
        }
        //初始化迷宮為0
        for(int i=0;i<s;i++){
            memset(maze[i],0,s*sizeof(int));
        }
        //隨機生成20%牆壁
        float wall = 0.2;
        int num = s*s*wall;
        int choose[num];//存放選取結果
        int lot[s*s-2];//存放可選編號
        int MaxIndex = s*s-3;//最大可選編號
        //去頭尾初始化lot編號
        for(int i=0;i<s*s-2;i++){
            lot[i] = i+1;
        }
        srand(time(0));
        //隨機選取20%牆壁
        for(int i=0;i<num;i++){
            int ranIndex = rand() % (MaxIndex+1);
            choose[i] = lot[ranIndex];
            lot[ranIndex] = lot[MaxIndex];
            MaxIndex--;
        }
        //放入牆壁
        for(int i=0;i<num;i++){
            int r = choose[i] / s;
            int c = choose[i] % s;
            maze[r][c] = 1;
        }
	}
	
	bool findPath(int r, int c, bool visited[SIZE][SIZE], List *path) {
        // Base Case: If we reach the end point, add it to the path and return true
        if (r == SIZE - 1 && c == SIZE - 1) {
            path->addElement(r, c);
            return true;
        }

        // Mark this cell as visited
        visited[r][c] = true;

        // Define the 4 possible directions (right, down, left, up)
        int dr[] = {0, 1, 0, -1};
        int dc[] = {1, 0, -1, 0};

        // Explore the 4 possible directions
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i]; // New row
            int nc = c + dc[i]; // New column

            // Check if the new position is within bounds, not visited, and is open space
            if (nr >= 0 && nr < SIZE && nc >= 0 && nc < SIZE && !visited[nr][nc] && maze[nr][nc] == 0) {
                // Recursive call to move to the next position
                if (findPath(nr, nc, visited, path)) {
                    // If a path is found, add the current cell to the path and return true
                    path->addElement(r, c);
                    return true;
                }
            }
        }

        // If no path is found in any direction, backtrack and return false
        return false;
    }

    List *getPath() {
        List *path = new List();
        bool visited[SIZE][SIZE] = {false};
        // Start the recursive DFS search from the start point (0, 0)
        if (findPath(0, 0, visited, path)) {
            return path; // If a path is found, return the list containing the path
        } else {
            return path; // If no path is found, return an empty list
        }
    }
	void printMaze()
	{
		int j, k;
		for(j = 0;j < SIZE;j ++)
		{
			for(k = 0;k < SIZE;k ++)
			{
				if(maze[j][k] == 0)
					cout<<" ";
				else if(maze[j][k] == 1)
					cout<<"*";
			}
			cout<<"\n";
		}
	}
private:
	int **maze;
};

int main()
{
	Maze *maze = new Maze();
	maze->printMaze();
	maze->getPath()->printList();
}