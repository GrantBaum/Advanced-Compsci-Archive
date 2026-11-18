#include "LinkedList.h"
#include <iostream>
#include <cstring>  // Include for strcmp

int main(int argc, char* argv[]) {
    LinkedList* list = new LinkedList();

    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " testCase#" << std::endl;
        delete list;
        return 0;
    }

    //TODO: Still need test cases for memory leaks
    if (std::strcmp(argv[1], "51") == 0) {
        std::cout << "Test Case 51: Seeing if memory leak occurs if insert 1 thing and delete one thing: "<<std::endl;
        list->append(10);
        list->removeHead();
        delete list; 
        return 0;
    }

    // Test Case 1: Create an empty list and check if display works
    std::cout << "Test Case 1: Displaying empty list: ";
    list->display();  // Expected output: NULL
    if (std::strcmp(argv[1], "1") == 0) {return 0;}

    // Test Case 2: Append an item to the empty list
    list->append(10);
    std::cout << "Test Case 2: Appending 10 to list: ";
    list->display();  // Expected output: 10 -> NULL
    if(std::strcmp(argv[1], "2") == 0){return 0;}

    // Test Case 3: Append another item
    list->append(20);
    std::cout << "Test Case 3: Appending 20 to list: ";
    list->display();  // Expected output: 10 -> 20 -> NULL
    if(std::strcmp(argv[1], "3") == 0){return 0;}

    // Test Case 4: Remove head
    std::cout << "Test Case 4: Removing the head: ";
    list->removeHead();
    list->display();  // Expected output: 20 -> NULL
    if(std::strcmp(argv[1], "4") == 0){return 0;}

    // Test Case 5: Remove head
    std::cout << "Test Case 5: Removing the head: ";
    list->removeHead();
    list->display();  // Expected output: NULL
    if(std::strcmp(argv[1], "5") == 0){return 0;}

    // Test Case 6: Adding many elements together to conserve space
    std::cout << "Test Case 6: Adding elements 5, 20, 50, and 2 to a blank LinkedList: ";
    list->append(5); list->append(20); list->append(50); list->append(2); 
    list->display();  // Expected output: 5 -> 20 -> 50 -> 2 -> NULL
    if(std::strcmp(argv[1], "6") == 0){return 0;}

    // Test Case 7: Deleting the LinkedList
    std::cout << "Test Case 7: Deleting the LinkedList: ";
    delete list;
    std::cout << "The delete should have occured. Check CheckIn to see the Valgrind output"<<std::endl;
    if(std::strcmp(argv[1], "7") == 0){return 0;}

    // Test Case 8: Prepending an item to an empty list
    std::cout << "Test Case 8: Prepending 30 to empty list (that has been created new): ";
    list = new LinkedList();
    list->prepend(30);
    list->display();  // Expected output: 30 -> NULL
    if(std::strcmp(argv[1], "8") == 0){return 0;}

    // Test Case 9: Prepending an item to a non-empty list
    std::cout << "Test Case 9: Prepending 40 to list: ";
    list->prepend(40);
    list->display();  // Expected output: 40 -> 30 -> NULL
    if(std::strcmp(argv[1], "9") == 0){return 0;}

    // Test Case 10: Removing head from a list with multiple elements
    std::cout << "Test Case 10: Removing the head from a list with multiple elements: ";
    list->removeHead();
    list->display();  // Expected output: 30 -> NULL
    if(std::strcmp(argv[1], "10") == 0){return 0;}

    // Test Case 11: Removing head from a list with one element
    std::cout << "Test Case 11: Removing the head from a list with one element: ";
    list->removeHead();
    list->display();  // Expected output: NULL
    if(std::strcmp(argv[1], "11") == 0){return 0;}

    // Test Case 12: Removing head from an empty list
    std::cout << "Test Case 12: Removing head from an empty list: ";
    list->removeHead();
    list->display();  // Expected output: NULL
    if(std::strcmp(argv[1], "12") == 0){return 0;}

    // Test Case 13: Appending items to a list and then removing head
    std::cout << "Test Case 13: Appending items and then removing head: ";
    list->append(60); list->append(70); list->removeHead();
    list->display();  // Expected output: 70 -> NULL
    if(std::strcmp(argv[1], "13") == 0){return 0;}

    // Test Case 14: Removing an item that does not exist in a non-empty list
    std::cout << "Test Case 14: Removing non-existing item from non-empty list: ";
    bool removed = list->remove(100);
    std::cout << "Removed: " << removed << " | List: ";
    list->display();  // Expected output: Removed: 0 | List: 70 -> NULL
    if(std::strcmp(argv[1], "14") == 0){return 0;}

    // Test Case 15: Removing an item that exists in a non-empty list
    std::cout << "Test Case 15: Removing existing item from non-empty list: ";
    list->append(80);
    removed = list->remove(70);
    std::cout << "Removed: " << removed << " | List: ";
    list->display();  // Expected output: Removed: 1 | List: 80 -> NULL
    if(std::strcmp(argv[1], "15") == 0){return 0;}

    // Test Case 16: Removing from an empty list
    std::cout << "Test Case 16: Removing from an empty list: ";
    list->removeHead();
    removed = list->remove(80);
    std::cout << "Removed: " << removed << " | List: ";
    list->display();  // Expected output: Removed: 0 | List: NULL
    if(std::strcmp(argv[1], "16") == 0){return 0;}

    // Test Case 17: Inserting after a non-existing item in a non-empty list
    std::cout << "Test Case 17: Inserting after non-existing item in non-empty list: ";
    list->append(90);
    list->insertAfter(100, 110);
    list->display();  // Expected output: 90 -> NULL
    if(std::strcmp(argv[1], "17") == 0){return 0;}

    // Test Case 18: Inserting after an existing item in a non-empty list
    std::cout << "Test Case 18: Inserting after existing item in non-empty list: ";
    list->insertAfter(90, 120);
    list->display();  // Expected output: 90 -> 120 -> NULL
    if(std::strcmp(argv[1], "18") == 0){return 0;}

        // Test Case 19: Testing append on an empty list with a negative number
    std::cout << "Test Case 19: Appending -5 to an empty list: ";
    delete list; list = new LinkedList();
    list->append(-5);
    list->display();  // Expected output: -5 -> NULL
    if(std::strcmp(argv[1], "19") == 0){return 0;}

    // Test Case 20: Testing append on an empty list with zero
    std::cout << "Test Case 20: Appending 0 to an empty list: ";
    delete list; list = new LinkedList();
    list->append(0);
    list->display();  // Expected output: 0 -> NULL
    if(std::strcmp(argv[1], "20") == 0){return 0;}

    // Test Case 21: Testing prepend on an empty list with a negative number
    std::cout << "Test Case 21: Prepending -10 to an empty list: ";
    delete list; list = new LinkedList();
    list->prepend(-10);
    list->display();  // Expected output: -10 -> NULL
    if(std::strcmp(argv[1], "21") == 0){return 0;}

    // Test Case 22: Testing prepend on an empty list with zero
    std::cout << "Test Case 22: Prepending 0 to an empty list: ";
    delete list; list = new LinkedList();
    list->prepend(0);
    list->display();  // Expected output: 0 -> NULL
    if(std::strcmp(argv[1], "22") == 0){return 0;}

    // Test Case 23: Removing from an empty list
    std::cout << "Test Case 23: Removing from an empty list: ";
    delete list; list = new LinkedList();
    list->removeHead();
    list->display();  // Expected output: NULL
    if(std::strcmp(argv[1], "23") == 0){return 0;}

    // Test Case 24: Inserting after a non-existing item in an empty list
    std::cout << "Test Case 24: Inserting after non-existing item in an empty list: ";
    delete list; list = new LinkedList();
    list->insertAfter(100, 110);
    list->display();  // Expected output: NULL
    if(std::strcmp(argv[1], "24") == 0){return 0;}

    // Test Case 25: Reversing an empty list
    std::cout << "Test Case 25: Reversing an empty list: ";
    delete list; list = new LinkedList();
    list->reverse();
    list->display();  // Expected output: NULL
    if(std::strcmp(argv[1], "25") == 0){return 0;}

    // Test Case 26: Reversing a list with one element
    std::cout << "Test Case 26: Reversing a list with one element: ";
    delete list; list = new LinkedList();
    list->append(42);
    list->reverse();
    list->display();  // Expected output: 42 -> NULL
    if(std::strcmp(argv[1], "26") == 0){return 0;}

    // Test Case 27: Reversing a list with two elements
    std::cout << "Test Case 27: Reversing a list with two elements: ";
    delete list; list = new LinkedList();
    list->append(10);
    list->append(20);
    list->reverse();
    list->display();  // Expected output: 20 -> 10 -> NULL
    if(std::strcmp(argv[1], "27") == 0){return 0;}

    // Test Case 28: Reversing a list with multiple elements
    std::cout << "Test Case 28: Reversing a list with multiple elements: ";
    delete list; list = new LinkedList();
    list->append(5); list->append(7); list->append(9);
    list->reverse();
    list->display();  // Expected output: 9 -> 7 -> 5 -> NULL
    if(std::strcmp(argv[1], "28") == 0){return 0;}

    // Test Case 29: Inserting after the head in a list with one element
    std::cout << "Test Case 29: Inserting after head in a list with one element: ";
    delete list; list = new LinkedList();
    list->append(50);
    list->insertAfter(50, 60);
    list->display();  // Expected output: 50 -> 60 -> NULL
    if(std::strcmp(argv[1], "29") == 0){return 0;}

    // Test Case 30: Inserting after the head in a list with multiple elements
    std::cout << "Test Case 30: Inserting after head in a list with multiple elements: ";
    delete list; list = new LinkedList();
    list->append(30); list->append(40); list->append(50);
    list->insertAfter(30, 35);
    list->display();  // Expected output: 30 -> 35 -> 40 -> 50 -> NULL
    if(std::strcmp(argv[1], "30") == 0){return 0;}

    // Test Case 31: Inserting after a non-existing item in a list with multiple elements
    std::cout << "Test Case 31: Inserting after non-existing item in a list with multiple elements: ";
    delete list; list = new LinkedList();
    list->append(10); list->append(20); list->append(30);
    list->insertAfter(15, 25);
    list->display();  // Expected output: 10 -> 20 -> 30 -> NULL
    if(std::strcmp(argv[1], "31") == 0){return 0;}

    // Test Case 32: Inserting after the last element in a list with multiple elements
    std::cout << "Test Case 32: Inserting after the last element in a list with multiple elements: ";
    delete list; list = new LinkedList();
    list->append(5); list->append(15); list->append(25);
    list->insertAfter(25, 35);
    list->display();  // Expected output: 5 -> 15 -> 25 -> 35 -> NULL
    if(std::strcmp(argv[1], "32") == 0){return 0;}

    // Test Case 33: Removing an item that does not exist in an empty list
    std::cout << "Test Case 33: Removing non-existing item from an empty list: ";
    delete list; list = new LinkedList();
    bool removed33 = list->remove(100);
    std::cout << "Removed: " << removed33 << " | List: ";
    list->display();  // Expected output: Removed: 0 | List: NULL
    if(std::strcmp(argv[1], "33") == 0){return 0;}

    // Test Case 34: Removing an item that does not exist in a list with one element
    std::cout << "Test Case 34: Removing non-existing item from a list with one element: ";
    delete list; list = new LinkedList();
    list->append(5);
    bool removed34 = list->remove(10);
    std::cout << "Removed: " << removed34 << " | List: ";
    list->display();  // Expected output: Removed: 0 | List: 5 -> NULL
    if(std::strcmp(argv[1], "34") == 0){return 0;}

    // Test Case 35: Removing an item that does not exist in a list with multiple elements
    std::cout << "Test Case 35: Removing non-existing item from a list with multiple elements: ";
    delete list; list = new LinkedList();
    list->append(10); list->append(20); list->append(30);
    bool removed35 = list->remove(25);
    std::cout << "Removed: " << removed35 << " | List: ";
    list->display();  // Expected output: Removed: 0 | List: 10 -> 20 -> 30 -> NULL
    if(std::strcmp(argv[1], "35") == 0){return 0;}

    // Test Case 36: Removing the head from a list with one element
    std::cout << "Test Case 36: Removing the head from a list with one element: ";
    delete list; list = new LinkedList();
    list->append(42);
    list->removeHead();
    list->display();  // Expected output: NULL
    if(std::strcmp(argv[1], "36") == 0){return 0;}

    // Test Case 37: Removing the head from a list with multiple elements
    std::cout << "Test Case 37: Removing the head from a list with multiple elements: ";
    delete list; list = new LinkedList();
    list->append(5); list->append(10); list->append(15);
    list->removeHead();
    list->display();  // Expected output: 10 -> 15 -> NULL
    if(std::strcmp(argv[1], "37") == 0){return 0;}

    // Test Case 38: Removing the last element from a list with multiple elements
    std::cout << "Test Case 38: Removing the last element from a list with multiple elements: ";
    delete list; list = new LinkedList();
    list->append(5); list->append(10); list->append(15);
    list->remove(15);
    list->display();  // Expected output: 5 -> 10 -> NULL
    if(std::strcmp(argv[1], "38") == 0){return 0;}

    // Test Case 39: Removing an item from a list with a single element
    std::cout << "Test Case 39: Removing the only element from a list: ";
    delete list; list = new LinkedList();
    list->append(7);
    list->remove(7);
    list->display();  // Expected output: NULL
    if(std::strcmp(argv[1], "39") == 0){return 0;}

    // Test Case 40: Removing the last item from a list with multiple identical elements
    std::cout << "Test Case 40: Removing the last item from a list with multiple identical elements: ";
    delete list; list = new LinkedList();
    list->append(5); list->append(5); list->append(5);
    list->remove(5);
    list->display();  // Expected output: 5 -> 5 -> NULL
    if(std::strcmp(argv[1], "40") == 0){return 0;}

    // Test Case 41: Removing an item from a list with multiple identical elements
    std::cout << "Test Case 41: Removing an item from a list with multiple identical elements: ";
    delete list; list = new LinkedList();
    list->append(10); list->append(20); list->append(10); list->append(30);
    list->remove(10);
    list->display();  // Expected output: 20 -> 30 -> NULL
    if(std::strcmp(argv[1], "41") == 0){return 0;}

    // Test Case 42: Removing an item from a list with multiple identical elements, leaving some
    std::cout << "Test Case 42: Removing an item from a list with multiple identical elements, leaving some: ";
    delete list; list = new LinkedList();
    list->append(10); list->append(20); list->append(10); list->append(30);
    list->remove(10);
    list->display();  // Expected output: 20 -> 30 -> NULL
    if(std::strcmp(argv[1], "42") == 0){return 0;}

    // Test Case 43: Removing an item from a list with multiple identical elements, all removed
    std::cout << "Test Case 43: Removing an item from a list with multiple identical elements, all removed: ";
    delete list; list = new LinkedList();
    list->append(10); list->append(10); list->append(10); list->append(10);
    list->remove(10);
    list->display();  // Expected output: NULL
    if(std::strcmp(argv[1], "43") == 0){return 0;}

    // Test Case 44: Inserting after a non-existing item in a list with multiple identical elements
    std::cout << "Test Case 44: Inserting after non-existing item in a list with multiple identical elements: ";
    delete list; list = new LinkedList();
    list->append(10); list->append(10); list->append(10);
    list->insertAfter(20, 30);
    list->display();  // Expected output: 10 -> 10 -> 10 -> NULL
    if(std::strcmp(argv[1], "44") == 0){return 0;}

    // Test Case 45: Inserting after the last item in a list with multiple identical elements
    std::cout << "Test Case 45: Inserting after the last item in a list with multiple identical elements: ";
    delete list; list = new LinkedList();
    list->append(10); list->append(10); list->append(10);
    list->insertAfter(10, 20);
    list->display();  // Expected output: 10 -> 10 -> 10 -> 20 -> NULL
    if(std::strcmp(argv[1], "45") == 0){return 0;}

    // Test Case 46: Inserting after the first item in a list with multiple identical elements
    std::cout << "Test Case 46: Inserting after the first item in a list with multiple identical elements: ";
    delete list; list = new LinkedList();
    list->append(10); list->append(10); list->append(10);
    list->insertAfter(10, 20);
    list->display();  // Expected output: 10 -> 20 -> 10 -> 10 -> NULL
    if(std::strcmp(argv[1], "46") == 0){return 0;}

    // Test Case 47: Inserting after an item in a list with multiple identical elements, all updated
    std::cout << "Test Case 47: Inserting after an item in a list with multiple identical elements, all updated: ";
    delete list; list = new LinkedList();
    list->append(10); list->append(10); list->append(10);
    list->insertAfter(10, 20);
    list->display();  // Expected output: 10 -> 20 -> 10 -> 20 -> 10 -> 20 -> NULL
    if(std::strcmp(argv[1], "47") == 0){return 0;}

    // Test Case 48: Inserting after a non-existing item in a list with multiple identical elements, all updated
    std::cout << "Test Case 48: Inserting after non-existing item in a list with multiple identical elements, all updated: ";
    delete list; list = new LinkedList();
    list->append(10); list->append(10); list->append(10);
    list->insertAfter(5, 20);
    list->display();  // Expected output: 10 -> 10 -> 10 -> NULL
    if(std::strcmp(argv[1], "48") == 0){return 0;}

    // Test Case 49: Inserting after the last item in a list with multiple identical elements, all updated
    std::cout << "Test Case 49: Inserting after the last item in a list with multiple identical elements, all updated: ";
    delete list; list = new LinkedList();
    list->append(10); list->append(10); list->append(10);
    list->insertAfter(10, 20);
    list->display();  // Expected output: 10 -> 10 -> 10 -> 20 -> NULL
    if(std::strcmp(argv[1], "49") == 0){return 0;}

    // Test Case 50: Removing head repeatedly until empty
    std::cout << "Test Case 51: Removing head repeatedly until empty: ";
    delete list; list = new LinkedList();
    list->append(5); list->append(10); list->append(15); list->append(20);
    list->removeHead();
    list->removeHead();
    list->removeHead();
    list->removeHead();
    list->display();  // Expected output: NULL
    if(std::strcmp(argv[1], "50") == 0){return 0;}


    return 0;
}