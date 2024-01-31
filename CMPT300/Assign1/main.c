#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// mock assert helper function
void mockAssert(bool stm, char* msg) {
    printf ("\n%s : %s\n", msg, stm? "PASS": "FAIL");
    if (!stm) {
        perror("=====================\nTEST FAILED: EXITING\n=====================");
        exit(1);
    }
}

// helper free fn for List_free() testing
void testFree(void* pItem) {
    // do nothing since static implementation
}

void test_create_list(int *numheads, int *numnodes) {
    printf("testing create_list()\n");
    List *list = List_create();
    if (*numheads == LIST_MAX_NUM_HEADS) {
        mockAssert(list == NULL,"not enough room, no list created");
    } else {
        mockAssert(list != NULL,"list created successfully");
        (*numheads)++;
        mockAssert(list->head == NULL,"head should be NULL");
        mockAssert(list->tail == NULL,"tail should be NULL");
        mockAssert(list->curr == NULL,"current should be NULL");
        mockAssert(list->size == 0,"size should be 0");
    }
    List_free(list, testFree);
}

void test_list_count(){
    printf("\ntesting list_count()\n");
    int item = 1;

    //general cases
    List* list = List_create();
    for(int i = 0;i < 6;i++){
        if(i == 0){
            mockAssert(list->size == i, "list size=0");
        }
        else if(i == 1){
            mockAssert(list->size == i, "list size=1");
        }
        else if(i == 5){
            mockAssert(list->size == i, "list size=5");
        }
        List_append(list, &item);
    }

    // testing when removing a node
    List_trim(list);
    mockAssert(list->size == 5,"decrements size 6 to 5");

    //set i to append to an unnecessary amount of times
    bool failTest = false;
    for(int i = 0; i < 500; i++){
        if(list->size == 101){
            failTest = true;
        }
        List_append(list, &item);
    }

    if(failTest){
        printf("testList->size exceeded LIST_MAX_NUM_NODES: FAIL\n");
    } else {
        printf("testList->size in expected range (0-100): PASS\n");
    }

    List_free(list, testFree);
}

void test_list_first(){
    printf("\ntesting list_first()\n");
    List* list = List_create();
    int one = 1;
    int newValue = 3;

    for(int i = 0; i < 5; i++){
        int *firstItem = List_first(list);

        if(i == 0){
            mockAssert(firstItem == NULL, "empty list, first item should return NULL");
            List_append(list, &one);
        }
        if(i == 1){
            mockAssert(*firstItem == 1, "returned first item should = 1");
            List_prepend(list, &newValue);
        }
        if(i == 2){
            mockAssert(*firstItem == 3,"returned first item should = 3");
        }
    }

    List_free(list, testFree);
}

void test_list_last(){
    printf("\ntesting list_last()\n");
    List* list = List_create();

    int two = 2;
    int newValue = 5;

    for(int i = 0; i < 5; i++){
        int *lastItem = List_last(list);

        if(i == 0){
            mockAssert(lastItem == NULL, "empty list, returned last item should = NULL");
            List_append(list, &two);
        }
        if(i == 1){
            mockAssert(*lastItem == 2, "returned last item should = 2");
            List_prepend(list, &newValue); 
        }
        if(i==2){
            mockAssert(*lastItem == 2,"returned last item should remain = 2") ;
        }
    }

    List_free(list, testFree);
}

