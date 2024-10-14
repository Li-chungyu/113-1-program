#include <iostream>
#include <cstdlib>
#include <ctime>

#define SIZE 100

using namespace std;

class Node
{
public:
	Node()
	{
		next = NULL;
		pre = NULL;
	}
	Node(int n)
	{
		data = n;
		next = NULL;
		pre = NULL;
	}
	int getData() { return data; }
	Node *getNext() { return next; }
	Node *getPre() { return pre; }
	void setData(int d) { data = d; }
	void setNext(Node *n) { next = n; }
	void setPre(Node *p) { pre = p; }
private:
	int data;
	Node *next, *pre; 
};

class List
{
public:
	List() { list = NULL; }
	List(int n) { generate(n); }
	
	void generate(int n)
	{
		int j;
		list = NULL;
		for(j = 0;j < n;j ++)
			generate();
	}
	
	void generate()
	{
		Node *buf = new Node(rand());
		buf->setNext(list);
		if(list != NULL)
			list->setPre(buf);
		list = buf;
	}
	
	void bubbleSort(){
        Node *ptr;
        Node *lastptr = nullptr;
        bool swap;

		if(list == nullptr || list->getNext() == nullptr) return;

        do{
            swap = false;
            ptr = list;
            while(ptr->getNext()!=lastptr){
                if(ptr->getData() > ptr->getNext()->getData()){
                    Vswap(ptr,ptr->getNext());
                    swap = true;
                }
                ptr = ptr->getNext();
            }
            ptr = lastptr;
        }while(swap);
	}
	
	void selectionSort(){
        Node *start = list;
        Node *minNode, *cur;
		
		if(list == nullptr || list->getNext() == nullptr) return;
        
		while(start != nullptr){
            minNode = start;
            cur = start->getNext();
            while(cur != nullptr){
                if(cur->getData() < minNode->getData()){
                    minNode = cur;
                }
                cur = cur->getNext();
            }
            if(minNode != start){
                Vswap(minNode,start);
            }
            start = start->getNext();
        }
	}
	
	void insertionSort(){
		Node *cur = list->getNext();

		if(list == nullptr || list->getNext() == nullptr) return;

		while(cur != nullptr){
			Node *Ins = cur;
			while(Ins->getPre() != nullptr && Ins->getData() < Ins->getPre()->getData()){
				Vswap(Ins,Ins->getPre());
				Ins = Ins->getPre();
			}
			cur = cur->getNext();
		}
	} 
	
	void print()
	{
		Node *cur = list;
		while(cur != NULL)
		{
			cout<<cur->getData()<<" ";
			cur = cur->getNext();
		}
		cout<<endl;
	}

	void Vswap(Node *n1, Node *n2){
		int temp = n1->getData();
        n1->setData(n2->getData());
        n2->setData(temp);
	}

private:
	Node *list;
};

int main()
{
	srand(time(NULL));
	List *l = new List(10);
	l->print();
	l->bubbleSort();
	l->print();
	
	l = new List(10);
	l->print();
	l->insertionSort();
	l->print();
	
	l = new List(10);
	l->print();
	l->selectionSort();
	l->print();
}
