#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

#define SIZE 10
#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3

class Grid
{
public:
	Grid() : Grid(0) {}
	Grid(int s)
	{
		state = s;
		dir[UP] = NULL;
		dir[DOWN] = NULL;
		dir[LEFT] = NULL;
		dir[RIGHT] = NULL;
	}
	Grid *getDir(int d) { return dir[d]; }
	int getState() { return state; }
	void setDir(int d, Grid *g) { dir[d] = g; }
	void setState(int s) { state = s;}
private:
	Grid *dir[4];
	int state;
};

struct List
{
public:
	List()
	{
		top = 0;
	}
	
	void addElement(Grid *g){
		data[top++] = g;
	}
	
	Grid *removeElement(){
		if(top > 0){
			return data[--top];
		}
		return nullptr;
	}
	void printPath()
	{
		int j;
		for(j = top-1;j >0;j --)
		{
			if(data[j-1] == data[j]->getDir(UP))
			{
				cout<<"UP\n";
			}
			else if(data[j-1] == data[j]->getDir(DOWN))
			{
				cout<<"DOWN\n";
			}
			else if(data[j-1] == data[j]->getDir(LEFT))
			{
				cout<<"LEFT\n";
			}
			else if(data[j-1] == data[j]->getDir(RIGHT))
			{
				cout<<"RIGHT\n";
			}
		}
	}
private:
	Grid *data[SIZE * SIZE];
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
		// Create the first row of the maze
        Grid* prevRow = nullptr;
        Grid* currRow = nullptr;
        Grid* last = nullptr;
		Grid* prevRowFirst = nullptr;
		
        maze = new Grid();  // Top-left corner (start point)
        last = maze;
        prevRow = last;

        // Create the rest of the first row
        for (int i = 1; i < s; i++) {
            Grid* newGrid = new Grid();
            last->setDir(RIGHT, newGrid);
            newGrid->setDir(LEFT, last);
            last = newGrid;
        }
	    // Link the rest of the row
		for (int i = 1; i < s; i++) {
			currRow = new Grid();
			prevRowFirst = prevRow;  // Save the first cell of the previous row
			prevRow->setDir(DOWN, currRow);
			currRow->setDir(UP, prevRow);
			last = currRow;
			for (int j = 1; j < s; j++) {
				Grid* newGrid = new Grid();
				last->setDir(RIGHT, newGrid);
				newGrid->setDir(LEFT, last);
				last = newGrid;

				prevRow = prevRow->getDir(RIGHT);  // Move `prevRow` to the right cell in the previous row
				prevRow->setDir(DOWN, newGrid);    // Link the new grid to the cell above
				newGrid->setDir(UP, prevRow);
			}

			prevRow = prevRowFirst->getDir(DOWN);  // Move to the next row for the next outer loop iteration
		}
		//generate 20% wall
		srand(time(0));
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
            int row = choose[i] / s;
            int col = choose[i] % s;
            Grid* curr = maze;
            for (int r = 0; r < row; r++) {
                curr = curr->getDir(DOWN);
            }
            for (int c = 0; c < col; c++) {
                curr = curr->getDir(RIGHT);
            }

            // Set the state to wall
            curr->setState(1);
        }
	}
	
	List *getPath(){
		// Create a list to store the path
        List *path = new List();
        // Create a 2D visited array to avoid visiting cells more than once
        bool visited[SIZE][SIZE] = {false};

        // Start DFS from the top-left corner (0,0)
        if (dfs(maze, path, visited))
        {
            return path; // Path found, return it
        }
        else
        {
            delete path; // No path found, delete the empty path
            return nullptr;
        }
	}
	void printMaze()
	{
		Grid *j = maze, *k;
		while(j != NULL)
		{
			k = j;
			while(k != NULL)
			{
				cout<<k->getState();
				k = k->getDir(RIGHT); 
			}
			cout<<endl;
			j = j->getDir(DOWN);
		}
	}
private:
	Grid *maze;
	 // Recursive DFS function to find the path
    bool dfs(Grid *current, List *path, bool visited[SIZE][SIZE], int row = 0, int col = 0)
    {
        // Base case: If we are at the bottom-right corner
        if (row == SIZE - 1 && col == SIZE - 1)
        {
            path->addElement(current); // Add the final cell to the path
            return true;               // Path found
        }

        // Mark the current cell as visited
        visited[row][col] = true;

        // Define directions: right, down, left, up
        int dr[] = {0, 1, 0, -1};
        int dc[] = {1, 0, -1, 0};

        // Try all 4 directions
        for (int i = 0; i < 4; i++)
        {
            int newRow = row + dr[i];
            int newCol = col + dc[i];

            // Check boundaries and if the new cell is unvisited and open (state == 0)
            if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE &&
                !visited[newRow][newCol] && current->getDir(i) != NULL && current->getDir(i)->getState() == 0)
            {
                // Recur with the new position
                if (dfs(current->getDir(i), path, visited, newRow, newCol))
                {
					path->addElement(current);
                    return true; // If the path is found, return true
                }
            }
        }

        return false; // No path found from this direction
    }
};

int main()
{
	Maze *maze = new Maze();
	maze->printMaze();
	maze->getPath()->printPath();
}
