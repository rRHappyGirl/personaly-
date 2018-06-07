#include <stdio.h>

void _duplicate(int arr[],int size,int* dup){
    if(arr == NULL || size <= 0){
        return;
    }
    int i = 0;
    for(;i < size;i++){
        if(arr[i] >= size || arr[i] < 0){
            return;
        }
    }
    int bound = 0;
    for(;bound < size;bound++){
        int cur = bound + 1;
        for(;cur < size;cur++){
            if(arr[bound] == arr[cur]){
                *dup = arr[bound];
                return;
            }
        }
    }
    return;
}
int main(){
    int arr[] = {1,2,3,5,2,4,3};
    int len = sizeof(arr)/sizeof(arr[0]);
    int dup;
    _duplicate(arr,len,&dup);
    printf("%d\n",dup);
    return 0;
}
