#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char String[20];

typedef struct {
    int day, month, year;    
} MyDate;

typedef struct {
    int id;
    String name;
    MyDate exp;
    float price;
} Product;

typedef struct node {
    Product prods;
	struct node *next;
} ProductList;

//Populating the Products
MyDate createDate(int day, int month, int year);
Product createProduct(int id, String name, MyDate exp, float price);
void populateProductList(ProductList **list, Product prods);

void addProductSorted(ProductList **list, Product p); // Add product on a sorted using date difference
ProductList *removeExpiredProducts(ProductList **list, MyDate exp); // Remove expired products and returns the removed products
void removeProduct(ProductList **list, int ndx); // Remove product in a certain index

// 3 helper functions to use in removeExpiredProducts function to determine product expiration
int isYear(int year, int year1);
int daysInMonth(int month, int day, int month1, int day1);
int dateDifference(MyDate d1, MyDate d2);

void displayProductList(ProductList *list);

void main() {
    ProductList *prod = NULL;
    
    populateProductList(&prod, createProduct(12, "Sardines", createDate(15, 7, 2027), 25)); // expired
    populateProductList(&prod, createProduct(123, "CornBeef", createDate(17, 5, 2027), 43)); // expired
    populateProductList(&prod, createProduct(1234, "Piatos", createDate(13, 4, 2026), 34));
    populateProductList(&prod, createProduct(12345, "Beefloaf", createDate(6, 5, 2025), 67));
    
    printf("Products Available:\n");
    displayProductList(prod);
    
    addProductSorted(&prod, createProduct(123456, "Chicken", createDate(15, 7, 2026), 25));
    addProductSorted(&prod, createProduct(1234566, "Buffalo", createDate(14, 7, 2026), 25)); // expired
    
    printf("Products Available:\n");
    displayProductList(prod);
    
    ProductList *expire = removeExpiredProducts(&prod, createDate(15, 7, 2026));
    
    printf("\nExpired Products:\n");
    displayProductList(expire);
    printf("\nProducts Available:\n");
    displayProductList(prod);
    
    removeProduct(&prod, 1);
    printf("\nProducts Available:\n");
    displayProductList(prod);
}

MyDate createDate(int day, int month, int year){
	MyDate x;
	x.day = day;
	x.month = month;
	x.year = year;
	return x;
}

Product createProduct(int id, String name, MyDate exp, float price){
	Product prod;
	prod.id = id;
	strcpy(prod.name, name);
	prod.price = price;
	prod.exp = exp;
	
	return prod;
}

void populateProductList(ProductList **list, Product prods){
	ProductList *temp = malloc(sizeof(ProductList));
	temp->next = *list;
	temp->prods = prods;
	*list = temp;
}
void displayProductList(ProductList *list){
	
	while(list != NULL){
		printf("%-10d - %-10s - %-10d - %-10d - %-10d - %-10.2f\n",list->prods.id, list->prods.name, list->prods.exp.day, 
							list->prods.exp.month, list->prods.exp.year,list->prods.price);
		list = list->next;
	}
}

int isYear(int year1, int year2){               //2027 5 17
	if(year1 == year2){
		return 1;
	}else if(year1 > year2){
		return 2;
	}else{
		return 3;
	}
}

int daysInMonth(int month, int day, int month1, int day1){
	if(month > month1){
		return 1;
	}else if(month < month1){
		return 2;
	}else{
		if(month == month1 && (day == day1 || day > day1)){
			return 1;
		}else{
			return 2;
		}	
	}
}

int dateDifference(MyDate d1, MyDate d2){
	if(isYear(d1.year, d2.year) == 1){
		if(daysInMonth(d1.month, d1.day, d2.month, d2.day) == 1){
			return 1;
		}else{
			return 2;
		}
	}else if(isYear(d1.year, d2.year) == 2){
		return 1;
	}else{
		return 2;
	}
}
// returns 1 if expire returns 2 if not expired
void addProductSorted(ProductList **list, Product p){  // Add product on a sorted using date difference
	ProductList **trav = list;
	
	for(trav; *trav != NULL && dateDifference((*trav)->prods.exp, p.exp) == 2; trav = &(*trav)->next){}
	ProductList *temp = malloc(sizeof(ProductList));
	temp->next = *trav;
	temp->prods = p;
	*trav = temp;
	
}
ProductList *removeExpiredProducts(ProductList **list, MyDate exp){ // Remove expired products and returns the removed products
	ProductList *expired = NULL;
	ProductList **trav = list;
	
	while(*trav != NULL){
		if(dateDifference((*trav)->prods.exp, exp) == 1){
			ProductList *temp = *trav;
			(*trav) = (*trav)->next;
			temp->next = expired;
			expired = temp;
		}else{
			trav = &(*trav)->next;
		}
	}
	
	return expired;
} 
void removeProduct(ProductList **list, int ndx){ // Remove product in a certain index
	ProductList **trav = list;
	int i;
	for(i = 0, trav; *trav != NULL && i < ndx; trav = &(*trav)->next, i++){}
	ProductList *del = *trav;
	(*trav) = (*trav)->next;
	free(del);
}
