
/* Created on 05/05/2019 by Fletcher van Ameringen */
// Enjoy!

#include <stdio.h>
#include <string.h>

void add();
void bubbleSort(int a);
char chooseOpt();
void del();
void edit();
void output();
void sort();
void sortAlpha();
void sortPrice();
void total();
char validFail();

char item[1000][50]; // can take 1000 products, each with a label less than 50 chars
float prices[1000];
int itemCount, i;


int main() {
	
	char choice;
	
	itemCount = 0;
	choice = 0;
	printf("\n\n*** Welcome To Fletcher's Shopping List! ***\n\n");
	while (choice != '4') {
		if (choice == '1') {
			edit();
		}
		if (choice == '2') {
			sort();
		}
		if (choice == '3') {
			output(); 
		}
    	choice = chooseOpt();
	}
	printf("\nThank you for using our list system!");
}

void output() { /* This function prints out the list */
	
	if (itemCount == 0) {
		printf("There are no items in your list yet!\n");
	} else {
	    printf("\n___________________________________");
		for (i = 0; i < itemCount; i++) {
			printf("\n|%2d. %15s costs $%7.2f |", i+1, item[i], prices[i]);
		}
		printf("\n");
		printf("___________________________________\n\n");
	}
}	
	
void edit() { /* This function handles the request of whether to add or delete an item */
	
    char tempChoice[10], choice;
    
	printf("Would you like to add an item (1), or delete an item (2)? ");
	scanf("%s", tempChoice);
	while ((strlen(tempChoice) > 1) || ((tempChoice[0] != '1') && (tempChoice[0] != '2'))) {
		tempChoice[0] = validFail();
	}
	choice = tempChoice[0];
	if (choice == '1') {
		add();
	} else if (choice == '2') {
		del();
	}
}

void add() { /* This function adds an item to the list */
	
	i = itemCount;
	printf("Please enter a product: ");
    	getchar();
	gets(item[i]); // <--

	printf("Please enter the price for that product: ");
	scanf("%f", &prices[i]); 
	itemCount++;
}

void del() { /* This function 'deletes' a list element (according to name) */
	
	int searchid;
	char search[10][50];
	
	printf("Please enter the product that you want to delete: ");
	scanf("%s", search[0]);
	searchid = -1;
	for (i = 0; i < itemCount; i++) {
		if (strcmp(item[i], search[0]) == 0) {
			searchid = i;
			
    		for (i = searchid; i < itemCount - 1; i++) {
    			strcpy(item[i], item[i+1]);
    			prices[i] = prices[i+1];
    		}
    		itemCount--;
    		printf("The product has been deleted.\n");
		}
	}
	if (searchid == -1) {
		printf("The product that you entered could not be found.\n");
	}
}

void sort() { /* This function handles the request of which method to use for sorting */
    
    char option, temp[10];
    
    printf("Would you like to sort according to name (1), or price (2)? Or would you like to see your receipt (3)? ");
    scanf("%s", temp);
	while ((strlen(temp) > 1) || ((temp[0] != '1') && (temp[0] != '2') && (temp[0] != '3'))) {
        temp[0] = validFail();
    }
    option = temp[0];
    if (option == '1') {
        sortAlpha();
    }
    if (option == '2') {
        sortPrice();
    }   
    if (option == '3') {
        total();
    }
}

void sortPrice() { /* This function sorts according to price (ascending) */
	
	int pass;
	for (pass = 0; pass < itemCount; pass++) {
		for (i = 0; i < itemCount-1; i++) {
			if (prices[i] > prices[i+1]) {
				bubbleSort(i);
			}
		}
	}
	printf("The list has been sorted according to price.\n");
}

void sortAlpha() { /* This function sorts according to alphabetical order (ascending) */
	
	int pass;
	
	for (pass = 0; pass < itemCount; pass++) {
		for (i = 0; i < itemCount-1; i++) {
			if (strcmp(item[i], item[i+1]) > 0) {
			    bubbleSort(i);
			}
		}
	}
	printf("The list has been sorted according to alphabetical order.\n");
}

void bubbleSort(int a) {  /* This function performs a bubble sort */

	char tempchar[1000][50];
	float tempfloat;

	// Sort Prices
	tempfloat = prices[a];
	prices[a] = prices[a+1];
	prices[a+1] = tempfloat;
	// Sort Products
	strcpy(tempchar[a], item[a]);
	strcpy(item[a], item[a+1]);
	strcpy(item[a+1], tempchar[a]);
}

void total() { /* This function calculates the total price of your list items, and the average price of an item */
	
   float sum, average;
	
	sum = 0;
    for (i = 0; i < itemCount; i++) {
        sum += prices[i];
    }
    average = sum / itemCount;
    printf("\nThe total of price your items (%d items) comes to: $%0.2f\n", itemCount, sum);
    printf("Your average item price is: $%0.2f\n\n", average);
}

char chooseOpt() {
    
    char tempChoice[10];
    
	printf("Would you like to edit the list (1), sort the list (2), print the list (3), or exit (4)? ");
	scanf("%s", tempChoice);
	while ((strlen(tempChoice) > 1) || ((tempChoice[0] != '1') && (tempChoice[0] != '2') && (tempChoice[0] != '3') && (tempChoice[0] != '4'))) {
		tempChoice[0] = validFail();
	}
	return tempChoice[0];	
}
char validFail() {
    char string[10];
    printf("Invalid entry, please enter again: ");
	scanf("%s", string);
	return string[0];
}
