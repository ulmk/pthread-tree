#ifndef TREE_H
#define TREE_H

typedef struct Node Node;

Node* newNode(int data);
void insert(Node** root, int data);
void inorder(Node* root);
void freeTree(Node* root);

void insert_wrapper(int data);
void inorder_wrapper();
void freeTree_wrapper();

#endif //  _TREE_H_