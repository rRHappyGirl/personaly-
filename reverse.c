#include <stdio.h>
#include <assert.h>
#include <string.h>

void Reverse(char* start,char* end){
    assert(start);
    assert(end);
    while(start <  end){
        char tmp = *start;
        *start = *end;
        *end = tmp;
        start++;
        end--;
    }
}

void ReverseString(char a[]){
    char* start = a;
    char* end = start;
    while(*start != '\0'){
        if(*start == ' '){
            start++;
            end++;
        }else if(*end == ' ' || *end == '\0'){
            Reverse(start,end - 1);
            start = end;
        }else{
            ++end;
        }
    }
    start = a;
    Reverse(start,end - 1);
    printf("%s\n",a);
}
int main(){
    char a[] = "I like Beijing";
    printf("%s\n",a);
    ReverseString(a);
    return 0;
}
