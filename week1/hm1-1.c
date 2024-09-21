//80分
#include <stdio.h>
#include <stdlib.h>
void allocArray(int ***p, int m, int n){
  //為行指針陣列分配空間
  *p = (int **)malloc(m*sizeof(int *));
  //為每行分配空間
  for(int i=0;i<m;i++){
    (*p)[i] = (int *)malloc(n*sizeof(int));
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
    for (j = 0; j < 5; j++) {
        free(array[j]);
    }
    free(array);
}