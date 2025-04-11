#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a book
typedef struct Building{
    int id;
    char *street;
    char *devCompany;
    int yearConstruction;
    int numHouse;
    int floors;
    float height;
    float energyEfficiency;
    int amountApartments;
    float *apartmentPrices;
}Building;

// Structure for a node in the linked list
typedef struct Node {
    Building building;
    struct Node* next;
}Node;

// Function to create a new node
Node* create_node(Building building) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    int success = (new_node != NULL);
    if(success){
        new_node->building = building;
        new_node->next = NULL;
    } 
    else{
        printf("Memory allocation error!\n");
    }
    return new_node;
}

// Function to append a book to the end of the list
void append(Node** head, Building building) {
    Node* new_node = create_node(building);
    Node* current = *head;
    if(*head == NULL){
        *head = new_node;
    }
    else{
        while(current->next != NULL){
            current = current->next;
        }
        current->next = new_node;
    }
}

// Function to calculate the length of the list
int length(Node* head){
    int count = 0;
    Node* current = head;
    while(current != NULL){
        count++;
        current = current->next;
    }
    return count;
}

// Function to remove an element by ID
void remove_from_end(Node** head, int id) {
    return;
}

// Function to print the list
void print_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("ID: %d\n", current->building.id);
        printf("Street: %s\n", current->building.street);
        printf("Developer Company: %s\n", current->building.devCompany);
        printf("Year Construction: %d\n", current->building.yearConstruction);
        printf("Floors: %d\n", current->building.floors);
        printf("Height: %.2f\n", current->building.height);
        printf("Energy Efficiency coeff: %.2f\n", current->building.energyEfficiency);
        printf("Apartments Price: ");
        for(int i=0; i<current->building.amountApartments; i++){
            printf("%.2f ", current->building.apartmentPrices[i]);
        }
        printf("\n\n");
        current = current->next;
    }
}

// Function to free the memory of the list
void free_list(Node* head){
    Node* current = head;
    Node* temp = NULL;
    while(current != NULL){
        temp = current;
        current = current->next;
        free(temp->building.street);
        free(temp->building.devCompany);
        free(temp->building.apartmentPrices);
        free(temp);
    }
}

// Function to read data from a CSV file
void read_from_csv(Node** head) {
    FILE* file = fopen("database.csv", "r");
    char line[1024];
    Building building;
    char* token;
    char* price_token;
    if(file){
        while(fgets(line, sizeof(line), file)){
            token = strtok(line, ",");

            building.id = atoi(token);

            building.street = (char*)malloc(strlen(token) + 1);
            token = strtok(NULL, ",");
            strcpy(building.street, token);

            token = strtok(NULL, ",");
            building.devCompany = (char*)malloc(strlen(token) + 1);
            strcpy(building.devCompany, token);

            building.yearConstruction = atoi(strtok(NULL, ","));
            building.numHouse = atoi(strtok(NULL, ","));
            building.floors = atoi(strtok(NULL, ","));
            building.height = atof(strtok(NULL, ","));
            building.energyEfficiency = atof(strtok(NULL, ","));
            building.amountApartments = atoi(strtok(NULL, ","));

            building.apartmentPrices = (float*)malloc(building.amountApartments * sizeof(float));
            token = strtok(NULL, "\n");
            price_token = strtok(token, ";");
            for(int i=0; i<building.amountApartments; i++){
                if(price_token != NULL){
                    building.apartmentPrices[i] = atof(price_token);
                    price_token = strtok(NULL, ";");
                }
            }
            append(head, building);
        }
        fclose(file);
    }
    else{
        printf("Error opening file\n");
    }
}

int main() {
    Node* head = NULL;
    read_from_csv(&head);
    print_list(head);
    free_list(head);
    return 0;
}