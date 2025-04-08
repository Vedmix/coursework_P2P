#include "stdio.h"

void read_from_csv() {
    FILE* file = fopen("books.csv", "r");
    if (!file) {
        printf("Error opening file books.csv\n");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        BOOK book;
        char* token;

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
        char* age_token = strtok(token, ";");
        for (int i = 0; i < book.readerCount; i++) {
            if (age_token != NULL) {
                book.readerAges[i] = atoi(age_token);
                age_token = strtok(NULL, ";");
            }
        }

        append(head, book);
    }
    fclose(file);
}

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
        new_node->prev = current; // Устанавливаем указатель на предыдущий узел
    }
}

int main(){




return 0;
}
