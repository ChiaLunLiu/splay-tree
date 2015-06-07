#include<cstdio>
#include<iostream>
#define SIZE 1024
using namespace std;
struct Node
{
    Node(){left = right = parent = NULL;size=1;}
    int value;
    int size;
    struct Node* left,*right,*parent;
};
struct SplayTree
{
public:
    void init();
    struct Node* find(int x);
    void remove(int x);
    void insert(int x);
    struct Node* predecessor(int x);
    struct Node* successor(int x);
    friend void print(struct Node* r);
    struct Node* getRoot(){return root;}
private:
    struct Node* bst_search(int x);
    struct Node* bst_insert(int x);
    struct Node* maximum(struct Node* r);
    struct Node* minimum(struct Node* r);
    void splay(struct Node* r);
    void leftRotate(struct Node* r);
    void rightRotate(struct Node* r);
    struct Node* join(struct Node* left,struct Node* right);
    struct Node* root;
};
void print(struct Node* r);

int main()
{
    int k,v;
    puts("1: insert, 2 : find, 3 : delete");
    SplayTree tree;
    tree.init();
    while(cin>>k>>v)
    {
        if(k==1)tree.insert(v);
        else if(k==2)
        {
            if(tree.find(v)) puts("found");
            else puts("not found");
        }
        else if(k==3)
        {
            tree.remove(v);
        }
        print(tree.getRoot());
        puts("");
       // if(root)
       // printf("root value : %d\n",root->value);
      //  inorder_traversal(root);puts("");
    }
    return 0;
}
struct Node* SplayTree::find(int x)
{
    struct Node* a;
    a = bst_search(x);
    splay(a);
    return a;
}
struct Node* SplayTree::bst_search(int x)
{
    struct Node* cur = root,t;
    if(cur==NULL)return NULL;
    while(cur)
    {
        if(x < cur->value)cur = cur->left;
        else if(x > cur->value)cur = cur->right;
        else return cur;
    }
    return NULL;
}
void SplayTree::insert(int x)
{
    struct Node* r = bst_insert(x);
    splay(r);
}
struct Node* SplayTree::bst_insert(int x)
{
    struct Node* cur = root,*t;
    if(cur==NULL)
    {
        root = new Node;
        root->value = x;
        return root;
    }
    while(true)
    {
        cur->size++;
        if(x < cur->value)
        {
            if(!cur->left)
            {
                t = new Node;
                t->value = x; t->parent = cur;
                cur->left = t;
                return t;
            }
            cur = cur->left;
        }
        else
        {
            if(!cur->right)
            {
                t = new Node;
                t->value =x;t->parent = cur;
                cur->right = t;
                return t;
            }
            cur = cur->right;
        }
    }
    return NULL;
}
void SplayTree::remove(int x)
{
    struct Node* r = find(x);
    if(r)
    {
        if(r->left)r->left->parent = NULL;
        if(r->right)r->right->parent = NULL;
        root = join(r->left,r->right);
        delete r;
    }
}
struct Node* SplayTree::join(struct Node* left,struct Node* right)
{
    if(!left)return right;
    if(!right)return left;
    struct Node* r = maximum(left);
    r->right = right;
    r->size+=right->size;
    right->parent = r;
    return r;
}
struct Node* SplayTree::maximum(struct Node* r)
{
    if(!r)return NULL;
    while(r->right!=NULL) r = r->right;
    splay(r);
    return r;
}
struct Node* SplayTree::minimum(struct Node* r)
{
    if(!r)return NULL;
    while(r->left!=NULL)r = r->left;
    splay(r);
    return r;
}
void SplayTree::splay(struct Node* r)
{
    if(!r)return ;
    struct Node* father;
    while(r->parent)
    {
        father = r->parent;
        printf("value : %d\n",r->value);
        if(r == father->left)rightRotate(r);
        else leftRotate(r);
    }
    root = r;
}
void SplayTree::leftRotate(struct Node* r)
{
    struct Node* father = r->parent;
    struct Node* grandfather = father->parent;
    struct Node* leftSon = r->left;
    father->right = leftSon;
    if(leftSon) leftSon->parent = father;
    r->parent = grandfather;
    if(grandfather)
    {
        if(grandfather->left == father)
            grandfather->left = r;
        else
            grandfather->right = r;
    }
    r->parent = grandfather;
    r->left = father;
    father->parent = r;

    int t = father->size;
    father->size -= r->size;
    if(leftSon)father->size+=leftSon->size;
    r->size = t;

}
void SplayTree::rightRotate(struct Node* r)
{
    struct Node* father = r->parent;
    struct Node* grandfather = father->parent;
    struct Node* rightSon = r->right;

    father->left = rightSon;
    if(rightSon)rightSon->parent = father;
    r->parent = grandfather;
    if(grandfather)
    {
        if(grandfather->left == father)
            grandfather->left = r;
        else
            grandfather->right = r;
        r->parent = grandfather;
    }
    r->right = father;
    father->parent = r;

    int t = father->size;
    father->size -= r->size;
    if(rightSon)father->size+=rightSon->size;
    r->size = t;
}
void print(struct Node* r)
{
    if(r)
    {

        print(r->left);printf("%d ,size :%d\n",r->value,r->size);
        print(r->right);
    }
}
struct Node* SplayTree::predecessor(int x)
{
    struct Node* r = find(x);
    if(!r || !r->left)return NULL;
    return maximum(r->left);
}
struct Node* SplayTree::successor(int x)
{
    struct Node* r = find(x);
    if(!r || !r->right)return NULL;
    return minimum(r->right);
}
void SplayTree::init()
{
    root = NULL;
}
