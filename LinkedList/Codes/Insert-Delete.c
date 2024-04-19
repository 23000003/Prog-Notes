#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int val;
    struct node *next;
}NodeType;

void display(NodeType *node);
void CreateNode(NodeType **list, int value);
void insertRear(NodeType **list, int value);
void insertFront(NodeType **list, int value);
void insertSorted(NodeType **list, int value);
void insertIndex(NodeType **list, int value);
void deleteItem(NodeType **list);
void deleteIndex(NodeType **list);
void deleteRear(NodeType **list);
void deleteFront(NodeType **list);
void deleteall(NodeType **node);
void sortList(NodeType *list);

int main(){
    NodeType *node = NULL;
    int val;

    int choice;
    do{
        printf("1: Insert Rear\n2: Insert Front\n3: Insert Certain Index\n4: Insert Sorted\n");
        printf("5: Delete Rear\n6: Delete Front\n7: Delete Certain Index\n8: Delete Item\n");
        printf("9: Sort in Ascending\n10: Delete All\nEnter your Choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                printf("\nEnter number to Insert Rear: ");
                scanf("%d",&val);
                insertRear(&node, val);
                display(node);
                break;
            case 2:
                printf("\nEnter number to Insert Front: ");
                scanf("%d",&val);
                insertFront(&node, val);
                display(node);
                break;
            case 3:
                printf("\nEnter number to Insert at Certain Node Index: ");
                scanf("%d",&val);
                insertIndex(&node, val);
                display(node);
                break;
            case 4:
                printf("\nEnter number to Insert at Sorted Node: ");
                scanf("%d",&val);
                insertSorted(&node, val);
                display(node);
                break;
            case 5:
                deleteRear(&node);
                display(node);
                break;
            case 6:
                deleteFront(&node);
                display(node);
                break;
            case 7:
                deleteIndex(&node);
                display(node);
                break;
            case 8:
                deleteItem(&node);
                display(node);
                break;
            case 9:
                sortList(node);
                display(node);
                break;
            case 10:
                deleteall(&node);
                display(node);
                break;
            default:
                printf("\n\nAre you retarded?\n\n");
                break;
        }
    }while(choice);
                                
    display(node);
}

void CreateNode(NodeType **list, int value){ // Creates a Node and pass it to the main node which is List
    NodeType *init = malloc(sizeof(NodeType));
    init->val = value;
    init->next = NULL;
    *list = init;
}

void insertRear(NodeType **list, int value){

    NodeType **trav;
    for(trav = list; *trav != NULL; trav = &(*trav)->next){}
    CreateNode(trav, value);

}

void insertFront(NodeType **list, int value){

    NodeType *temp;
    CreateNode(&temp, value);
    temp->next = *list;
    *list = temp;

}

void insertSorted(NodeType **list, int value){
    
    NodeType **trav;
    for(trav = list; *trav != NULL && (*trav)->val< value; trav = &(*trav)->next){}
    NodeType *curr = *trav;
    CreateNode(trav,value);
    (*trav)->next = curr;    //trav (from the heap) will get the address of curr (holds the value node)
} 

void insertIndex(NodeType **list, int value){
    
    NodeType **trav;
    int i, j;
    printf("What Index would you want to insert the value?: ");
    scanf("%d",&j);

    for(i = 0, trav = list; *trav != NULL && i != j; trav = &(*trav)->next, i++){}
    NodeType *curr = *trav;
    CreateNode(trav,value);
    (*trav)->next = curr;

}

void deleteFront(NodeType **list){
    NodeType *delete = *list;

    *list = (*list)->next;
    free(delete);
}

void deleteRear(NodeType **list){
    NodeType **trav;

    for(trav = list; (*trav)->next != NULL; trav = &(*trav)->next){}
    NodeType *del = *trav;
    *trav = NULL; //Can be *trav = (*trav)->next as the last node is always NULL
    free(del);

}

void deleteIndex(NodeType **list){
    int ndx;

    printf("What index would you like to delete?: ");
    scanf("%d",&ndx);

    NodeType **trav, *del;
    int i;

    for(i = 0, trav = list; *trav != NULL && i < ndx; i++, trav = &(*trav)->next){}

    if(*trav != NULL){
        del = *trav;
        *trav = (*trav)->next;
        free(del);
    }else{
        printf("Your chosen index exceeds the node\n");
    }
}

void deleteItem(NodeType **list){
    int ndx;

    printf("What index would you like to delete?: ");
    scanf("%d",&ndx);

    NodeType **trav, *del;
    int i;

    for(trav = list; *trav != NULL && (*trav)->val != ndx; i++, trav = &(*trav)->next){}

    if(*trav != NULL){
        del = *trav;
        *trav = (*trav)->next;
        free(del);
    }else{
        printf("Your item is not found\n");
    }
}

void deleteall(NodeType **node){

    while(*node != NULL){
        NodeType *del = *node;
        *node = (*node)->next;
        free(del);
    }
}

void sortList(NodeType *list){
    NodeType *i;

    for(list; list != NULL; list = list->next){
        NodeType *temp = list;
        for(i = list->next; i != NULL; i = i->next){
            if(temp->val > i->val){
                temp = i;
            }
        }
        int swap = temp->val;
        temp->val = list->val;
        list->val = swap;
    }
}

void display(NodeType *node){
    printf("\n\n{");
    while(node != NULL){
        printf("%d",node->val);
        if(node->next != NULL){
            printf(", ");
        }
        node = node->next;
    }
    printf("}\n\n");
}