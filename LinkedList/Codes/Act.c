#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int val;
    struct node *next;
}Node;

//delete all occurence
//(factor) return
// (factor) delete and return


//combining array list and (return) link list
void insertFront(Node **head, int val){
    Node *temp = malloc(sizeof(Node));
    temp->val = val;
    temp->next = *head;
    *head = temp;
}

void removeoccurence(Node **head, int occu){
    Node **temp = head;

    while(*temp != NULL){
        if((*temp)->val == occu){
            Node *del = *temp;
            *temp = del->next; //can be *temp = (*temp)->next
            free(del);
        }else{
            temp = &(*temp)->next;
        }
    }
}

Node *removefactor(Node *head, int factor){
    Node *occu = NULL, *fact = NULL;
    while(head != NULL){
        if(head->val % factor == 0){
            Node *temp = NULL;
            insertFront(&temp, head->val);       
            if(fact == NULL){
                fact = temp;
                occu = fact;
            }else{
                fact->next = temp;
                fact = fact->next;
            }
        }
        head = head->next;
    }
    return occu;
}

void deletenonfactors(Node **head, int fact){
    Node **trav = head;

    while(*trav != NULL){
        if((*trav)->val % fact == 0){
            Node *del = *trav;
            *trav = del->next; //can be *trav = (*trav)->next
            free(del);
        }else{
            trav = &(*trav)->next; 
        }
    }
}

void display(Node *trav){
    while(trav != NULL){
        printf("%d ", trav->val);
        trav = trav->next;
    }
    printf("\n");
}

int main(){
    Node *head = NULL;
    int array[7] = {7, 8, 7, 5, 4, 7, 1};

    for(int i = 0; i < 7; i++){
        insertFront(&head, array[i]);
    }
    display(head);
    
    removeoccurence(&head,7);
    display(head);
    
    Node *fact = removefactor(head, 2);
    display(fact);

    printf("\nBefore Deleted: \n");
    display(head);
    deletenonfactors(&head, 2);
    display(head);
}
