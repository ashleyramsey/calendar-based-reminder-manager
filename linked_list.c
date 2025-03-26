#include "linked_list.h"

/*
Purpose: Creates a new linked list node containing the specified reminder text.
Parameters:  A string containing the reminder text to store in the new node (reminder)
Return Value: A pointer to the newly created node, or NULL if memory allocation fails
*/
Node* create_node(const char* reminder) {
    Node* new_node = (Node*)malloc(sizeof(Node)); // Allocate memory for the new node
    if (new_node) {
        // Copy the reminder text into the node to ensure it is null-terminated
        strncpy(new_node->reminder, reminder, MAX_STR_LEN - 1);
        new_node->reminder[MAX_STR_LEN - 1] = '\0'; 
        new_node->next = NULL;  // Initialize the next pointer to NULL
    }
    return new_node;    // Return the created node or NULL if allocation failed
}

/*
Purpose: Adds a new node containing the specified reminder to the end of the linked list
Parameters: A pointer to the pointer of the head node of the linked list (head), and a string 
containing the reminder text to store in the new node (reminder)
Return Value: None (void)
*/
void add_node(Node** head, const char* reminder) {
    Node* new_node = create_node(reminder);     // Create a new node
    if (!new_node) return;      // Exit if the node could not be created

    // If the list is empty, set the new node as the head
    if (!*head) {
        *head = new_node;
    } else {
        // Otherwise, iterate to the end of the list and add the new node
        Node* temp = *head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

/*
Purpose: Frees all nodes in a linked list, releasing the memory allocated for each node
Parameters: A pointer to the head node of the linked list (head)
Return Value: None (void)
*/
void free_all_nodes(Node* head) {
    Node* temp;
    // Iterate the list and free each node
    while (head) {
        temp = head;
        head = head->next;
        free(temp);     // Release the memory for the current node
    }
}

/*
Purpose: Prints all reminders stored in the linked list, one per line
Parameters: A pointer to the head node of the linked list (head)
Return Value: None (void)
*/
void print_list(Node* head) {
    // Iterate the list and print each reminder
    while (head) {
        printf("- %s\n", head->reminder);
        head = head->next;
    }
}
