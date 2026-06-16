#include <iostream>
using namespace std;

int LinearSearch(int arr[], int size, int target){
   for (int i = 0; i < size; i++){
      if(arr[i] == target){
      return i;
      }
   }
   return -1;
}

int main (){
   const int size = 10;
   int arr[size] ={10, 20, 30, 40, 50, 55, 32, 34, 35, 65};
   int target = 55;
   int ind = LinearSearch(arr, 10,target);
   cout <<ind; 
}