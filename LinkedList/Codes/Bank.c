#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    int thousands;
    int fivehundreds;
    int onehundreds;
}Bill;

typedef struct{
    int id;
    char brand[20];
    char location[20];
    Bill bills;
    int balance;
}Bank;

typedef struct{
    int id;
    char fname[20];
    int balance;
}User;

typedef struct{
    int count;
    int max;
    Bank name;
    User *user;
}BankList;

typedef struct node{
    BankList bank;
    struct node *next;
}Node;

//ACT
bool withdraw(Node *x, int userId, int withdraw);
bool transferUserSorted(Node *x, int userId, int bankID);
bool sendMoney(Node *x, int userIdFrom, int userIdTo, int transferMoney);
bool transferAllUser(Node *x, int frombank, int tobank);
//ACT

void displayUser(Node *x);
bool registerUser(Node *x, int id, User user);
User inputuser(int id, char name[], int balance);
void displaybank(Node *x);
void populateNode(Node **x, BankList bank);
BankList populateBank(Bank name);
Bank bankname(int id, char brand[], char location[], int bal);
    
int main(){
    Node *x = NULL;

    populateNode(&x,populateBank(bankname(101,"MetroBank","Mandaue",45000)));
    populateNode(&x,populateBank(bankname(105,"ChinaBank","Banilad",45000)));
    populateNode(&x,populateBank(bankname(106,"LandBank","Cebu",45000)));
    populateNode(&x,populateBank(bankname(205,"BdoBANK","Consolacion",45000)));

    registerUser(x,101, inputuser(123,"Kenny", 5000));
    registerUser(x,101, inputuser(124,"Kentward", 4000));
    registerUser(x,101, inputuser(125,"Marlou", 12000));
    registerUser(x,105, inputuser(126,"Marlon", 3000));
    registerUser(x,105, inputuser(127,"Ermac", 9700));
    registerUser(x,106, inputuser(128,"Joe", 15000));
    registerUser(x,106, inputuser(129,"Harry", 7500));
    registerUser(x,106, inputuser(130,"Luke", 1000));
    registerUser(x,106, inputuser(131,"John", 25000));
    registerUser(x,205, inputuser(132,"Ziryll", 33000));
    registerUser(x,205, inputuser(133,"Majarocon", 700));
    registerUser(x,205, inputuser(134,"Paolo", 20000));
    registerUser(x,205, inputuser(136,"Nazzar", 35000));
    registerUser(x,205, inputuser(137,"Lopez", 55000));

    int id, id1, money;
    int choice;
    do{
        displaybank(x);
        displayUser(x);
        printf("=========================\n\n");
        printf("1. Send Money\n2. Transfer User to Another Bank\n3. Withdraw Money\n4. Register User\n5. Transfer All User");
        printf("\nEnter Choice: ");
        scanf("%d",&choice);

        //pag imo2 nlang og input ari
        switch(choice){
            case 1:
                printf("\nEnter Sender ID: ");
                scanf("%d",&id);
                printf("\nEnter Receiver ID: ");
                scanf("%d",&id1);
                printf("\nEnter Amount: ");
                scanf("%d",&money);
                if(!sendMoney(x, id, id1, money)){
                    printf("Account Not Found or Insufficient Amount\n\n");
                }else{
                    printf("Sent Successfully!\n\n");
                }
                break;
            case 2:
                printf("\nEnter User ID to transfer: ");
                scanf("%d",&id);
                printf("\nEnter Bank ID to transfer: ");
                scanf("%d",&id1);
                if(!transferUserSorted(x, id, id1)){
                    printf("Transfer Error\n\n");
                }else{
                    printf("Transfer Successfully!\n\n");
                }
                //bool transferUserSorted(Node *x, int userId, int bankID);//
                break;
            case 3:
                printf("\nEnter User ID to Withdraw: ");
                scanf("%d",&id);
                printf("\nEnter amount to withdraw: ");
                scanf("%d",&money);
                if(!withdraw(x, id, money)){
                    printf("Withdraw Error\n\n");
                }else{
                    printf("Withdraw Successfully!\n\n");
                }
                break;
            case 4:
                //bool registerUser(Node *x, int id, User user);//
                break;
            case 5:
                printf("\nEnter Bank ID to Transfer Users: ");
                scanf("%d",&id);
                printf("\nEnter Bank ID to Transfer Location: ");
                scanf("%d",&id1);
                if(!transferAllUser(x, id, id1)){
                    printf("Withdraw Error\n\n");
                }else{
                    printf("Withdraw Successfully!\n\n");
                }
                // bool transferAllUser(Node *x, int frombank, int tobank);
                break;
        }

        printf("\n=============================\n\n");
    }while(choice);
}

