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
	
	void insertionSort() {
        // 如果鏈表為空或只有一個元素，直接返回
        if (list == nullptr || list->getNext() == nullptr) return;

        // 初始化 sorted 為空鏈表
        Node* sorted = nullptr;

        // 遍歷原始鏈表的每一個節點
        Node* cur = list;
        while (cur != nullptr) {
            // 保存下一個節點，因為我們將當前節點移入 sorted
            Node* next = cur->getNext();
            
            // 將當前節點插入 sorted 鏈表
            sortedInsert(&sorted, cur);

            // 繼續遍歷原始鏈表
            cur = next;
        }

        // 將排序後的鏈表設置為 list
        list = sorted;
    }

    // 輔助函數，用於將一個節點插入 sorted 鏈表
    void sortedInsert(Node** sorted, Node* newNode) {
        // 如果 sorted 為空或 newNode 的數據小於 sorted 第一個節點的數據
        if (*sorted == nullptr || (*sorted)->getData() >= newNode->getData()) {
            newNode->setNext(*sorted);
            if (*sorted != nullptr) {
                (*sorted)->setPre(newNode);
            }
            *sorted = newNode;
        }
        else {
            // 找到適合 newNode 插入的位置
            Node* cur = *sorted;
            while (cur->getNext() != nullptr && cur->getNext()->getData() < newNode->getData()) {
                cur = cur->getNext();
            }

            // 插入 newNode 到 cur 之後
            newNode->setNext(cur->getNext());
            if (cur->getNext() != nullptr) {
                cur->getNext()->setPre(newNode);
            }
            cur->setNext(newNode);
            newNode->setPre(cur);
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
