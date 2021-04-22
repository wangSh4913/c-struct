#include <iostream>
#include <queue>
#include <stack>
#include "include/binaruSerchTree.h"

using namespace std;

void BinarySerchTree::add(int val){
    Node *newNode = new Node(val);
    if(root == nullptr){
        m_size++;
        root = newNode;
        return;
    }
    Node *tmp = root;
    Node *parent = tmp->parent;
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

void BinarySerchTree::remove(int val){
    Node* tmp = node(root, val);
    if(tmp == nullptr){
        cout << "remove value is not exist" << endl;
        return;
    }
    m_size--;
    if(tmp->left != nullptr && tmp->right != nullptr){ //度为2的节点
        //找到后继节点，由于后继节点只能度为1或者2，所以复制后继节点的值，然后把要删除的节点改为后继节点
        Node* su = successor(root);
        tmp->Val = su->Val;
        tmp = su;
    }
    if(tmp->left == nullptr && tmp->right == nullptr){ //度为0的节点
        if(tmp->parent == nullptr){ //度为0且没有父节点，则是只有根节点的树
            root = nullptr;
        }else{ 
            if(tmp == tmp->parent->right){
                tmp->parent->right = nullptr;
            }else{
                tmp->parent->left = nullptr;
            }
        }
    }else if(tmp->left == nullptr){ //度为1的节点
        tmp->parent->right = tmp->right;
        tmp->right->parent = tmp->parent;
    }else if(tmp->right == nullptr){
        tmp->parent->left = tmp->left;
        tmp->left->parent = tmp->parent;
    }
}

bool BinarySerchTree::contains(int val){
    printf("bool BinarySerchTree::contains(int val) %p\n",root);
    printf("bool BinarySerchTree::contains(int val) %p\n",*root);
    return node(root, val) != nullptr;
}

void BinarySerchTree::clear(){
    m_size = 0;
    root = nullptr;
}

void BinarySerchTree::preorder(){
    preorder(root);
    cout << endl;
}

void BinarySerchTree::preorder(Node *root){
    if(root == nullptr){
        return;
    }

    cout << root->Val << " ";
    preorder(root->left);
    preorder(root->right);
}

void BinarySerchTree::preorder(void (*func)(int)){
    if (func != nullptr){
        preorder(root, func);
    }else{
        preorder(root);
    }
    cout << endl;
}

void BinarySerchTree::preorder(Node *root, void (*func)(int)){
    if(root == nullptr){
        return;
    }
    /*
    stack<Node*> stack;
    stack.push(root);
    while(!stack.empty()){
        if(stack.top()==nullptr){
            stack.pop();
            continue;
        }
        Node *tmp = stack.top();
        func(tmp->Val);
        stack.pop();
        stack.push(tmp->right);
        stack.push(tmp->left);
    }
    */

    func(root->Val);
    preorder(root->left, func);
    preorder(root->right, func);

}

void BinarySerchTree::inorder(void (*func)(int)){
    inorder(root, func);
    cout << endl;
}
void BinarySerchTree::inorder(Node *root, void (*func)(int)){
    stack<pair<Node*,bool>> stack;
    stack.push(make_pair(root,false));
    while(!stack.empty()){
        if (stack.top().first == nullptr)
        {
            stack.pop();
            continue;
        }
        Node *tmp = stack.top().first;
        bool visit = stack.top().second;
        stack.pop();
        if(visit){
            func(tmp->Val);
        }
        else{
            stack.push(make_pair(tmp->right,false));
            stack.push(make_pair(tmp,true));
            stack.push(make_pair(tmp->left,false));
        }
    }
}


void BinarySerchTree::leveltraversal(void (*func)(int)){
    leveltraversal(root, func);
}

void BinarySerchTree::leveltraversal(Node *root,void (*func)(int)){
    queue<Node*> Tree;
    Tree.push(root);
    while(!Tree.empty()){
        if (Tree.front()==nullptr)
        {
            Tree.pop();
            continue;
        }
        func(Tree.front()->Val);
        Tree.push(Tree.front()->left);
        Tree.push(Tree.front()->right);
        Tree.pop();
    }
}

int BinarySerchTree::height(){
    return height1(root);
}

int BinarySerchTree::height1(Node *root){
    queue<Node *> queue;
    queue.push(root);
    int levelsize = 1;
    int height = 0;
    while(!queue.empty()){
        Node *tmp = queue.front();
        queue.pop();
        if(tmp->left != nullptr){
            queue.push(tmp->left);
        }
        if(tmp->right != nullptr){
            queue.push(tmp->right);
        }
        levelsize--;
        if(levelsize == 0){
            levelsize = queue.size();
            height++;
        }
    }
    return height;
}

int BinarySerchTree::height(Node *root){
    if(root == nullptr){
        return 0;
    }
    int max = height(root->left) > height(root->right) ? height(root->left) : height(root->right);
    return 1 + max;
}

bool BinarySerchTree::isComplete(){
    if(root == nullptr){
        return false;
    }
    bool isLeaf = false; 
    queue<Node*> queue;
    queue.push(root);
    while(!queue.empty()){
        Node *tmp = queue.front();
        queue.pop();
        if(isLeaf && (tmp->left != nullptr || tmp->right != nullptr)){
            return false;
        }
        if(tmp->left != nullptr && tmp->right != nullptr){
            queue.push(tmp->left);
            queue.push(tmp->right);
        }else if(tmp->left == nullptr && tmp->right != nullptr){
            return false;
        }else{
            isLeaf = true;
            if(tmp->left != nullptr){
                queue.push(tmp->left);
            }
        }
    }
    return true;
}

/*
前驱后继节点概念：中序遍历一个二叉树，某一个节点的前一个或后一个节点
思路：
1. 如果有左子树，则找左子节点下面最右的节点
2. 如果没有左子树，则一直向上找父节点，直到某个节点是父节点的右子节点为止
3. 没有左子树也没有父节点，则前驱节点为空
*/
Node *BinarySerchTree::predecessor(Node *node){
    if(node == nullptr){
        return node;
    }
    Node *tmp = node->left;
    if(tmp != nullptr){
        while(tmp->right != nullptr){
            tmp = tmp->right;
        }        
        return tmp;
    }

    if(node->left == nullptr && node->parent != nullptr){
        while(node->parent != nullptr && node != node->parent->right){
            node = node->parent;
        }
    }
    return node->parent;
}

Node *BinarySerchTree::successor(Node *node){
    if(node == nullptr){
        return node;
    }
    Node *tmp = node->right;
    if(tmp != nullptr){
        while(tmp->left != nullptr){
            tmp = tmp->left;
        }        
        return tmp;
    }

    if(node->right == nullptr && node->parent != nullptr){
        while(node->parent != nullptr && node != node->parent->left){
            node = node->parent;
        }
    }
    return node->parent;
}

Node* BinarySerchTree::node(Node *root, int key){
    if(root == nullptr){
        return nullptr;
    }
    while(root != nullptr){
        if(key > root->Val){
            root = root->right;
        }else if(key < root->Val){
            root = root->left;
        }else{
            return root;
        }
    }
    return nullptr;
}

void BinarySerchTree::test(){
    Node *tmp = root;   
    while(tmp != nullptr){
        tmp = successor(tmp);
        if(tmp != nullptr){
            cout << "successor is :" << tmp->Val << endl;
        }
    }
}

