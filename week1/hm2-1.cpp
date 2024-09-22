//80分
#include <iostream>
#include <cstdlib>

using namespace std;

template<class T>
class Memory{
    public:
        static T **allocArray(int m, int n){
            //分配空間給行指針陣列
            T **array = new T *[m];
            //分配空間給每一行
            for(int i=0;i<m;i++){
                array[i] = new T[n];
            }
            return array;
        }
        static void deletearray(T **array,int m){
            //釋放每一行的內容
            for(int i=0;i<m;i++){
                delete[] array[i];
            }
            //釋放行指針陣列內存
            delete[] array;
        }
};

int main(){
  int **array;
  array = Memory<int>::allocArray(5, 10);
  int j, k;
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      array[j][k] = j * 10 + k;
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      cout<<array[j][k]<<" ";

  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      printf("%p ", &(array[j][k]));

  Memory<int>::deletearray(array,5);
}