Bank bankname(int id, char brand[], char location[], int bal){
    Bank x;
    x.id = id;
    strcpy(x.brand, brand);
    strcpy(x.location, location);
    x.balance = bal;
    x.bills = (Bill){20, 30, 100};
    return x;
}

BankList populateBank(Bank name){
    BankList x;
    x.name = name;
    x.count = 0;
    x.max = 5;
    x.user = malloc(sizeof(User) * x.max);
    return x;
}

void populateNode(Node **x, BankList bank){
    Node *temp = malloc(sizeof(Node));
    temp->bank = bank;
    temp->next = *x;
    *x = temp;
}

void displaybank(Node *x){
    printf("Banks Available:\n");
    printf("ID\tName\tLocation\tBalance\t\tBills\n\n");
    while(x != NULL){
        printf("%-3d - %-10s - %-12s - %-10d - Thousands: %-5d - FiveHundreds: %-5d - Hundreds: %-5d\n",x->bank.name.id,x->bank.name.brand,x->bank.name.location,
                               x->bank.name.balance,x->bank.name.bills.thousands, x->bank.name.bills.fivehundreds,x->bank.name.bills.onehundreds);
        x = x->next;
    }
    printf("\n");
}


User inputuser(int id, char name[], int balance){
    User x;
    x.id = id;
    strcpy(x.fname, name);
    x.balance = balance;

    return x;
}

bool registerUser(Node *x, int id, User user){
    
    while(x != NULL){
        if(x->bank.name.id == id){
            if(x->bank.count == x->bank.max){
                x->bank.user = realloc(x->bank.user, ++x->bank.max * sizeof(User)); //Increase dynamic size if user is full
            }
            x->bank.user[x->bank.count++] = user;
            return true;   
        }
        x = x->next;
    }
    return false;
}

void displayUser(Node *x){
    while(x != NULL){
        printf("%s Users(%d/%d):\n",x->bank.name.brand, x->bank.count, x->bank.max);
        for(int i = 0; i < x->bank.count; i++){
            printf("%d - %s - %d\n",x->bank.user[i].id,x->bank.user[i].fname, x->bank.user[i].balance);
        }
        printf("\n");
        x = x->next;
    }
}

// Create a bool function to transfer user balance/send money to another user when its in the same bank 
// deduct/add the balance of the user
//(return true if transfer successful, false if user dont exist / if sender balance exceeds)
bool sendMoney(Node *x, int userIdFrom, int userIdTo, int transferMoney){
    int i, j;
    while(x != NULL){
        for(i = 0; i < x->bank.count && x->bank.user[i].id != userIdFrom; i++){}
        for(j = 0; j < x->bank.count && x->bank.user[j].id != userIdTo; j++){}
        if(i == x->bank.count || j == x->bank.count){
            x = x->next;
        }else{
            if(x->bank.user[i].balance - transferMoney < 0){
                return false;
            }else{
                x->bank.user[j].balance += transferMoney;
                x->bank.user[i].balance -= transferMoney;
                return true;
            }
        }
    }
    return false;
}

