// Assignment 1 
// Sahmaya Anderson-Edwards 
// Student ID: 24012404 

#include <stdio.h>
#include <stdlib.h>

// Defining Struct Node
struct Node {
    int index;
    int value;
    struct Node* next;
};
typedef struct Node Node;

void AddNode(Node** listpointer, int indx, int val) {
// Function to add new nodes ensuring the indices stay in order 
    Node* newNode = (Node*)malloc(sizeof(Node)); // allocates memory for the node
    if (newNode == NULL) {
        return;
    }
    newNode->index = indx;        
    newNode->value = val;
    newNode->next = NULL;

    if (*listpointer == NULL) {
        *listpointer = newNode;
        return;
    }
    if ((*listpointer)->index > indx) {
        newNode->next = *listpointer;
        *listpointer = newNode;
        return;
    }

    Node* current = *listpointer;
    Node* previous = NULL;
    while (current != NULL) {
        if (current->index >= indx) {
            break;
        }
        previous = current;
        current = current->next;
    }
    newNode->next = current;
    if (previous != NULL) {
        previous->next = newNode;
    }
}
void ReadSparseVector(Node** listpointer) {
// Function to read the sparse vectors from the input 
    int n;
    int indx;
    int val;
    scanf("%d", &n);
    *listpointer = NULL;
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &indx, &val);
        if (val != 0) {
            AddNode(listpointer, indx, val);
        }
    }
}

void PrintSparseVector(Node* listpointer) {
// Function to print the sparse vector output in the format n, index, value 
    int count = 0; // initialise 
    Node* current = listpointer;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    printf("%d", count);
    
    current = listpointer;
    while (current != NULL) {
        printf(" %d %d", current->index, current->value);
        current = current->next;
    }
    printf("\n");
}

void AddSparseVector(Node* vector1, Node* vector2, Node** result) {
// Function to add the two sparse vectors together, 
    *result = NULL; // initializes list 

    // While loop to sort through both vectors as long as at least one of them contains values 
    while (vector1 != NULL || vector2 != NULL) {
        int indx;
        int val;

        // If vector 2 is empty then copy values from vector 1 as we are adding a value + 0 
        if (vector2 == NULL) {
            indx = vector1->index;
            val = vector1->value;
            vector1 = vector1->next;
        } 
        // If vector 1 is empty then copy values from vector 2 as we are adding a value + 0 
        else if (vector1 == NULL) {
            indx = vector2->index;
            val = vector2->value;
            vector2 = vector2->next;
        } 
        // If both vectors contain values then add the smaller index first 
        else {
            if (vector1->index < vector2->index) {
                indx = vector1->index;
                val = vector1->value;
                vector1 = vector1->next;
            } 
            // If vector 2 is smaller add first 
            else if (vector2->index < vector1->index) {
                indx = vector2->index;
                val = vector2->value;
                vector2 = vector2->next;
            } 
            // if the indices are the same then add the values
            else { 
                indx = vector1->index;
                val = vector1->value + vector2->value;
                vector1 = vector1->next;
                vector2 = vector2->next;
            }
        }
        // add and save the values that do not equal 0 (non-zero values)
        if (val != 0) {
            AddNode(result, indx, val);
        }
    }
}

void FreeList(Node* listpointer) {
// Function to free allocated memory
    Node* temp;
    while (listpointer != NULL) {
        temp = listpointer;
        listpointer = listpointer->next;
        free(temp);
    }
}

// Main function to execute code 
int main() {
    Node* vector1 = NULL;
    Node* vector2 = NULL;
    Node* result = NULL;

    ReadSparseVector(&vector1);
    ReadSparseVector(&vector2);

    AddSparseVector(vector1, vector2, &result);
    PrintSparseVector(result);

    FreeList(vector1);
    FreeList(vector2);
    FreeList(result);

    return 0;
}

