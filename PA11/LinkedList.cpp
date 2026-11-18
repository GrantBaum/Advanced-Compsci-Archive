#include "LinkedList.h"
#include <iostream>


/**
 * LinkedList
 * Constructor for the LinkedList class.
 *
 * Description:
 *     This is the default constructor for the LinkedList class. It initializes
 *     the head pointer of the list to nullptr, indicating that the list is initially empty.
 *     This constructor is called automatically when a new instance of the LinkedList class
 *     is created.
 *
 * Example Usage:
 *     LinkedList myList; // Creates an empty linked list with the head pointer set to nullptr
 *
 * Note:
 *     As this constructor initializes an empty list, no nodes are created or allocated.
 *     It is simply preparing the LinkedList object for use.
 *     THIS FUNCTION IS ALREADY DONE FOR YOU, THERE IS NO WORK TO DO HERE
 */
LinkedList::LinkedList() : head(nullptr) {}

/**
 * append
 * Adds a new node with the specified data to the end of the list.
 *
 * Description:
 *     This function creates a new node with the provided data and appends it
 *     at the end of the linked list. If the list is empty (head is nullptr),
 *     the new node is set as the head of the list. Otherwise, the function traverses
 *     the list to find the last node and sets its next pointer to the new node,
 *     effectively adding the new node at the end of the list.
 *
 * Parameters:
 *     data - The data value (integer) to be stored in the new node that will be
 *            added at the end of the list.
 *
 * Returns:
 *     void: This function does not return any value.
 *
 * Example Usage:
 *     LinkedList list;
 *     list.append(5);  // Adds a new node with data 5 at the end of the list
 */
void LinkedList::append(int data) {
    // TODO: Implement append method

}

/**
 * display
 * Outputs the data in each node of the linked list to the console.
 *
 * Description:
 *     This function traverses the linked list starting from the head, and prints
 *     the data in each node to the console. The format for displaying each node is
 *     '[Node Data] -> '. When the end of the list is reached, it prints 'NULL' to
 *     indicate the end of the list. This function is useful for visually verifying
 *     the contents and structure of the linked list.
 *
 * Example Output:
 *     If the linked list contains the elements 5, 8, and 3, the output will be:
 *     '5 -> 8 -> 3 -> NULL'
 *
 *     If the linked list is empty, the output will be:
 *     'NULL'
 *
 * Note:
 *     This function is declared as const because it does not modify any member
 *     variables of the LinkedList class. It only reads and displays them.
 *
 * Returns:
 *     void: This function does not return any value.
 */
void LinkedList::display() const {
    // TODO: Implement display method

}

/**
 * prepend
 * Inserts a new node with the specified data at the beginning of the list.
 *
 * Description:
 *     This function creates a new node with the given data and adds it to the
 *     start of the linked list. The new node becomes the new head of the list.
 *     If the list is empty (head is nullptr), the new node is simply set as the head.
 *     If the list is not empty, the new node is inserted before the current head
 *     and its next pointer is set to the former head.
 *
 * Parameters:
 *     data - The data value (integer) to be stored in the new node that will be
 *            added at the beginning of the list.
 *
 * Returns:
 *     void: This function does not return any value.
 */
void LinkedList::prepend(int data) {
    // TODO: Implement prepend method

}

/**
 * removeHead
 * Removes the head (first node) of the linked list.
 *
 * Description:
 *     This function removes the first node of the list, if it exists.
 *     It handles two cases:
 *     1. When the list is empty, it simply returns false as there is no node to remove.
 *     2. When the list has one or more nodes, it removes the head and updates the head
 *        pointer to the next node (if present).
 *
 * Returns:
 *     bool: Returns true if the head is successfully removed.
 *           Returns false if the list is empty and there is no head to remove.
 */
bool LinkedList::removeHead(){
    // If the list is empty, there is no head to remove
    return false;
}

/**
 * remove
 * Removes a node containing the specified data from the linked list.
 *
 * Description:
 *     This function searches for a node with the specified data value and removes it
 *     from the list. The function handles three main scenarios:
 *     1. The list is empty (head is nullptr), in which case it returns false as there
 *        is nothing to remove.
 *     2. The head itself contains the data to be removed. In this case, it removes the head
 *        and updates the head pointer to the next node.
 *     3. The data to be removed is in a node elsewhere in the list. The function traverses
 *        the list, finds the node, removes it by adjusting the pointers, and deallocates
 *        the memory.
 *
 * Parameters:
 *     data - The data value (integer) to be searched and removed from the list.
 *
 * Returns:
 *     bool: Returns true if a node with the specified data was found and removed.
 *           Returns false if no node with the specified data was found.
 *
 * Note:
 *     This function deletes the first occurrence of the specified data. If there are
 *     multiple nodes with the same data, only the first one encountered is removed.
 */
bool LinkedList::remove(int data) {
    // TODO: Implement remove method

    return false; // Placeholder return
}

/**
 * insertAfter
 * Inserts a new node with the specified data immediately after the first occurrence of a node with specified 'after' data.
 *
 * Description:
 *     This function traverses the linked list to find the first node that contains
 *     the data value specified by 'after'. Once this node is found, a new node
 *     containing the 'data' is inserted into the list immediately after it.
 *     If the 'after' node is not found in the list, the new node is not inserted.
 *
 * Parameters:
 *     after - The data value (integer) of the node after which the new node is to be inserted.
 *     data - The data value (integer) to be stored in the new node that is to be inserted.
 *
 * Note:
 *     This function only inserts after the first occurrence of the 'after' value.
 *     If there are multiple nodes with the 'after' value, the new node will be
 *     inserted only after the first one of these.
 *
 * Returns:
 *     void: This function does not return any value.
 */
void LinkedList::insertAfter(int after, int data) {
    // TODO: Implement insertAfter method

}

/**
 * ~LinkedList
 * Destructor for the LinkedList class.
 *
 * Description:
 *     This destructor is responsible for deallocating memory used by the linked list.
 *     It iterates through the entire list and deletes each node to prevent memory leaks.
 *     Starting from the head, it moves through each node, keeping track of the next node
 *     before deleting the current one. This process continues until all nodes have been
 *     safely deallocated.
 *
 * Important Note:
 *     It is essential to handle the deletion process carefully to avoid dangling pointers
 *     and other common pitfalls associated with dynamic memory management. The destructor
 *     ensures that all dynamically allocated memory for the nodes is properly freed when
 *     an instance of the LinkedList is destroyed.
 *
 * Usage:
 *     When an instance of LinkedList goes out of scope or is explicitly deleted,
 *     this destructor is automatically called to clean up the resources.
 */
LinkedList::~LinkedList() {
    // TODO: Implement the destructor to free memory
}

/**
 * reverse
 * Reverses the linked list so that the last node becomes the first node and vice versa.
 *
 * Description:
 *     This function iteratively reverses the linked list. It works by changing the
 *     direction of each node's next pointer to point to its previous node. It keeps
 *     track of three pointers during each iteration: the current node being processed,
 *     the previous node, and the next node in the original sequence. By the end of
 *     the iteration, the head pointer is updated to point to what was originally
 *     the last node of the list, effectively reversing the list.
 *
 * Notes:
 *     1. If the list is empty (head is nullptr), the function does nothing.
 *     2. The function operates in-place, meaning it doesn't create a new list but
 *        modifies the original list.
 *
 * Complexity:
 *     Time Complexity: O(n), where n is the number of nodes in the list, as it
 *     needs to traverse the entire list once.
 *
 * Returns:
 *     void: This function does not return any value.
 */
void LinkedList::reverse() {
    // TODO: Implement reverse method

}