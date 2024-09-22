//100分
#include <iostream>
#include <cstdlib>

using namespace std;

template<class T>
class Memory{
    public:
        static T **allocArray(int m, int n){
            //分配行指針陣列
            T **array = new T *[m];
            //一次分配所有內存
            T *data = new T[n*m];
            //把行指針指向適當位置
            for(int i=0;i<m;i++){
                array[i] = data + n*i;
            }
            return array;
        }
        static void deletearray(T **array,int m){
            //釋放連續內容
            delete[] array[0];
            //釋放行指針鎮行指針陣列
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