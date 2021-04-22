#include "./binaruSerchTree.h"

struct AVLNode{
    int Val;
    int height;
    AVLNode *left;
    AVLNode *right;
    AVLNode *parent;
    AVLNode():Val(0),left(nullptr),right(nullptr),parent(nullptr){}
    AVLNode(int val):Val(val){
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }
    AVLNode(int val, AVLNode *parent):Val(val), parent(parent){
        left = nullptr;
        right = nullptr;
    }
};

class AVLTree : public BinarySerchTree{
private:
    int m_size;
    AVLNode* root;
public:
    void add(int val);//添加元素
    void afferAdd();
};