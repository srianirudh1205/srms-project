#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node *next;
};
struct node *head = NULL;

struct node* createNode(int val) {
    struct node *newn = (struct node*)malloc(sizeof(struct node));
    newn->data = val;
    newn->next = NULL;
    return newn;
}
void display() {
    struct node *temp = head;

    printf("\nLinked List Simulation:\n");

    if (temp == NULL) {
        printf("List is Empty\n");
        return;
    }

    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void insertBeg(int val) {
    struct node *newn = createNode(val);
    newn->next = head;
    head = newn;
    printf("\nInserted %d at Beginning\n", val);
    display();
}

void insertEnd(int val) {
    struct node *newn = createNode(val);

    if (head == NULL) {
        head = newn;
    } else {
        struct node *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newn;
    }

    printf("\nInserted %d at End\n", val);
    display();
}

void insertPos(int val, int pos) {
    struct node *newn = createNode(val);

    if (pos == 1) {
        newn->next = head;
        head = newn;
        display();
        return;
    }

    struct node *temp = head;
    int i;

    for (i = 1; i < pos-1 && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\nInvalid Position\n");
        return;
    }

    newn->next = temp->next;
    temp->next = newn;

    printf("\nInserted %d at Position %d\n", val, pos);
    display();
}

void deleteBeg() {
    if (head == NULL) {
        printf("\nList Empty\n");
        return;
    }

    struct node *temp = head;
    head = head->next;
    free(temp);

    printf("\nDeleted from Beginning\n");
    display();
}

void deleteEnd() {
    if (head == NULL) {
        printf("\nList Empty\n");
        return;
    }

    struct node *temp = head;

    if (temp->next == NULL) {
        head = NULL;
        free(temp);
    } else {
        struct node *prev = NULL;
        while (temp->next != NULL) {
            prev = temp;
            temp = temp->next;
        }
        prev->next = NULL;
        free(temp);
    }

    printf("\nDeleted from End\n");
    display();
}

void search(int val) {
    struct node *temp = head;
    int pos = 1;
    while (temp != NULL) {
        if (temp->data == val) {
            printf("\n%d found at position %d\n", val, pos);
            return;
        }
        temp = temp->next;
        pos++;
    }
    printf("\nValue Not Found\n");
}

void count() {
    struct node *temp = head;
    int c = 0;

    while (temp != NULL) {
        c++;
        temp = temp->next;
    }

    printf("\nTotal Nodes = %d\n", c);
}

int main() {
    int ch, val, pos;

    while (1) {
        printf("\n--- Linked List Simulation ---\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Delete at Beginning\n");
        printf("5. Delete at End\n");
        printf("6. Search Element\n");
        printf("7. Count Nodes\n");
        printf("8. Display\n");
        printf("9. Exit\n");

        printf("Enter choice : ");
        scanf("%d", &ch);

        switch(ch) {
            case 1:
                printf("Enter value : ");
                scanf("%d", &val);
                insertBeg(val);
                break;

            case 2:
                printf("Enter value : ");
                scanf("%d", &val);
                insertEnd(val);
                break;

            case 3:
                printf("Enter value : ");
                scanf("%d", &val);
                printf("Enter position : ");
                scanf("%d", &pos);
                insertPos(val, pos);
                break;

            case 4:
                deleteBeg();
                break;

            case 5:
                deleteEnd();
                break;

            case 6:
                printf("Enter value : ");
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
                printf("Invalid Choice\n");
        }
    }

    return 0;
}