void test_list_next(){
    printf("\ntesting list_next()\n");
    List* list = List_create();
    int a = 1;
    int b = 5;
    int c = 3; 
    int testVal = 10; 
    int *arr[3] = {&a, &b, &c};

    // list empty case List_next
    void* listNextItem = List_next(list);
    mockAssert(list->curr == NULL && listNextItem == NULL,"when testList is empty and test list is advanced, return NULL");
    mockAssert(list->listStatus == LIST_OOB_END,"for empty list, advancing causes status to be set to LIST_OOB_END");

    // fill list with some arbitrary int values
    for(int i = 0; i < 3; i++){
        List_append(list, arr[i]);
    }

    List_prepend(list, &testVal);
    for(int i=0; i<7; i++){
        void* list_next_item = List_next(list);
        if(i == 2){
            mockAssert(list->tail->item == list->curr->item && list_next_item == list->curr->item,"Current item should traversed to the tail");
        }
        else if(i == 3){
            mockAssert(list->curr == NULL && list->listStatus == LIST_OOB_END && list_next_item == NULL,"The current should be NULL & reaches LIST_OOB_End as expected when advancing past boundary");
        }
        else if(i == 5){
            mockAssert(list->curr == NULL && list->listStatus == LIST_OOB_END && list_next_item == NULL,"testList->current should = NULL & status should remain as LIST_OOB_END");
        }
    }

    List_free(list, testFree);
}

void test_list_prev(){
    printf("\ntesting list_prev()\n");
    List* list = List_create();
    int a = 1;
    int b = 5;
    int c = 3; 
    int *arr[3] = {&a, &b, &c};

    // list empty case List_prev
    void* listPrevItem = List_prev(list);
    mockAssert(list->curr == NULL && listPrevItem == NULL, "when testList is empty & test list is backtracked, return NULL");
    mockAssert(list->listStatus == LIST_OOB_START, "for empty list, backtracking causes status to be set to LIST_OOB_Start");

    // fill list with some arbitrary int values
    for(int i = 0; i < 3; i++){
        List_append(list, arr[i]);
    }

    for(int i=0; i<5; i++){
        void* list_prev_item = List_prev(list);

        if(i==1){
            mockAssert(list->head->item == list->curr->item && list_prev_item == list->curr->item, "Current item should traversed backwards to the head");
        }
        else if(i==2){
            mockAssert(list->curr == NULL && list->listStatus == LIST_OOB_START && list_prev_item == NULL,"The current should = NULL & reache LIST_OOB_START as expected when backtracking past the boundary");
        }
        else if(i==4){
            mockAssert(list->curr == NULL && list->listStatus == LIST_OOB_START && list_prev_item == NULL,"testList->current should still = NULL & status should remain as LIST_OOB_START");
        }
    }

    List_free(list, testFree);
}

void test_list_curr(){
    printf("\ntesting list_curr()\n");
    List* list = List_create();
    int a = 1; 
    int b = 5; 
    int c = 3; 
    int *arr[3] = {&a,&b,&c};

    //empty list case
    void* currItem = List_curr(list);
    mockAssert((list->curr == NULL || list->curr->item == NULL) && currItem == NULL,"empty list current item should be NULL");

    for(int i = 0; i<3; i++){
        List_append(list, arr[i]);
        void* currItem = List_curr(list);
        if(i == 0){
            mockAssert(list->curr->item == &a && currItem == &a,"current item = 1");
        }
        else if(i == 1){
            mockAssert(list->curr->item == &b && currItem ==&b,"current item = 5");
        }
        else if(i == 2){
            mockAssert(list->curr->item == &c && currItem ==&c,"current item = 3");
        }
    }
    // checking NULL val for LIST_OOB_END
    List_next(list);
    currItem = List_curr(list);
    mockAssert((list->curr == NULL || list->curr->item == NULL) && currItem == NULL,"LIST_OOB_END should = zero");

    // checking NULL val for LIST_OOB_START
    List_prepend(list, &a);
    List_prev(list);
    currItem = List_curr(list);
    mockAssert((list->curr == NULL || list->curr->item == NULL) && currItem == NULL,"LIST_OOB_START should = zero");

    List_free(list, testFree);
}

