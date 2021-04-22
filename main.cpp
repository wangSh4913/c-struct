#include <iostream>
#include "include/binaruSerchTree.h"
#include <unordered_map>

using namespace std;

void printnum(int val){
    cout << val << "_ ";
}

int main(){
    BinarySerchTree tree;
    int arr[] = {7,4,2,1,3,5,9,8,11,10,12,13,14};
    for(int i = 0; i<10; i++){
        tree.add(arr[i]);
    }
    tree.inorder([](int val)->void{
        cout << val << "_ "; 
    });
    tree.remove(9);
    tree.inorder([](int val)->void{
        cout << val << "_ "; 
    });

}




