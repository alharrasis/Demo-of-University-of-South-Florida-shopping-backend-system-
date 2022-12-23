/*
Project 8 - Program Design
Name: Shahad Abdullah Al Harrasi 
In this program, we can see a prototype for online store, to sell t-shirts from its student organizations.
This can enter the information about the available t-shirt into the inventory with the following information,
1. Student organization name
2. Size
3. Price
4. Quantity
In addition, it has the following functions,
1. Functions to search t-shirts by its student organization name and its size.
2. Functions to print and clear inventory.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
//////////////////////
// data definitions //
//////////////////////

#define ORG_NAME_LEN 50
#define SIZE_LEN 3

struct tshirt {
    char org_name[ORG_NAME_LEN+1];
    char size[SIZE_LEN+1];
    double price;
    int quantity;
    struct tshirt *next;
};

/////////////////////////
// function prototypes //
/////////////////////////

struct tshirt * add_to_inventory(struct tshirt *inventory);
void search_by_organization(struct tshirt *inventory);
void search_by_size(struct tshirt *inventory);
void print_inventory(struct tshirt *inventory);
void clear_inventory(struct tshirt *inventory);
int read_line(char str[], int n);
void help();

/**********************************************************
 * main: Prompts the user to enter an operation code,     *
 *       then calls a function to perform the requested   *
 *       action. Repeats until the user enters the        *
 *       command 'q'. Prints an error message if the user *
 *       enters an illegal code.                          *
 **********************************************************/
int main() {
    char code;
    struct tshirt *inventory = NULL;

    help();
    printf("\n");

    for (;;) {
        // read operation code
        printf("Enter operation code: ");
        scanf(" %c", &code);
        while(getchar() != '\n') /* skips to end of line */
            ;

        // run operation
        switch (code) {
            case 'a':
                inventory = add_to_inventory(inventory);
                break;
            case 'h':
                help();
                break;
            case 'o':
                search_by_organization(inventory);
                break;
            case 's':
                search_by_size(inventory);
                break;
            case 'p':
                print_inventory(inventory);
                break;
            case 'q':
                clear_inventory(inventory);
                return 0;
				break;
            default:
                printf("Illegal operation code!\n");
        }
        printf("\n");
    }
}

//////////////////////////
// function definitions //
//////////////////////////

void help() {
    printf("List of operation codes:\n");
    printf("\t'a' for adding a t-shirt to the inventory;\n");
    printf("\t'h' for help;\n");
    printf("\t'o' for searching t-shirts by organization;\n");
    printf("\t's' for searching t-shirts by size;\n");
    printf("\t'p' for printing the inventory;\n");
    printf("\t'q' for quit.\n");
}

/*
In this function, first ask the user to enter the student organization name and the size.
Then check if the inventory has a t-shirt for this organization with this specific size. 
If yes, it prints a message stating that this t-shirt already exists and exit the function. 
Else, ask the user to enter the price and the quantity, allocate memory for a new t-shirt and save the entered
information.
Finally, add it to the end of the linked list, and then exit the function.
*/

struct tshirt * add_to_inventory(struct tshirt *inventory) {

	char org_name[50] = "";
	char size[3] = "";
	
	printf("Enter student organization name: ");
	read_line(org_name,50);
	printf("Enter t-shirt size: ");
    scanf("%s", size);
		
	struct tshirt *current = inventory; 
	while (current != NULL)
	{
		if (strcmp(current -> org_name,org_name) == 0 && strcmp(current -> size, size) == 0)
		{
			printf("T-shirt already exists in the inventory!\n");
			return inventory;
		}
		current = current -> next;
	}
	
	struct tshirt *temp,*ptr;
	
	temp=(struct tshirt *)malloc(sizeof(struct tshirt));
	
	if(temp==NULL)
		printf("\nOut of Memory Space:\n");

	strcpy(temp->org_name,org_name);
	strcpy(temp->size,size);
		
	printf("Enter price: ");
	scanf("%lf", &temp->price);
	printf("Enter quantity: ");
	scanf("%d", &temp->quantity);

	temp->next =NULL;

	if(inventory==NULL)
        inventory=temp;
	else
	{
		ptr=inventory;
		while(ptr->next !=NULL)
			ptr=ptr->next;
        ptr->next =temp;
	}
		
	return inventory;

}