void test_list_insert_after() {
    printf("\ntesting List_insert_after()\n");
    List* list = List_create();
    int a = 1;
    int b = 5;
    int c = 3; 
    int d = 7; 
    int e = 9;
    int f = 11;

    // Empty list case
    List_insert_after(list, &a);
    mockAssert(list->curr->item == &a && list->size == 1, "Size & curr item update accordingly when inserting into empty list");

    // Insert after the current item (middle of the list)
    List_append(list, &b);
    List_insert_after(list, &c);
    mockAssert(list->curr->item == &c && list->size == 3 && *((int*)List_prev(list)) == b, "Insert behaves correctly with items already in the list. The value before the new curr remains correct too");

    // Insert after the current item when it's at the start
    List_first(list);
    List_insert_after(list, &d);
    mockAssert(list->curr->item == &d && list->size == 4 && *((int*)List_prev(list)) == a, "If curr pointer is first item in the list, list_insert should work accordingly. The value before the new curr remains correct");

    // Insert when current is beyond the end
    List_last(list);
    List_next(list); // Move current beyond the end of list
    List_insert_after(list, &e);
    mockAssert(list->curr->item == &e && list->size == 5 &&list->tail->item == &e, "When LIST_OOB_END flag is triggered, still inserts item at the end of the list");

    // Insert when current is before the start
    List_first(list);
    List_prev(list); // Move current before the start
    List_insert_after(list, &f);
    mockAssert(list->curr->item == &f && list->size == 6 && list->head->item==&f, "When LIST_OOB_FIRST flag is triggered, still inserts item at the front of the list");
    
    List_free(list, testFree);
}

void test_list_insert_before() {
    printf("\ntesting List_insert_before()\n");
    List* list = List_create();
    int a = 1;
    int b = 5; 
    int c = 3; 
    int d = 7; 
    int e = 9; 
    int f = 11; 

    // Empty list case
    List_insert_before(list, &a);
    mockAssert(list->curr->item == &a && list->size == 1, "Size & curr item update accordingly when inserting into empty list");

    // Insert before the current item (middle of the list)
    List_append(list, &b);
    List_insert_before(list, &c);
    mockAssert(list->curr->item == &c && list->size == 3 && *((int*)List_next(list)) == b, "Insert behaves correctly with items already in the list. Value after the new curr remains correct");

    // Insert before the current item when it's at the end
    List_last(list);
    List_insert_before(list, &d);
    mockAssert(list->curr->item == &d && list->size == 4 && *((int*)List_next(list)) == b, "curr pointer is last item in the list, list_insert works accordingly. The value after the new curr should remains correct");

    // Insert when current is beyond the end
    List_last(list);
    List_next(list); // Move current beyond the end
    List_insert_before(list, &e);
    mockAssert(list->curr->item == &e && list->size == 5 && list->tail->item == &e, "When LIST_OOB_END flag is triggered, still inserts item at the end of the list");

    // Insert when current is before the start
    List_first(list);
    List_prev(list); // Move current before the start
    List_insert_before(list, &f);
    mockAssert(list->curr->item == &f && list->size == 6 && list->head->item == &f, "When LIST_OOB_START flag is triggered, still inserts item at the front of the list");
    
    List_free(list, testFree);
}

void test_List_append() {
    printf("\ntesting List_append()\n");
    List* list = List_create();

    // Create more than 100 items to exhaust nodes
    int values[101]; 
    for (int i = 0; i < 101; i++) {
        values[i] = i;
    }

    int appendResult;
    for (int i = 0; i < 101; i++) {
        appendResult = List_append(list, &values[i]);
        if (i == 99) {
            mockAssert(appendResult == LIST_SUCCESS, "Appending succeeds for the first 100 nodes");
        } else if(i == 100) {
            mockAssert(appendResult == LIST_FAIL, "Appending fails when the nodes exhausted");
        }
    }

    List_free(list, testFree);
}

void test_List_prepend() {
    printf("\ntesting List_prepend()\n");
    List* list = List_create();

    // Create more than 100 items to exhaust the nodes
    int values[101]; 
    for (int i = 0; i < 101; i++) {
        values[i] = i;
    }

    int prependResult;
    for (int i = 0; i < 101; i++) {
        prependResult = List_prepend(list, &values[i]);
        if (i == 99) {
            mockAssert(prependResult == LIST_SUCCESS, "Prepending succeeds for the first 100 nodes");
        } else if(i == 100) {
            mockAssert(prependResult == LIST_FAIL, "Prepending fails when the nodes exhausted");
        }
    }

    List_free(list, testFree);
}

