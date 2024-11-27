#include<iostream>
#include<vector>
#include<stdexcept>

using namespace std;

template<class T>
class MaxHeap {
    public:
        MaxHeap() : heapSize(0) {}
        void insert(T value){
            heap.push_back(value);
            heapSize++;
            bubbleUp(heapSize-1);
        }
        T extract(){
            if(heapSize == 0){
                throw out_of_range("Heap is empty.");
            }
            T rootvalue = heap[0];
            swap(heap[0],heap[heapSize-1]);
            heap.pop_back();
            heapSize--;
            bubbleDown(0);
            return rootvalue;
        }
        int count(){
            return heapSize;
        }
    private:
        int heapSize;
        vector<T> heap;
        void bubbleUp(int index){
            while(index > 0){
                int parent = (index - 1) / 2;
                if(heap[index] <= heap[parent]) break;
                swap(heap[index],heap[parent]);
                index = parent;
            }
        }
        void bubbleDown(int index){
            while(2 * index + 1 < heapSize){
                int leftChild = 2 * index + 1;
                int rightChild = leftChild + 1;
                int largerChild = leftChild;
                if(rightChild < heapSize && heap[rightChild] >= heap[leftChild]) break;
                swap(heap[index],heap[largerChild]);
                index = largerChild;
            }
        }

};
