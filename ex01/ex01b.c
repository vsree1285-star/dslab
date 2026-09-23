#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node* createNode(int data);
void insertAtEnd(struct Node **head, int data);
void insertAtPosition(struct Node **head, int data, int position);
int searchElement(struct Node *head, int data);
void deleteElement(struct Node **head, int position);
void displayList(struct Node *head);

int main()
{
    struct Node *head = NULL;
    int choice, data, position, result;

    while (1)
    {
        printf("\nSingly Linked List Operations Menu:\n");
        printf("1. Insert at End\n");
        printf("2. Insert at Position\n");
        printf("3. Search Element\n");
        printf("4. Delete Element\n");
        printf("5. Display List\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter data to insert at end: ");
                scanf("%d", &data);
                insertAtEnd(&head, data);
                break;

            case 2:
                printf("Enter data to insert: ");
                scanf("%d", &data);

                printf("Enter position to insert (0-based index): ");
                scanf("%d", &position);

                insertAtPosition(&head, data, position);
                break;

            case 3:
                printf("Enter element to search: ");
                scanf("%d", &data);

                result = searchElement(head, data);

                if (result != -1)
                    printf("Element found at position: %d\n", result);
                else
                    printf("Element not found in the list.\n");

                break;

            case 4:
                printf("Enter position to delete (0-based index): ");
                scanf("%d", &position);

                deleteElement(&head, position);
                break;

            case 5:
                displayList(head);
                break;

            case 6:
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

struct Node* createNode(int data)
{
    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

void insertAtEnd(struct Node **head, int data)
{
    struct Node *newNode;
    struct Node *temp;

    newNode = createNode(data);

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    temp = *head;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newNode;
}

void insertAtPosition(struct Node **head, int data, int position)
{
    struct Node *newNode;
    struct Node *current;
    struct Node *previous;
    int currentPos = 0;

    if (position < 0)
    {
        printf("Error: Invalid position.\n");
        return;
    }

    newNode = createNode(data);

    if (position == 0)
    {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    current = *head;
    previous = NULL;

    while (current != NULL && currentPos < position)
    {
        previous = current;
        current = current->next;
        currentPos++;
    }

    if (currentPos != position)
    {
        printf("Error: Invalid position.\n");
        free(newNode);
        return;
    }

    newNode->next = current;
    previous->next = newNode;
}

int searchElement(struct Node *head, int data)
{
    struct Node *temp = head;
    int position = 0;

    while (temp != NULL)
    {
        if (temp->data == data)
        {
            return position;
        }

        temp = temp->next;
        position++;
    }

    return -1;
}

void deleteElement(struct Node **head, int position)
{
    struct Node *temp;
    struct Node *previous;
    int currentPos = 0;

    if (*head == NULL)
    {
        printf("Error: List is empty.\n");
        return;
    }

    if (position < 0)
    {
        printf("Error: Invalid position.\n");
        return;
    }

    temp = *head;

    if (position == 0)
    {
        *head = temp->next;
        free(temp);
        return;
    }

    previous = NULL;

    while (temp != NULL && currentPos < position)
    {
        previous = temp;
        temp = temp->next;
        currentPos++;
    }

    if (temp == NULL)
    {
        printf("Error: Invalid position.\n");
        return;
    }

    previous->next = temp->next;
    free(temp);
}

void displayList(struct Node *head)
{
    struct Node *temp = head;

    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    printf("Linked List: ");

    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }

    printf("NULL\n");
}