// Create a bool function that transfers a user in sorted (by id) from a bank to another bank 
// if count and max is the same....decrease max, count and realloc
//(return true if transfer successful, false if bank dont exist or user alrdy exist in the bank)
bool transferUserSorted(Node *x, int userId, int bankID){
    int i;
    Node *trav = x;
    while(x != NULL){
        for(i = 0; i < x->bank.count; i++){
            if(x->bank.user[i].id == userId && x->bank.name.id != bankID){
                while(trav != NULL){
                    if(trav->bank.name.id == bankID){
                        if(trav->bank.count == trav->bank.max){
                            trav->bank.user = realloc(trav->bank.user, ++trav->bank.max * sizeof(User));
                        }
                        int z;
                        for(z = 0; z < trav->bank.count; z++){
                            if(trav->bank.user[z].id > x->bank.user[i].id){
                                memmove(&trav->bank.user[z+1], &trav->bank.user[z], (trav->bank.count - z) * sizeof(User));
                                trav->bank.user[z] = x->bank.user[i];
                                trav->bank.count++;
                                break;
                            }
                        }
                        if(z == trav->bank.count){
                            trav->bank.user[z] = x->bank.user[i];
                            trav->bank.count++;
                        }
                        memmove(&x->bank.user[i], &x->bank.user[i+1], (x->bank.count - i) * sizeof(User));

                        if(x->bank.max > 5){
                            x->bank.count--;
                            x->bank.user = realloc(x->bank.user, --x->bank.max * sizeof(User));
                        }else{
                            x->bank.count--;
                        }
                        return true;
                    }else{
                        trav = trav->next;
                    }
                }
            }
        }
        x = x->next;
    }
    return false;
}

// Create a bool function that lets user withdraw from the bank if divisible by 100, deduct balance and bills on both(Bank and user), 
//(return true if withdrawal dont exceed the balance of bank, false if otherwise)
bool withdraw(Node *x, int userId, int withdraw){
    while(x != NULL){
        for(int i = 0; i < x->bank.count; i++){
            if(x->bank.user[i].id == userId){
                if(x->bank.user[i].balance - withdraw < 0 || x->bank.name.balance - withdraw < 0){
                    return false;
                }else{
                    x->bank.user[i].balance -= withdraw;
                    x->bank.name.balance -= withdraw;
                    
                    if(withdraw < 1000){
                            withdraw /= 100;
                            if(withdraw >= 5){
                                x->bank.name.bills.fivehundreds -=1;
                                withdraw -= 5;
                            }
                            x->bank.name.bills.onehundreds -= withdraw;
                            return true;
                    }

                    int thou = withdraw / 1000;
                    withdraw -= (thou * 1000);
                    if(thou - x->bank.name.bills.thousands > 0){
                        thou -= x->bank.name.bills.thousands;
                        x->bank.name.bills.thousands = 0;
                        thou *= 2; //cause we will use it in the fivehundeds
                        withdraw -= (thou * 500);
                        if(thou - x->bank.name.bills.fivehundreds > 0){
                            thou -= x->bank.name.bills.fivehundreds;
                            x->bank.name.bills.fivehundreds = 0;
                            thou *= 5;
                            x->bank.name.bills.onehundreds -= thou;
                            return true;
                        }else{
                            if(withdraw > 0){
                                withdraw /= 100;
                                x->bank.name.bills.onehundreds -= withdraw;
                                return true;
                            }
                        }
                    }else{
                        x->bank.name.bills.thousands -= thou;
                        if(withdraw > 0){
                            withdraw /= 100;
                            if(withdraw >= 5){
                                x->bank.name.bills.fivehundreds -=1;
                                withdraw -= 5;
                            }
                            x->bank.name.bills.onehundreds -= withdraw;
                            return true;
                        }
                    }
                }
            }
        }
        x = x->next;
    }
    return false;
}

// transfer all users to another bank
//use memcpy
bool transferAllUser(Node *x, int frombank, int tobank){ 
    Node *y = x;

    for(x; x != NULL && x->bank.name.id != frombank; x = x->next){}
    for(y; y != NULL && y->bank.name.id != tobank; y = y->next){}

    if(x != NULL && y != NULL){
        int cunt = y->bank.count;
        y->bank.count += x->bank.count;
        if(y->bank.count > y->bank.max){
            y->bank.max = y->bank.count;
            y->bank.user = realloc(y->bank.user, y->bank.max * sizeof(User));
        }
        memcpy(&y->bank.user[cunt], x->bank.user, x->bank.count * sizeof(User));
        x->bank.count = 0;
        return true;
    }

    return false;
}