void test_list_remove() {
    printf("\ntesting List_remove()\n");
    List* list = List_create();
    int a = 1;
    int b = 5;
    int c = 3;
    int *arr[3]= {&a,&b,&c};
    
    // removing from an empty list
    void* itemToRemove = List_remove(list);
    mockAssert(list->size == 0 || itemToRemove == NULL, "returns NULL when removing from an empty list");

    for(int i = 0; i < 3; i++){
        List_append(list, arr[i]); 
    }

    // removing from middle
    List_first(list);
    List_next(list); // Points to 'b'
    itemToRemove = List_remove(list);
    mockAssert(itemToRemove == &b && list->size == 2, "removes middle element correctly");

    // removing head
    List_first(list); // Point to 'a'
    itemToRemove = List_remove(list);
    mockAssert(*(int*)itemToRemove == a && list->size == 1 && list->head->item == &c, "removes the head correctly");

    // removing tail (which is also the head)
    itemToRemove = List_remove(list);
    mockAssert(*(int*)itemToRemove == c && list->size == 0 && list->head == NULL && list->tail == NULL, "removes the last remaining element (head and tail) correctly");

    // removing when current is beyond the end
    List_next(list);
    itemToRemove = List_remove(list);
    mockAssert(itemToRemove == NULL, "returns NULL when current is beyond the end");

    // removing when current is before the start
    List_prev(list);
    itemToRemove = List_remove(list);
    mockAssert(itemToRemove == NULL, "returns NULL when current is before the start");

    List_free(list, testFree);
}

void test_list_trim() {
    printf("\ntesting List_trim()\n");
    List* list = List_create();
    int a = 1;
    int b = 5; 
    int c = 3;
    int *arr[3] = {&a, &b, &c};

    // empty list case
    void* trimmedItem = List_trim(list);
    mockAssert(trimmedItem == NULL, "returns NULL when trimming from empty list");

    for(int i = 0; i < 3; i++){
        List_append(list, arr[i]);
    }

    for(int i = 0; i < 4; i++){
        trimmedItem = List_trim(list);
        // trimming from a list with multiple items
        if(i == 0){
            mockAssert(trimmedItem == &c && list->size == 2 && list->curr->item == &b, "trims the last element & sets current to the new last item");
        }
        else if(i == 1){ // trimming the new tail
            mockAssert(trimmedItem == &b && list->size == 1 && list->curr->item == &a, "trims the last element & sets current to the new last item");
        }
        else if(i == 2){ // trimming the last item
            mockAssert(trimmedItem == &a && list->size == 0 && list->head == NULL && list->tail == NULL && list->curr == NULL, "trims only remaining element & resets list properties");
        }
        else if(i == 3){ // trimming again after the list is empty
            mockAssert(trimmedItem == NULL, "returns NULL when trimming an empty list");
        }
    }

    List_free(list, testFree);
}

void test_list_concat(){
    printf("\ntesting List_concat()\n");

    List* list1 = List_create();
    List* list2 = List_create();
    int a = 1;
    int b = 5;
    int c = 3;
    int *arr1[2] = {&a, &b};
    int *arr2[1] = {&c};

    // fill list 1
    for (int i = 0; i < 2; i++) {
        List_append(list1, arr1[i]);
    }
    // fill list 2
    for (int i = 0; i < 1; i++) {
        List_append(list2, arr2[i]);
    }

    // concatenating two non-empty lists
    List_concat(list1, list2);
    mockAssert(list1->size == 3 && list1->tail->item == &c, "concatenates two filled lists");

    // concatenating with first list empty
    list1 = List_create();
    list2 = List_create();

    List_append(list2, &c);
    List_concat(list1, list2);
    mockAssert(list1->size == 1 && list1->tail->item == &c, "concatenates when first list is empty");

    // concatenating with second list empty
    list1 = List_create();
    list2 = List_create();
    for (int i = 0; i < 2; i++) {
        List_append(list1, arr1[i]);
    }

    List_concat(list1, list2);
    mockAssert(list1->size == 2 && list1->tail->item == &b, "concatenates when second list is empty");

    // concatenating two empty lists
    list1 = List_create();
    list2 = List_create();

    List_concat(list1, list2);
    mockAssert(list1->size == 0 && list1->head == NULL && list1->tail == NULL, "handles concatenating two empty lists");

    List_free(list1, testFree);
    List_free(list2, testFree);
}

