//100分
#include <stdio.h>
#include <stdlib.h>
void allocArray(int ***p, int m, int n){
  //分配行指針陣列空間
  *p = (int **)malloc(m*sizeof(int *));
  //一次分配好連續記憶體
  int *data = (int *)malloc(n*m*sizeof(int));
  //把行指針指向連續記憶體
  for(int i=0;i<m;i++){
    (*p)[i] = data + i*n;
  }
}

int main(){
  int **array, *a;
  int j, k;
  allocArray(&array, 5, 10);
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      array[j][k] = j * 10 + k;
  for(j = 0;j < 5;j ++)
    for(k = 0;k < 10;k ++)
      printf("%p ", &(array[j][k]));

   // 釋放記憶體
    free(array[0]); 
    free(array);    
}