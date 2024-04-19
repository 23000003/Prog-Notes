#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

typedef char String[MAX];

typedef struct{
    int id;
    String name;
    float price;
    int quantity;
    String supplier;
}item;

typedef struct node{
    item iteminvent;
    struct node *next;
}itemlist;

item inputstructs(int id, int quantity, float price, char name[], char supp[]);
void addtolinklist(itemlist **node, item items);
void additem(itemlist **node);
void display(item node);
void generateReport(itemlist *node);

int main(){
    itemlist *node = NULL, *trav = NULL;
    int choice, search;
    
    do{
        printf("Inventory Management System\n");
        printf("1. Add new item\n2. Search item by ID\n3. Display inventory\n4. Generate report\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                additem(&node);
                break;
            case 2:
                printf("Enter the ID of the item to search: ");
                scanf("%d",&search);
                for(trav = node; trav != NULL && trav->iteminvent.id != search; trav = trav->next){}
                if(trav == NULL){
                    printf("\nID is not found!\n\n");
                }else{
                    display(trav->iteminvent);
                }
                break;
            case 3:
                trav = node;
                printf("Current inventory:\n");
                while(trav != NULL){
                    display(trav->iteminvent);
                    trav = trav->next;
                }
                printf("\n");
                break;
            case 4:
                generateReport(node);
                break;
            case 5:
                printf("Exiting program.");
                break;
        }
    }while(choice != 5);
}

item inputstructs(int id, int quantity, float price, char name[], char supp[]){
    item x;

    x.id = id;
    x.quantity = quantity;
    x.price = price;
    strcpy(x.name, name);
    strcpy(x.supplier, supp);
    
    return x;
}
void addtolinklist(itemlist **node, item items){
    itemlist *temp = malloc(sizeof(itemlist));
    temp->next = NULL;
    temp->iteminvent = items;

    itemlist **trav;
    for(trav = node; *trav != NULL; trav = &(*trav)->next){}
    *trav = temp;
}

void additem(itemlist **node){

    int id, quantity;
    float price;
    char name[MAX], supplier[MAX];
    printf("Enter the ID of the item: ");
    scanf("%d",&id);
    printf("Enter the name of the item: ");
    scanf(" %s",name);
    printf("Enter the price of the item: ");
    scanf("%f",&price);
    printf("Enter the quantity of the item: ");
    scanf("%d",&quantity);
    printf("Enter the supplier of the item: ");
    scanf(" %s",supplier);

    addtolinklist(node,inputstructs(id,quantity,price,name,supplier));
    
    printf("Item added to inventory.\n\n");
}

void generateReport(itemlist *node){
    float sales = 0;
    int quan = 0;

    while(node != NULL){
        sales += node->iteminvent.price * node->iteminvent.quantity;
        quan += node->iteminvent.quantity;
        node = node->next;
    }

    printf("Total sales: $%.2f",sales);
    printf("\nTotal quantity: %d\n\n",quan);
}

void display(item node){
    
    printf("ID: %d\n",node.id);
    printf("Name: %s\n",node.name);
    printf("Price: %.2f\n",node.price);
    printf("Quantity: %d\n",node.quantity);
    printf("Supplier: %s\n\n",node.supplier);
    
}