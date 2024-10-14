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
            while(ptr->getNext() != lastptr){
                if(ptr->getData() > ptr->getNext()->getData()){
                    NSwap(ptr,ptr->getNext());
                    swap = true;
                }else{
                    ptr = ptr->getNext();
                }
            }
            lastptr = ptr;
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
            if(start != minNode){
				NSwap(start,minNode);
                start = minNode->getNext();
            }else{
                start = start->getNext();
            }
        }
	}
	
	void insertionSort(){
		Node *cur = list->getNext();

		if(list == nullptr || list->getNext() == nullptr) return;

		while(cur != nullptr){
			Node *Ins = cur;
			cur = cur->getNext();	
			while(Ins->getPre() != nullptr && Ins->getData() < Ins->getPre()->getData()){
				if(Ins->getPre()->getPre() == nullptr){
					NSwap(Ins->getPre(),Ins);
					list = Ins;
				}else{
					NSwap(Ins->getPre(),Ins);
				}
			}
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
    
	void NSwap(Node *n1,Node *n2){
		if(n1->getNext()==n2){//相鄰互換
			if(n1->getPre()!=NULL)
				n1->getPre()->setNext(n2);
			else{
				list=n2;
			}
		
			if(n2->getNext()!=NULL)
				n2->getNext()->setPre(n1);

			Node *tempPre=n1->getPre();
			n1->setPre(n2);
			n1->setNext(n2->getNext());
			n2->setPre(tempPre);
			n2->setNext(n1);
		}
		else{//非相鄰互換
			Node temp=*n1;
			if(n1->getPre()!=NULL){
				n1->getPre()->setNext(n2);
			}
			else{
				list = n2;
			}
			if(n2->getNext()!=NULL){
				n2->getNext()->setPre(n1);
			}
			n1->getNext()->setPre(n2);
			n2->getPre()->setNext(n1);
			
			n1->setPre(n2->getPre());
			n1->setNext(n2->getNext());
			n2->setPre(temp.getPre());
			n2->setNext(temp.getNext());	
		}		
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