/*
In this function search t-shirt by a student organization name. 
For that first ask the user to enter the name of the organization and then find all t-shirts on inventory for this organization. 
Finally, Display organization name, size, price and quantity.
*/
void search_by_organization(struct tshirt *inventory) {
	
	char org_name[50] = "";
	printf("Enter student organization name: ");
	read_line(org_name,50);
	
	struct tshirt *current = inventory;
	struct tshirt *newList = NULL;
	struct tshirt *tail = NULL;
	
    while (current != NULL)
    {
        if (strcmp(current->org_name,org_name) == 0){
			if (newList == NULL)
			{
				newList = (struct tshirt*)malloc(sizeof(struct tshirt));
				strcpy(newList->org_name, current->org_name);
				strcpy(newList->size, current->size);
				newList->price = current->price;
				newList->quantity = current->quantity;
				newList->next = NULL;
				tail = newList;
			}
			else {
				tail->next = (struct tshirt*)malloc(sizeof(struct tshirt));
				tail = tail->next;
				strcpy(tail->org_name, current->org_name);
				strcpy(tail->size, current->size);
				tail->price = current->price;
				tail->quantity = current->quantity;
				tail->next = NULL;
			}
		}
        current = current->next;
    }
	
    if(newList != NULL){
		print_inventory(newList);
		free(newList);
		free(tail->next);
	}
	else
		printf("No t-shirt found!\n");

}

/*
In this function search t-shirt by t-shirt size. 
For that first ask the user to enter the desired size and then find all t-shirts on inventory for this size. 
Finally, Display organization name, size, price and quantity.
*/
void search_by_size(struct tshirt *inventory) {
	char size[3] = "";
	
	printf("Enter t-shirt size: ");
	scanf("%s", size);

	struct tshirt *current = inventory;  
	struct tshirt *newList = NULL;
	struct tshirt *tail = NULL;
	
    while (current != NULL)
    {
        if (strcmp(current->size,size) == 0){
			if (newList == NULL)
			{
				newList = (struct tshirt*)malloc(sizeof(struct tshirt));
				strcpy(newList->org_name, current->org_name);
				strcpy(newList->size, current->size);
				newList->price = current->price;
				newList->quantity = current->quantity;
				newList->next = NULL;
				tail = newList;
			}
			else {
				tail->next = (struct tshirt*)malloc(sizeof(struct tshirt));
				tail = tail->next;
				strcpy(tail->org_name, current->org_name);
				strcpy(tail->size, current->size);
				tail->price = current->price;
				tail->quantity = current->quantity;
				tail->next = NULL;
			}
		}
        current = current->next;
    }
	
    if(newList != NULL){
		print_inventory(newList);
		free(newList);
		free(tail->next);
	}
	else
		printf("No t-shirt found!\n");
}

/*
In this function print organization name, size, price and quantity for all t-shirts on inventory.
*/
void print_inventory(struct tshirt *inventory) {

    if (inventory != NULL) {
		struct tshirt *current_node = inventory;
		printf("|----------------------------------------------------|-----|-------|------|\n");
		printf("| Student organization                               | Sz. | Price | Qty. |\n");
		printf("|----------------------------------------------------|-----|-------|------|\n");
		while ( current_node != NULL) {
			printf("| %-50s | %-3s | %5.2f | %4d |\n", current_node ->org_name, current_node ->size, current_node ->price, current_node ->quantity);
			current_node = current_node->next;
		}
		printf("|----------------------------------------------------|-----|-------|------|\n");
    }
	else
		printf("No t-shirt found!\n");
}

/*
In this function deallocate all the memory used for the linked list, when the user exits the program.
*/
void clear_inventory(struct tshirt *inventory) {
		
		struct tshirt *temp,*ptr;

        if(inventory != NULL)
		{
			while (inventory != NULL)
			{
				if(inventory->next ==NULL)
				{
					free(inventory);
					inventory =NULL;
				}
				else
				{
					ptr=inventory;
					while(ptr->next!=NULL)
					{
							temp=ptr;
							ptr=ptr->next;
					}
					temp->next=NULL;
					free(ptr);
				}
			}
		}
	
}

/*
Function to read the name of the student organization
*/
int read_line(char str[], int n) {
    int ch, i=0;

    while (isspace(ch = getchar()))
        ;
    str[i++] = ch;
    while ((ch = getchar()) != '\n') {
        if (i < n)
            str[i++] = ch;    
    }
    str[i] = '\0';
    return i;
}



