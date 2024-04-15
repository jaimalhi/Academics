#include "list.h"
#include <stdlib.h>
#include <stdio.h>

// define static list heads & nodes
static List listHeadArray[LIST_MAX_NUM_HEADS];
static Node nodeArray[LIST_MAX_NUM_NODES];

// list stack utils
static int freeListHeads[LIST_MAX_NUM_HEADS];
static int freeListTopIndex = -1; // -1 = empty list

// node stack utils
static int freeNodes[LIST_MAX_NUM_NODES];
static int freeNodeTopIndex = -1; // -1 = empty list

// variable to control ensure list init only once
static bool stacksInitalized = false;
 
// helper function to initalize stack
static void initStack() {
    // reset stacktop during init & stack status
    freeListTopIndex = -1; 
    freeNodeTopIndex = -1;
    stacksInitalized = false;
    // fill list heads and nodes
    for (int i = 0; i < LIST_MAX_NUM_HEADS; i++) {
        freeListHeads[++freeListTopIndex] = i;
    }
    for(int i = 0; i < LIST_MAX_NUM_NODES; i++){
        freeNodes[++freeNodeTopIndex] = i;
    }
}

// Makes a new, empty list, and returns its reference on success. 
// Returns a NULL pointer on failure.
List* List_create(){
    if(!stacksInitalized){
        initStack();
        stacksInitalized = true;
    }

    // no list heads remaining
    if(freeListTopIndex == -1) return NULL;

    int i = freeListHeads[freeListTopIndex--];

    // init the list at index i
    listHeadArray[i].head = NULL;
    listHeadArray[i].tail = NULL;
    listHeadArray[i].curr = NULL;
    listHeadArray[i].size = 0;
    // list not out of bounds to begin
    listHeadArray[i].listStatus = LIST_NOT_OOB;

    return &listHeadArray[i];
}

// create a new node with value void* item
Node* Node_create(void* item){
    // no nodes remaining
    if(freeNodeTopIndex == -1) return NULL;
    // free index i from the top of node stack
    int i = freeNodes[freeNodeTopIndex--];

    nodeArray[i].item = item;
    nodeArray[i].prev = NULL;
    nodeArray[i].next = NULL;

    return &nodeArray[i];
}

// Returns the number of items in pList.
int List_count(List* pList){
    return pList->size;
}

// Returns a pointer to the first item in pList and makes the first item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_first(List* pList){
    if(pList == NULL) return NULL;

    // if list empty return NULL
    if(pList->size == 0){
        pList->curr = NULL;
        return NULL;
    }
    pList->curr = pList->head;
    return pList->head->item;
}

// Returns a pointer to the last item in pList and makes the last item the current item.
// Returns NULL and sets current item to NULL if list is empty.
void* List_last(List* pList){
    if(pList == NULL) return NULL;

    // if list empty return NULL
    if(pList->size == 0){
        pList->curr = NULL;
        return NULL;
    }
    pList->curr = pList->tail;
    return pList->tail->item;
}

// Advances pList's current item by one, and returns a pointer to the new current item.
// If this operation advances the current item beyond the end of the pList, a NULL pointer 
// is returned and the current item is set to be beyond end of pList.
void* List_next(List* pList){
    if(pList == NULL) return NULL;

    if(pList->curr == NULL || pList->curr->next == NULL){
        pList->curr = NULL;
        pList->listStatus = LIST_OOB_END;
        return NULL;
    }
    pList->curr = pList->curr->next;
    return pList->curr->item;
}

// Backs up pList's current item by one, and returns a pointer to the new current item. 
// If this operation backs up the current item beyond the start of the pList, a NULL pointer 
// is returned and the current item is set to be before the start of pList.
void* List_prev(List* pList){
    if(pList == NULL) return NULL;

    if(pList->curr == NULL || pList->curr->prev == NULL){
        pList->curr = NULL; //beyond list is set to NULL
        pList->listStatus = LIST_OOB_START;
        return NULL;
    }
    pList->curr = pList->curr->prev;
    return pList->curr->item;
}

// Returns a pointer to the current item in pList.
void* List_curr(List* pList){
    if(pList == NULL || pList->curr == NULL) return NULL;
    return pList->curr->item;
}

