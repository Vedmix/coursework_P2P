#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a book
typedef struct {
    char *title;
    char *author;
    int yearPublished;
    int pageCount;
    float price;
    float rating;
    int *readerAges;
    int readerCount;
} BOOK;

// Structure for a node in the linked list
typedef struct Node {
    BOOK book;
    struct Node* next;
} Node;

// Function to create a new node
Node* create_node(BOOK book) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    int success = (new_node != NULL);
    if (success) {
        new_node->book = book;
        new_node->next = NULL;
    } else {
        printf("Memory allocation error!\n");
    }
    return new_node;
}

// Function to append a book to the end of the list
void append(Node** head, BOOK book) {
    Node* new_node = create_node(book);
    Node* current = *head;
    if (*head == NULL) {
        *head = new_node;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// Function to calculate the length of the list
int length(Node* head) {
    int count = 0;
    Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Function to remove an element by its position from the end
void remove_from_end(Node** head, int position_from_end) {
    int len = length(*head);
    int position_from_start = len - position_from_end;
    Node* temp = NULL;
    Node* current = *head;

    if (*head != NULL) {
        if (position_from_end > len || position_from_start == 0) {
            temp = *head;
            *head = (*head)->next;
        } else {
            for (int i = 0; i < position_from_start - 1; i++) {
                current = current->next;
            }
            temp = current->next;
            current->next = temp->next;
        }
        
        if (temp != NULL) {
            free(temp->book.title);
            free(temp->book.author);
            free(temp->book.readerAges);
            free(temp);
            printf("Element deleted successfully.\n");
        }
    } else {
        printf("The list is empty. Deletion is not possible.\n");
    }
}

// Function to print the list
void print_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("Title: %s\n", current->book.title);
        printf("Author: %s\n", current->book.author);
        printf("Year Published: %d\n", current->book.yearPublished);
        printf("Page Count: %d\n", current->book.pageCount);
        printf("Price: %.2f\n", current->book.price);
        printf("Rating: %.2f\n", current->book.rating);
        printf("Reader Ages: ");
        for (int i = 0; i < current->book.readerCount; i++) {
            printf("%d ", current->book.readerAges[i]);
        }
        printf("\n\n");
        current = current->next;
    }
}

// Function to free the memory of the list
void free_list(Node* head) {
    Node* current = head;
    Node* temp = NULL;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp->book.title);
        free(temp->book.author);
        free(temp->book.readerAges);
        free(temp);
    }
}

// Function to read data from a CSV file
void read_from_csv(Node** head) {
    FILE* file = fopen("books.csv", "r");
    char line[1024];
    BOOK book;
    char* token;
    char* age_token;

    if (file) {
        while (fgets(line, sizeof(line), file)) {
            token = strtok(line, ",");
            book.title = (char*)malloc(strlen(token) + 1);
            strcpy(book.title, token);

            token = strtok(NULL, ",");
            book.author = (char*)malloc(strlen(token) + 1);
            strcpy(book.author, token);

            book.yearPublished = atoi(strtok(NULL, ","));
            book.pageCount = atoi(strtok(NULL, ","));
            book.price = atof(strtok(NULL, ","));
            book.rating = atof(strtok(NULL, ","));
            book.readerCount = atoi(strtok(NULL, ","));
            
            book.readerAges = (int*)malloc(book.readerCount * sizeof(int));
            token = strtok(NULL, "\n");
            age_token = strtok(token, ";");
            for (int i = 0; i < book.readerCount; i++) {
                if (age_token != NULL) {
                    book.readerAges[i] = atoi(age_token);
                    age_token = strtok(NULL, ";");
                }
            }
            
            append(head, book);
        }
        fclose(file);
    } else {
        printf("Error opening file books.csv\n");
    }
}

int main() {
    Node* head = NULL;
    int position_from_end;
    
    read_from_csv(&head);
    printf("Original list of books:\n");
    print_list(head);
    
    printf("Enter the position from the end to delete: ");
    scanf("%d", &position_from_end);
    
    remove_from_end(&head, position_from_end);
    
    printf("\nList of books after deletion:\n");
    print_list(head);
    
    free_list(head);
    return 0;
}