/* Instructions:
	The University of San Carlos has begun rolling out its newest locker technology: GraviLockers.
	These lockers are capable of fitting any amount of items, for as long as the total weight of all items
	does not exceed the weight limit of 5 KG. However, during shipping, the lockers' disk drives were damaged,
	and the firmware that made them work was lost. Luckily, the documentation for the structures remained intact.
	
	As students of DCIS, USC needs your help. Write the codes for the functions to make the lockers work again.
	Use the structures defined below.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLOCKERS 10
#define WEIGHTLIMIT 5

typedef struct{
	char studID[9];		
	char studName[65];  
	char course[5];		
}Student;

typedef struct{
	char itemName[33];	
	float weight;		/* Weight of the item to be stored */	
}ItemDets;

typedef struct ItemNode{
	ItemDets item;
	struct ItemNode* nextItem;
}ItemNode, *ItemList;

typedef struct{
	Student owner;			/* Details of the student who owns the locker */
	ItemList IL;			/* Linked list representation of all the items inside a certain locker */
	int lockerStat; 	 	/* 0 if locker is Vacant, 1 if occupied */
	float totWeight;		/* Total weight of all items in the locker */
}Locker;

typedef struct{
    Locker *locker;
    int count;
    int max;
}lockerlist;

/* Function depositItem(): This function will receive as parameter a Locker, a student ID, and an item to be
stored. The function will insert the item into the Locker's ItemList, which is sorted by weight. Heavier
items are stored at the end of the locker's ItemList. Before insertion, please make sure that the student ID
passed is the same as the student ID of the locker's owner. Also, make sure that the weight of all items,
including the new item to store, does not exceed the weight limit. */

Student students(char studID[], char studName[], char course[]){
    Student studs;
    strcpy(studs.studID, studID);
    strcpy(studs.studName, studName);
    strcpy(studs.course, course);

    return studs;
}

Locker inputlockers(Student stud, int lockerStat, float totWeight){
    Locker myLock;

    myLock.owner = stud;
    myLock.lockerStat = lockerStat;
    myLock.totWeight = totWeight;
    myLock.IL = NULL;

    return myLock;
}

void populateLocker(lockerlist *myLocker, Locker lock){

    myLocker->locker[myLocker->count++] = lock;
}

void depositItem(lockerlist* L, char studID[], ItemDets newItem)
{
	for(int i = 0; i < L->count; i++){
        if(strcmp(L->locker[i].owner.studID, studID) == 0 && L->locker[i].totWeight + newItem.weight < WEIGHTLIMIT){
            ItemList temp = malloc(sizeof(ItemNode));
            temp->item = newItem;

            ItemList *trav = &L->locker[i].IL;
            for(trav; *trav != NULL && (*trav)->item.weight < newItem.weight; trav = &(*trav)->nextItem){}
            temp->nextItem = *trav;
            *trav = temp;
            L->locker[i].totWeight += newItem.weight;
            break;
        }
    }
}

Student *getStudent(lockerlist L, float limit){
    Student *stud = malloc(sizeof(Student) * L.count);
    int j = 0;
    for(int i = 0; i < L.count; i++){
        if(L.locker[i].totWeight > limit){
            stud[j++] = L.locker[i].owner;
        }
    }
    strcpy(stud[j].studName, "");
    
    return stud;
}

/* Function getHeavyItems(): This function will receive as parameter a Locker and a weight threshold/limit.
The function will go through all the items in the passed Locker's ItemList. If any item EXCEEDS the passed
threshold/limit, store that item into a new ItemList using insertFirst, and delete it from the locker's 
ItemList. Return the ItemList of deleted items to the calling function. */


ItemList getHeavyItems(lockerlist* L, float limit)
{	
	ItemList ret = NULL;
    for(int i = 0; i < L->count; i++){
        ItemNode **trav = &L->locker[i].IL;
        while(*trav != NULL){
            if((*trav)->item.weight > limit){
                ItemList temp = *trav;
                *trav = (*trav)->nextItem;
                temp->nextItem = ret;
                ret = temp;
            }else{
                trav = &(*trav)->nextItem;
            }
        }
    }
	
	return ret;
}

void displayStud(Student *s){
    
    printf("Students who has items that exceeds the limit:\n");
    for(int i = 0; strcmp(s[i].studName, "") != 0; i++){
        printf("%s - %s - %s\n",s[i].studID, s[i].studName, s[i].course);
    }
}

void displayItemList(ItemList L)
{
	ItemList trav;
	float totWeight = 0;
	
	for(trav = L; trav != NULL; trav = trav->nextItem){
		printf("Item: %-15s | Weight: %-15.2f\n", trav->item.itemName, trav->item.weight);
		totWeight += trav->item.weight;
	}
	printf("\nTotal Weight: %.2fkg\n\n", totWeight);
}

int main(void)
{
	ItemDets item1 = {"Prog 1 Book", 0.35};
	ItemDets item2 = {"Shoes", 0.87};
	ItemDets item3 = {"Laptop", 2.35};
	ItemDets item4 = {"Keyboard", 1.17};
	ItemDets item5 = {"Keybd", 1.37};
	
  lockerlist myLocker;
  myLocker.count = 0;
  myLocker.max = 5;
  myLocker.locker = malloc(sizeof(Locker) * myLocker.max);

  populateLocker(&myLocker, inputlockers(students("14101941", "Cris Militante", "BSCS"), 1, 0));
  populateLocker(&myLocker, inputlockers(students("123", "Jungcook", "BSCS"), 1, 0));
  populateLocker(&myLocker, inputlockers(students("1234", "King Baldwin", "BSIS"), 1, 0));
  populateLocker(&myLocker, inputlockers(students("12345", "Romeo Juliet", "BSIT"), 1, 0));

	ItemList heavyItems = NULL;
	
	depositItem(&myLocker, "14101941", item5);
	depositItem(&myLocker, "14101941", item4);
	depositItem(&myLocker, "123", item2);
	depositItem(&myLocker, "123", item3);
	depositItem(&myLocker, "1234", item1);
  depositItem(&myLocker, "1234", item3);
  depositItem(&myLocker, "12345", item4);
  depositItem(&myLocker, "12345", item2);
	
	for(int i = 0; i < myLocker.count; i++){
        printf("(%s's Locker:)\n",myLocker.locker[i].owner.studName);
        displayItemList(myLocker.locker[i].IL);   
	}
	
  Student *studs = getStudent(myLocker, 2.6);

  displayStud(studs);
  printf("\n\n==========\n\n");
	heavyItems = getHeavyItems(&myLocker, 1.00);
	
	printf("\n\n====After deleted====\n");
	for(int i = 0; i < myLocker.count; i++){
        printf("(%s's Locker:)\n",myLocker.locker[i].owner.studName);
        displayItemList(myLocker.locker[i].IL);   
	}
	printf("====HeavyItems====\n");
	displayItemList(heavyItems);

	return 0;
}