// Adds the new item to pList directly after the current item, and makes item the current item. 
// If the current pointer is before the start of the pList, the item is added at the start. If 
// the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert_after(List* pList, void* pItem){
    if(pList == NULL) return LIST_FAIL;

    Node* newNode = Node_create(pItem);
    if(newNode == NULL) return LIST_FAIL;

    if(pList->size == 0){ 
        // list empty
        pList->head = pList->tail = pList->curr = newNode;
    } else if(pList->curr != NULL) { 
        // list exists
        newNode->next = pList->curr->next;
        newNode->prev = pList->curr;

        if(pList->curr->next != NULL) pList->curr->next->prev = newNode;
        else pList->tail = newNode;

        pList->curr->next = newNode;
        pList->curr = newNode;
    } else if(pList->listStatus == LIST_OOB_START){
        // out of bounds (before head)
        newNode->next = pList->head;
        pList->head->prev = newNode;
        pList->head = pList->curr = newNode;
    } else if(pList->listStatus == LIST_OOB_END){
        // out of bounds (after tail)
        newNode->prev = pList->tail;
        pList->tail->next = newNode;
        pList->tail = pList->curr = newNode;
    }

    pList->size++;
    return LIST_SUCCESS;
}

// Adds item to pList directly before the current item, and makes the new item the current one. 
// If the current pointer is before the start of the pList, the item is added at the start. 
// If the current pointer is beyond the end of the pList, the item is added at the end. 
// Returns 0 on success, -1 on failure.
int List_insert_before(List* pList, void* pItem){
    if(pList == NULL) return LIST_FAIL;

    Node* newNode = Node_create(pItem);
    if(newNode == NULL) return LIST_FAIL;

    if(pList->size == 0){
        // list empty 
        pList->curr = pList->head = pList->tail = newNode;
    } else if(pList->curr != NULL) {
        // list exists 
        newNode->prev = pList->curr->prev;
        newNode->next = pList->curr;

        if(pList->curr->prev != NULL) pList->curr->prev->next = newNode;
        else pList->head = newNode;

        pList->curr->prev = newNode;
        pList->curr = newNode;
    } else if(pList->listStatus == LIST_OOB_START){ 
        // out of bounds (before head) 
        newNode->next = pList->head;
        pList->head->prev = newNode;
        pList->curr = pList->head = newNode;
    } else if(pList->listStatus == LIST_OOB_END){ 
        // out of bounds (after tail)  
        newNode->prev = pList->tail;
        pList->tail->next = newNode;
        pList->curr = pList->tail = newNode;
    }

    pList->size++;
    return LIST_SUCCESS;
}

// Adds item to the end of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_append(List* pList, void* pItem){
    // dont append if size greater than nodes available
    if(pList == NULL || pList->size >= LIST_MAX_NUM_NODES) return LIST_FAIL;

    Node* newNode = Node_create(pItem);
    if(newNode == NULL) return LIST_FAIL;

    newNode->prev = pList->tail;
    pList->tail = pList->curr = newNode;

    // if list empty adjust head
    if(pList->size == 0) {
        pList->head = newNode;
    } else {
        newNode->prev->next = newNode;
    }

    pList->size++;
    return LIST_SUCCESS;
}

// Adds item to the front of pList, and makes the new item the current one. 
// Returns 0 on success, -1 on failure.
int List_prepend(List* pList, void* pItem){
    if(pList == NULL) return LIST_FAIL;

    Node* newNode = Node_create(pItem);
    if(newNode == NULL) return LIST_FAIL;

    newNode->next = pList->head;
    pList->head = pList->curr = newNode;

    // if list empty adjust tail
    if(pList->size == 0) {
        pList->tail = newNode;
    } else {
        newNode->next->prev = newNode;
    }

    pList->size++;
    return LIST_SUCCESS;
}

// helper function for remove & trim
static void freeNode(Node* node){
    // if node stack full
    if (freeNodeTopIndex >= LIST_MAX_NUM_NODES-1){
         return;
    } else {
        // remove the node from list and adjust stack
        node->next = NULL;
        node->prev = NULL;
        node->item = NULL; 
        freeNodes[++freeNodeTopIndex] = node - nodeArray;
    }
}

// Return current item and take it out of pList. Make the next item the current one.
// If the current pointer is before the start of the pList, or beyond the end of the pList,
// then do not change the pList and return NULL.
void* List_remove(List* pList){
    // base cases
    // if(pList->listStatus == LIST_OOB_START || pList->listStatus == LIST_OOB_END) return NULL;
    if(pList->size == 0) return NULL;
    if(pList == NULL) return NULL;

    Node* tempRemovalNode = pList->curr;
    void* tempRemovalItem = pList->curr->item;

    // check prev and next
    if(tempRemovalNode->prev != NULL) tempRemovalNode->prev->next = tempRemovalNode->next;
    if(tempRemovalNode->next != NULL) tempRemovalNode->next->prev = tempRemovalNode->prev;

    // if node to remove is the head
    if (tempRemovalNode == pList->head){
        pList->head = tempRemovalNode->next;
        if (pList->head != NULL) pList->head->prev = NULL;
        else pList->listStatus = LIST_OOB_START;
    }
    
    // if node to remove is the tail
    if (tempRemovalNode == pList->tail) {
        pList->tail = tempRemovalNode->prev;
        if (pList->tail != NULL) pList->tail->next = NULL;
        else pList->listStatus = LIST_OOB_END;
    }
    
    pList->size--;
    pList->curr = tempRemovalNode->next;
    freeNode(tempRemovalNode);

    return tempRemovalItem;
}

