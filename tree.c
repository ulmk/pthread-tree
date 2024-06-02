#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "tree.h"

typedef struct Node {
    int data;
    struct Node *left, *right;
    pthread_mutex_t mu;
} Node;


Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    pthread_mutex_init(&node->mu, NULL);
    return node;
}

void insert(Node** root, int data){
    if (*root == NULL) {
        *root = newNode(data);
        return;
    }

    Node* temp = *root;
    while (1) {
        pthread_mutex_lock(&temp->mu);
        if (data < temp->data) {
            if (temp->left == NULL) {
                temp->left = newNode(data);
                pthread_mutex_unlock(&temp->mu);
                break;
            } else {
                pthread_mutex_unlock(&temp->mu);
                temp = temp->left;
            }
        } else {
            if (temp->right == NULL) {
                temp->right = newNode(data);
                pthread_mutex_unlock(&temp->mu);
                break;
            } else {
                pthread_mutex_unlock(&temp->mu);
                temp = temp->right;
            }
        }
    }
}

void inorder(Node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d", root->data);
    inorder(root->right);
}

void freeTree(Node* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    pthread_mutex_destroy(&root->mu);
    free(root);
}

// Node * root = NULL;

// void insert_wrapper(int data) {
//     insert(&root, data);
// }

// void inorder_wrapper(){
//     inorder(root);
// }

// void free_wrapper(){
//     freeTree(root);
//     root = NULL;
// }
typedef struct {
    Node** root;
    int* values;
} ThreadArgs;

void* threadFunction(void* arg) {
    ThreadArgs* args = (ThreadArgs*)arg;
    Node** root = args->root;
    int* values = args->values;

    for (int i = 0; i < 10; i++) {
        insert(root, values[i]);
    }
    return NULL;
}

void* print_message(void* ptr) {
    char* message = (char*)ptr;
    printf("%s\n", message);
    return NULL;
}

// int main() {
//     Node* root = NULL;
//     pthread_t thread1, thread2;
//    //     char* message1 = "Thread 1";
//    // char* message2 = "Thread 2";
//     int values1[] = {5, 3, 7, 1, 4, 6, 8, 2, 9, 10};
//     int values2[] = {50, 30, 70, 10, 40, 60, 80, 20, 90, 100};

//     ThreadArgs args1 = { &root, values1 };
//     ThreadArgs args2 = { &root, values2 };

//     pthread_create(&thread1, NULL, threadFunction, (void*)&args1);
//     pthread_create(&thread2, NULL, threadFunction, (void*)&args2);

//     // pthread_create(&thread1, NULL, print_message, (void*)message1);
//    //pthread_create(&thread2, NULL, print_message, (void*)message2);

//     pthread_join(thread1, NULL);
//     pthread_join(thread2, NULL);

//     // Traverse the tree and print the values
//     printf("%s\n", "printing tree");
//     inorder(root);
//     printf("\n");

//     return 0;
// }



// int main() {
//     pthread_t thread1, thread2;
//     char* message1 = "Thread 1";
//     char* message2 = "Thread 2";

//     pthread_create(&thread1, NULL, print_message, (void*)message1);
//     pthread_create(&thread2, NULL, print_message, (void*)message2);

//     pthread_join(thread1, NULL);
//     pthread_join(thread2, NULL);

//     return 0;
// }


// int main() {
//     Node* root = NULL;

//     insert(&root, 10);
//     insert(&root, 5);
//     insert(&root, 15);
//     insert(&root, 25);
//     insert(&root, 35);
//     insert(&root, 2);
//     inorder(root);
// }

