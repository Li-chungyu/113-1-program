//80分
#include <iostream>
#include <cstring>

#define SIZE 100

using namespace std;

class Queue
{
public:
    Queue()
    {
        top = 0;
        bot = -1;
    }
    int enqueue(int data)
    {
        if(bot >= SIZE-1) return -1;
        this->data[++bot] = data;
        return 1;
    }
    int *dequeue()
    {
        if(top > bot) return NULL;
        return &data[top++];
    }
private:
    int data[SIZE];
    int top, bot;
};

int main()
{
    int data, *temp;
    char command[50];
    Queue *queue = new Queue();
    while(1)
    {
        cin>>command;
        if(strcmp(command, "exit") == 0)
        {
            break;
        }
        else if(strcmp(command, "enqueue") == 0)
        {
            cout<<"Please input a integer data:";
            cin>>data;
            if(queue->enqueue(data) == 1)
            {
                cout<<"Successfully enqueue data "<<data<<" into queue."<<endl;
            }
            else
            {
                cout<<"Failed to enqueue data into queue."<<endl;
            }
        }
        else if(strcmp(command, "dequeue") == 0) 
        {
            temp = queue->dequeue();
            if(temp == NULL)
            {
                cout<<"Failed to dequeue a data from queue.\n";
            }
            else
            {
                cout<<"Dequeue data "<<*temp<<" from queue."<<endl;
            }
        }
    }
}