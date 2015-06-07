#ifndef __SPLAY_H__
#define __SPLAY_H__
struct node;
typedef struct node node_t;

struct node
{
    Node(){left = right = parent = NULL;size=1;}
    int value;
    int size;
    Node* left,*right,*parent;
};

typedef struct _splay_tree{
	node_t* root;
	int size;
	int (*seeker)(const node_t* n,const char* key);
	int (*comparator)(const node_t* a, const node_t* b);
	void* (*copy)( void*); /* make a copy of the input argument and return the copy */
	void  (*free)(void*); 
}splay_tree_t;


void splay_tree_init(splay_tree_t* tree,
	int (*seeker)(const node_t* n,const char* key),
	int (*comparator)(const node_t* a, const node_t* b),
	void* (*copy)( void*),
	void  (*free)(void*)
);
void splay_tree_insert(splay_tree_t* tree, void *data);

void spaly_tree_destroy(splay_tree_t* tree);
  
#endif
    
    
