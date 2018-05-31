#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Adjust(int arr[],int size){
    int* tmp = (int*)malloc(sizeof(int) * size);
    int tmp_index = 0;
    int cur1 = 0;
    int cur2 = 0;
    for(;cur1 < size;cur1++){
        if((arr[cur1]&1) == 1){
            tmp[tmp_index++] = arr[cur1];
        }
    }
    for(cur2 = 0;cur2 < size;cur2++){
        if((arr[cur2]&1) == 0){
            tmp[tmp_index++] = arr[cur2];
        }
    }
    memcpy(arr,tmp,sizeof(int) * size);
    free(tmp);
    return;
}

int main(){
    int arr[] = {2,1,4,5,3,7,6,9,8,10,12};
    int len = sizeof(arr)/sizeof(arr[0]);
    Adjust(arr,len);
    int i = 0;
    for(;i < len;i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}
