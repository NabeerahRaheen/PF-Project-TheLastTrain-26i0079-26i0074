#include "util.h"
#include<iostream>
using namespace std;

// Primitive helper utilities, clamping, and screen control
int clampInt(int val, int minVal, int maxVal) {
    if (val < minVal) return minVal;
    if (val > maxVal) return maxVal;
    return val;
}
//emit spaces form end and start
void trimWhitespace(char* str){
   if(*str=='\0'){
    return;
   }
   char* end=str;
   char*start=str;
   char*size=str;
   while(*size!=0){
    size++;
   }
   while(*start==' '){
    start++;
   }
   for(end=size-1;end>=start && *end==' ';end--){

   }
   char* read=start;
   while(read<=end){
    *str=*read;
    read++;
    str++;

   }
   *str='\0';
}
// whether strings are matched or not
bool stringEquals(const char*a,const char*b){
    if(a==nullptr || b==nullptr){
        return false;
    }
    while(*a!='\0' && *b!='\0'){
        if(*a!=*b){
            return false;
        }
        a++;
        b++;
    }
    return (*a=='\0' && *b=='\0');

}
// only prints the header
void printHeader(const char* title){
    if(title==nullptr){
        return;
    }
    cout<<"<=========================================>"<<endl;
    while(*title!='\0'){
        cout<<*title;
        title++;
    }
    cout<<endl;
    cout<<"<=========================================>"<<endl;
    
}
// clear the screen
void clearScreen(){
    for(int i=0;i<35;i++){
        cout<<endl;
    }
}