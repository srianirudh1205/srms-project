#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *head = NULL;

// Create a new node
struct Node* getNode(int val) {
    struct Node *n = (struct Node*)malloc(sizeof(struct Node));
    n->data = val;
    n->next = NULL;
    return n;
}

// Display list
void display() {
    struct Node *temp = head;

    printf("\nLinked List: ");
    if (temp == NULL) {
        printf("EMPTY\n");
        return;
    }

    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Insert at beginning
void insertBegin(int val) {
    struct Node *n = getNode(val);
    n->next = head;
    head = n;
    printf("\nInserted %d at Beginning\n", val);
}

// Insert at end
void insertEnd(int val) {
    struct Node *n = getNode(val);

    if (head == NULL) {
        head = n;
    } else {
        struct Node *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = n;
    }

    printf("\nInserted %d at End\n", val);
}

// Insert at any position
void insertPos(int val, int pos) {
    struct Node *n = getNode(val);

    if (pos == 1) {
        n->next = head;
        head = n;
        printf("\nInserted %d at Position %d\n", val, pos);
        return;
    }

    struct Node *temp = head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\nInvalid Position!\n");
        return;
    }

    n->next = temp->next;
    temp->next = n;

    printf("\nInserted %d at Position %d\n", val, pos);
}

// Delete beginning
void deleteBegin() {
    if (head == NULL) {
        printf("\nList Empty!\n");
        return;
    }

    struct Node *temp = head;
    head = head->next;
    printf("\nDeleted %d from Beginning\n", temp->data);
    free(temp);
}

// Delete end
void deleteEnd() {
    if (head == NULL) {
        printf("\nList Empty!\n");
        return;
    }

    struct Node *temp = head, *prev = NULL;

    if (temp->next == NULL) {
        printf("\nDeleted %d from End\n", temp->data);
        head = NULL;
        free(temp);
        return;
    }

    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }

    printf("\nDeleted %d from End\n", temp->data);
    prev->next = NULL;
    free(temp);
}

// Search element
void search(int val) {
    struct Node *temp = head;
    int pos = 1;

    while (temp != NULL) {
        if (temp->data == val) {
            printf("\n%d Found at Position %d\n", val, pos);
            return;
        }
        temp = temp->next;
        pos++;
    }
    printf("\nValue NOT Found!\n");
}

// Count nodes
void count() {
    struct Node *temp = head;
    int cnt = 0;

    while (temp != NULL) {
        cnt++;
        temp = temp->next;
    }

    printf("\nTotal Nodes: %d\n", cnt);
}

int main() {
    int ch, val, pos;

    while (1) {
        printf("\n--- LINKED LIST MENU ---\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Delete at Beginning\n");
        printf("5. Delete at End\n");
        printf("6. Search Element\n");
        printf("7. Count Nodes\n");
        printf("8. Display List\n");
        printf("9. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Enter Value: ");
                scanf("%d", &val);
                insertBegin(val);
                break;

            case 2:
                printf("Enter Value: ");
                scanf("%d", &val);
                insertEnd(val);
                break;

            case 3:
                printf("Enter Value: ");
                scanf("%d", &val);
                printf("Enter Position: ");
                scanf("%d", &pos);
                insertPos(val, pos);
                break;

            case 4:
                deleteBegin();
                break;

            case 5:
                deleteEnd();
                break;

            case 6:
                printf("Enter Value: ");
                scanf("%d", &val);
                search(val);
                break;

            case 7:
                count();
                break;

            case 8:
                display();
                break;

            case 9:
                exit(0);

            default:
                printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}
