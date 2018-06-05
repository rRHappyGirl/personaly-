#include <stdio.h>


void Find(int arr[],int size){
    if(arr == NULL){
        return;
    }
    int bound = 0;
    for(;bound < size;bound++){
        int cur = bound + 1;
        for(;cur < size;cur++){
            if(arr[bound] == arr[cur]){
                printf("%d\n",arr[bound]);
                break;
            }   
        }
        break;
    }
    return;
}
int main(){
    int arr[] = {2,3,1,0,2,5,3};
    int len = sizeof(arr)/sizeof(arr[0]);
    Find(arr,len);
    return 0;
}
