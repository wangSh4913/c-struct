#include "include/AVLTree.h"

void AVLTree::add(int val){
    AVLNode *newNode = new AVLNode(val);
    if(root == nullptr){
        m_size++;
        root = newNode;
        return;
    }
    AVLNode *tmp = root;
    AVLNode *parent = tmp->parent;
    while(tmp != nullptr){
        if(tmp->Val > val) {
            parent = tmp;
            tmp = tmp->left;
        }else if(tmp->Val < val){
            parent = tmp;
            tmp = tmp->right;
        }else{ //相等
            parent = tmp;
        }
    }
    if(parent->Val > val){
        parent->left = newNode;
        newNode->parent = parent;
    }else if(parent->Val < val){
        parent->right = newNode;
        newNode->parent = parent;
    }else{
        return;
    }
    m_size++;
    return;
}

