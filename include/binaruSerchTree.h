
struct Node{
    int Val;
    Node *left;
    Node *right;
    Node *parent;
    Node():Val(0),left(nullptr),right(nullptr),parent(nullptr){}
    Node(int val):Val(val){
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }
    Node(int val, Node *parent):Val(val), parent(parent){
        left = nullptr;
        right = nullptr;
    }
};

class BinarySerchTree{
private:
    int m_size;
    Node *root;
public:
    class Vistor{
        virtual void visit(int val);
    };
    BinarySerchTree(){root = nullptr; m_size = 0;}
    int size() {return m_size;}
    bool isEmpty() {return m_size == 0;}
    void clear();
    void add(int val);
    void remove(int val);
    bool contains(int val);
    void preorder();
    void preorder(Node *root);
    void preorder(void (*func)(int));
    void preorder(Node *root, void (*func)(int));
    void inorder(void (*func)(int));
    void inorder(Node *root, void (*func)(int));
    void leveltraversal(void (*func)(int));
    void leveltraversal(Node *root,void (*func)(int));
    int height();
    int height(Node *root);  //迭代
    int height1(Node *root); //递归
    bool isComplete(); //是否是完全二叉树（叶子节点只会出现在最后两层，且最后一层的叶子节点全部左对齐）
    Node *predecessor(Node *node); //找前驱节点
    Node *successor(Node *node);   //找后继节点
    Node* node(Node *root, int key); //找一个节点
    void test();
};