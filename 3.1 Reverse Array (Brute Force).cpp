#include <iostream>
using namespace std;

int* ReverseArray(int arr[], int size){
    for (int i = 0; i< size; i++){
        if(i >= size){return arr;}
        int temp;
        temp = arr[i];
        arr[i] = arr[size];
        arr[size] = temp;
        size--;
    }
    return arr;
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
