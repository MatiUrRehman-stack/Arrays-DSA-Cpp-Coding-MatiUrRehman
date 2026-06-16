#include <iostream>
using namespace std;

int* ReverseArray(int arr[], int s2, int s1 = 0){
    int temp;
    temp = arr[s1] ;
    arr[s1] = arr[s2];
    arr[s2] = temp;
    if(s1>=s2){
        return arr;
    }
    
    return ReverseArray(arr, s2-1, s1+1);
}

int main(){
    
    int array[] = {10, 20, 30, 40, 50, 60, 25, 35, 70};
    for (int i = 0;i < 9; i++){
        cout<<array[i]<<" ";
    }
    cout << endl;
    
    ReverseArray(array, 9-1);
    for (int i = 0;i < 9; i++){
        cout<<array[i]<<" ";
    }
    cout << endl;
}
