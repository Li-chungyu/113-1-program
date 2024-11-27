#include <iostream>
#include <vector>
#include <stdexcept>
#include <cmath>

template<class T>
class MinMaxHeap {
public:
    MinMaxHeap() {}

    void insert(T value) {
        heap.push_back(value);
        bubbleUp(heap.size() - 1);
    }

    T getMin() const {
        if (heap.empty()) throw std::runtime_error("Heap is empty");
        return heap[0];
    }

    T getMax() const {
        if (heap.empty()) throw std::runtime_error("Heap is empty");
        if (heap.size() == 1) return heap[0];
        if (heap.size() == 2) return heap[1];
        return std::max(heap[1], heap[2]);
    }

    void deleteMin() {
        if (heap.empty()) throw std::runtime_error("Heap is empty");
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) trickleDown(0);
    }

    void deleteMax() {
        if (heap.empty()) throw std::runtime_error("Heap is empty");
        if (heap.size() == 1) {
            heap.pop_back();
            return;
        }
        int maxIndex = (heap.size() == 2 || heap[1] > heap[2]) ? 1 : 2;
        heap[maxIndex] = heap.back();
        heap.pop_back();
        trickleDown(maxIndex);
    }

private:
    std::vector<T> heap;

    bool isMinLevel(int index) const {
        return static_cast<int>(std::log2(index + 1)) % 2 == 0;
    }

    void bubbleUp(int index) {
        if (index == 0) return;
        int parent = (index - 1) / 2;
        if (isMinLevel(index)) {
            if (heap[index] > heap[parent]) {
                std::swap(heap[index], heap[parent]);
                bubbleUpMax(parent);
            } else {
                bubbleUpMin(index);
            }
        } else {
            if (heap[index] < heap[parent]) {
                std::swap(heap[index], heap[parent]);
                bubbleUpMin(parent);
            } else {
                bubbleUpMax(index);
            }
        }
    }

    void bubbleUpMin(int index) {
        int grandparent = (index - 3) / 4;
        if (index >= 3 && heap[index] < heap[grandparent]) {
            std::swap(heap[index], heap[grandparent]);
            bubbleUpMin(grandparent);
        }
    }

    void bubbleUpMax(int index) {
        int grandparent = (index - 3) / 4;
        if (index >= 3 && heap[index] > heap[grandparent]) {
            std::swap(heap[index], heap[grandparent]);
            bubbleUpMax(grandparent);
        }
    }

    void trickleDown(int index) {
        if (isMinLevel(index)) {
            trickleDownMin(index);
        } else {
            trickleDownMax(index);
        }
    }

    void trickleDownMin(int index) {
        int smallest = index;
        int left = 2 * index + 1, right = 2 * index + 2;

        if (left < heap.size() && heap[left] < heap[smallest]) smallest = left;
        if (right < heap.size() && heap[right] < heap[smallest]) smallest = right;

        for (int i = 4 * index + 3; i <= 4 * index + 6 && i < heap.size(); ++i) {
            if (heap[i] < heap[smallest]) smallest = i;
        }

        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            if (smallest >= 4 * index + 3) {
                int parent = (smallest - 1) / 2;
                if (heap[smallest] > heap[parent]) std::swap(heap[smallest], heap[parent]);
                trickleDownMin(smallest);
            }
        }
    }

    void trickleDownMax(int index) {
        int largest = index;
        int left = 2 * index + 1, right = 2 * index + 2;

        if (left < heap.size() && heap[left] > heap[largest]) largest = left;
        if (right < heap.size() && heap[right] > heap[largest]) largest = right;

        for (int i = 4 * index + 3; i <= 4 * index + 6 && i < heap.size(); ++i) {
            if (heap[i] > heap[largest]) largest = i;
        }

        if (largest != index) {
            std::swap(heap[index], heap[largest]);
            if (largest >= 4 * index + 3) {
                int parent = (largest - 1) / 2;
                if (heap[largest] < heap[parent]) std::swap(heap[largest], heap[parent]);
                trickleDownMax(largest);
            }
        }
    }
};

int main() {
    MinMaxHeap<int> mmHeap;
    int j;
    srand(time(NULL));
    for(j = 0; j < 10; j++)
        mmHeap.insert(rand() % 100);

    std::cout << "Min values: ";
    while(true) {
        try {
            std::cout << mmHeap.getMin() << " ";
            mmHeap.deleteMin();
        }
        catch(std::exception&) {
            break;
        }
    }
    std::cout << std::endl;

    for(j = 0; j < 10; j++)
        mmHeap.insert(rand() % 100);

    std::cout << "Max values: ";
    while(true) {
        try {
            std::cout << mmHeap.getMax() << " ";
            mmHeap.deleteMax();
        }
        catch(std::exception&) {
            break;
        }
    }
    return 0;
}