static int itemsFreedCounter = 0;
// increments itemsFreedCounter 
void testItemFreeCount(void* pItem) {
    itemsFreedCounter++;
}
void test_list_free() {
    printf("\ntesting List_free()\n");
    
    List* list = List_create();
    int a = 1;
    int b = 2; 
    int c = 3;
    int *arr[3] = {&a, &b, &c};
    for (int i = 0; i < 3; i++) {
        List_append(list, arr[i]);
    }

    // freeing a non-empty list;
    List_free(list, testItemFreeCount);
    mockAssert(itemsFreedCounter == 3, "frees all items from non-empty list (3 items freed)");

    // freeing an empty list
    List* testList2 = List_create();
    itemsFreedCounter = 0; 
    List_free(testList2, testItemFreeCount);
    mockAssert(itemsFreedCounter == 0, "handles freeing an empty list without freeing any items");
}

// test_list_search helper
bool testComparator(void* item1, void* item2) {
    return (*(int*)item1) == (*(int*)item2);
}
void test_list_search() {
    printf("\ntesting List_search()\n");

    List* testList = List_create();
    int a = 1; 
    int b = 2;
    int c = 3;

    List_prepend(testList, &a);
    List_prepend(testList, &b);
    List_prepend(testList, &c);

    // assuming that the current is the head.
    int targetItem = 2;
    void* foundItem = List_search(testList, testComparator, &targetItem);
    mockAssert(foundItem == &b, "finds item 2 in list");

    // with an empty list.
    List* emptyList = List_create();
    foundItem = List_search(emptyList, testComparator, &targetItem);
    mockAssert(foundItem == NULL, "does not find item in empty list");

    // when no match is found.
    int searchForMissing = 99;
    foundItem = List_search(testList, testComparator, &searchForMissing);
    mockAssert(foundItem == NULL && testList->listStatus == LIST_OOB_END, "returns NULL & sets status to LIST_OOB_END when no match found");

    // when the curr pointer is before the start of the list.
    testList->curr = NULL; 
    testList->listStatus = LIST_OOB_START;
    targetItem = 3;
    foundItem = List_search(testList, testComparator, &targetItem);
    mockAssert(foundItem == &c, "finds item 3 in the list even if curr pointer was before the start");

    // when item is in list but the curr pointer is already past it.
    List_append(testList,&c);
    targetItem = 2;
    foundItem = List_search(testList, testComparator, &targetItem);
    mockAssert(foundItem == NULL && testList->listStatus == LIST_OOB_END,"returns NULL & sets status to LIST_OOB_END if the curr pointer is past the target item");

    List_free(testList, testFree);
}

int main(){
    //test List_Create
    int numberOfHeads = 0, numberOfNodes = 0;
    test_create_list(&numberOfHeads, &numberOfNodes);
    printf("==========================================");
    
    // simple functions
    test_list_count();
    printf("==========================================");
    test_list_first();
    printf("==========================================");
    test_list_last();
    printf("==========================================");
    test_list_next();
    printf("==========================================");
    test_list_prev();
    printf("==========================================");
    test_list_curr();
    printf("==========================================");

    // various inserts
    test_list_insert_after();
    printf("==========================================");
    test_list_insert_before();
    printf("==========================================");

    // node list testing
    test_List_append();
    printf("==========================================");
    test_List_prepend();
    printf("==========================================");

    // remove functions
    test_list_remove();
    printf("==========================================");
    test_list_trim();
    printf("==========================================");

    // complex functions
    test_list_concat();
    printf("==========================================");
    test_list_free();
    printf("==========================================");
    test_list_search();

    return 0;
}