#include <iostream>
#include <climits>
using namespace std;

int main(){
   int arr[5] = {10, 20, 30, 40, 50};
   int size = 5;

   int smallest = INT_MAX;
   int largest  = INT_MIN;

   for(int i = 0; i < size; i++){
      smallest = min(arr[i] , smallest);
      largest = max(arr[i] , largest);
   }

   cout<<"Largest: " << largest << "\nSmallest: " << smallest << endl;


}