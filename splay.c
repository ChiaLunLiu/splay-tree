#include "splay.h"
/* private function */
static node_t* splay_tree_bst_insert(splay_tree_t* tree,void * data);

void splay_tree_init(splay_tree_t* tree,
	int (*seeker)(const node_t* n,const char* key),
	int (*comparator)(const node_t* a, const node_t* b),
	void* (*copy)( void*),
	void  (*free)(void*)
)
{
	tree->root = NULL;
	tree->size = 0;
	tree->seeker = seeker;
	tree->comparator = comparator;
	tree->copy = copy;
	tree->free = free;
}


void splay_insert(splay_tree_t* tree,void *data)
{
    node_t* r = bst_insert(tree,data);
    if(r) splay(r);
}


node_t* splay_tree_bst_insert(splay_tree_t* tree,void * data)
{
    node_t* cur = root,*t;
    if(cur==NULL)
    {
        root = malloc(sizeof( node_t) );//new Node;
        if(!root) return NULL;
        root->value = x;
        return root;
    }
    while(1)
    {
        cur->size++;
        if( x < cur->value)
        {
            if(!cur->left)
            {
                t = malloc( sizeof( node_t));
                if(!t)return NULL;
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
                t = malloc(sizeof( node_t));
                if(!t)return NULL;
                t->value =x;t->parent = cur;
                cur->right = t;
                return t;
            }
            cur = cur->right;
        }
    }
    return NULL;
}
