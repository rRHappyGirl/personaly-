#include <stdio.h>
#include <assert.h>

#define ROW 3
#define COL 3


int Sreach_value(int a[ROW][COL],int value){
    assert(a);
    int row = 0;
    int col = COL - 1;
    if(a != NULL && ROW > 0 && COL > 0){
        while(row < ROW && col >= 0){
            if(a[row][col] == value){
                return 1;
            }else if(a[row][col] > value){
                --col;
            }else if(a[row][col] < value){
                ++row;
            }
        }
    }
    return 0;
}
int main(){
    int a[][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    int ret = Sreach_value(a,8);
    if(ret == 1){
        printf("找到了\n");
    }else{
        printf("没找到\n");
    }
    return 0;
}