// Return last item and take it out of pList. Make the new last item the current one.
// Return NULL if pList is initially empty.
void* List_trim(List* pList){
    // base cases
    if(pList->listStatus == LIST_OOB_START || pList->listStatus == LIST_OOB_END) return NULL;
    if(pList->size == 0) return NULL;
    if(pList == NULL) return NULL;

    Node* tempRemovalNode = pList->tail;
    void* tempRemovalItem = pList->tail->item;

    // one item in the list
    if(pList->size == 1) {
        pList->tail = pList->head = pList->curr = NULL;
    } else { // update new tail and current
        Node* prevNode = tempRemovalNode->prev;
        prevNode->next = NULL;
        pList->tail = pList->curr = prevNode;
    }
    pList->size--;
    freeNode(tempRemovalNode);
    
    return tempRemovalItem;
}

// helper function for concat & free
static void freeList(List* list){
    // if list stack full
    if (freeListTopIndex >= LIST_MAX_NUM_HEADS-1){
        return;
    } else {
        list->head = NULL;
        list->tail = NULL;
        list->curr = NULL;
        list->size = 0;
        freeListHeads[++freeListTopIndex] = list - listHeadArray;
    }
}

// Adds pList2 to the end of pList1. The current pointer is set to the current pointer of pList1. 
// pList2 no longer exists after the operation; its head is available
// for future operations.
void List_concat(List* pList1, List* pList2){
    // list1 or list2 dont exist
    if (pList1 == NULL || pList2 == NULL) return;

    if (pList1->size == 0 && pList2->size == 0) {
        // both lists empty
        freeList(pList2);
    } else if (pList1->size == 0) { 
        // pList1 is empty, merge p2 into p1
        pList1->head = pList2->head;
        pList1->tail = pList2->tail;
        pList1->size = pList2->size;
        pList1->curr = NULL;
        pList1->listStatus = LIST_OOB_START;
        freeList(pList2); 
    } else if (pList2->size == 0) { 
        // pList2 is empty 
        freeList(pList2);
    } else { 
        // both lists filled
        pList1->tail->next = pList2->head;
        pList2->head->prev = pList1->tail;
        pList1->tail = pList2->tail;
        pList1->size += pList2->size;
        freeList(pList2);
    }
}

// Delete pList. pItemFreeFn is a pointer to a routine that frees an item. 
// It should be invoked (within List_free) as: (*pItemFreeFn)(itemToBeFreedFromNode);
// pList and all its nodes no longer exists after the operation; its head and nodes are 
// available for future operations.
void List_free(List* pList, FREE_FN pItemFreeFn){
    // base cases
    if (pList == NULL || pItemFreeFn == NULL) return;

    // iterate and free nodes
    for (Node* currNode = pList->head; currNode != NULL; ) {
        Node* nextNode = currNode->next;
        pItemFreeFn(currNode->item); // use FREE_FN 
        freeNode(currNode);
        currNode = nextNode;
    }

    freeList(pList);
}

// Search pList, starting at the current item, until the end is reached or a match is found. 
// In this context, a match is determined by the comparator parameter. This parameter is a
// pointer to a routine that takes as its first argument an item pointer, and as its second 
// argument pComparisonArg. Comparator returns 0 if the item and comparisonArg don't match, 
// or 1 if they do. Exactly what constitutes a match is up to the implementor of comparator. 
// 
// If a match is found, the current pointer is left at the matched item and the pointer to 
// that item is returned. If no match is found, the current pointer is left beyond the end of 
// the list and a NULL pointer is returned.
// 
// If the current pointer is before the start of the pList, then start searching from
// the first node in the list (if any).
void* List_search(List* pList, COMPARATOR_FN pComparator, void* pComparisonArg){
    if (pList == NULL || pComparator == NULL) return NULL;

    // current pointer before the start of pList, start from first node
    if (pList->listStatus == LIST_OOB_START && pList->curr == NULL) pList->curr = pList->head;

    // Searching from the current node
    for (Node* currentNode = pList->curr; currentNode != NULL; currentNode = currentNode->next) {
        // check if item matches using COMPARATOR_FN
        if (pComparator(currentNode->item, pComparisonArg) == 1) {
            pList->curr = currentNode;
            return currentNode->item;
        }
    }

    //No match found, set attributes for pList
    pList->listStatus = LIST_OOB_END;
    pList->curr = NULL;

    return NULL;
}