// linked_list.cc -- functions for linked_list lab (cs221)

#include "linked_list.h"

/**
 * Inserts a new Node (with key=newKey) at the head of the linked_list.
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty)
 * PRE: newKey is the value for the key in the new Node
 * POST: the new Node is now the head of the linked_list
 */
void insert(Node *&head, int newKey)
{
    Node *curr = new Node(newKey, head);
    head = curr;
}

/**
 * Print the keys of a linked_list in order, from head to tail
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty)
 */
void print(Node *head)
{
    std::cout << "[";
    for (Node *curr = head; curr != NULL; curr = curr->next)
    {
        std::cout << curr->key;
        if (curr->next != NULL)
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

/**
 * Returns the size (number of Nodes) of the linked_list
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty)
 */
int size(Node *head)
{
    if (!head) return 0;
    return 1 + size(head->next);
}

/**
 * Copies the keys in a linked list to a vector.
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty)
 * POST: a new vector<int> containing the keys in the correct order has been returned.
 */
std::vector<int> to_vector(Node *head)
{
    std::vector<int> result;
    for (Node *curr = head; curr != NULL; curr = curr->next)
    {
        result.push_back(curr->key);
    }
    return result;
}

/**
 * Delete the last Node in the linked_list
 * PRE: head is the first Node in a linked_list (if NULL, linked_list is empty)
 * POST: the last Node of the linked_list has been removed
 * POST: if the linked_list is now empty, head has been changed
 * POST: else head remains the first Node in the linked_list
 */
void delete_last_element(Node *&head)
{
    // ******** WRITE YOUR CODE HERE ********
    if (head == nullptr) return;
    if(head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }
    delete_last_element(head->next);
}

// {
//     // ******** WRITE YOUR CODE HERE ********
//     int curr_size = size(head);
//     if (curr_size == 1) {
//         delete head;
//         head = NULL;
//     } else {
//         Node *curr = head;
//         for (int i=1; i<=curr_size-2; i++) {
//             curr = curr->next;
//     }      
//     delete curr->next;
//     curr->next = NULL;
//     }
// }

/**
 * Removes an existing Node (with key=oldKey) from the linked_list.
 * PRE: head is the first node in a linked_list (if NULL, linked_list is empty)
 * PRE: oldKey is the value of the key in the Node to be removed
 * PRE: if no Node with key=oldKey exists, the linked_list has not changed
 * POST: if a Node with key=oldKey was found, then it was deleted
 * POST: other Nodes with key=oldKey might still be in the linked_list
 * POST: head is the new first Node of the linked_list, if updated
 */
void remove(Node *&head, int oldKey)
{
    // ******** WRITE YOUR CODE HERE ********
    if (head == nullptr) return;
    if(head->key == oldKey) {
        Node *temp = head;
        head = head->next;
        delete temp;
        return;
    }
    remove(head->next, oldKey);
}

// {
//     // ******** WRITE YOUR CODE HERE ********
//     Node *curr = head, *delete_curr = head;
//     int curr_size = size(head);

//     //head
//     if (delete_curr->key == oldKey) {
//         head = head->next;
//         delete delete_curr;
//         return;
//     } 

//     //body and tail
//     for(int i=1; i<curr_size; i++) {
//         delete_curr=delete_curr->next;
//         if (delete_curr->key == oldKey) {
//             if(i == curr_size-1) {
//                 for(int j=1; j<i-1; j++) {
//                     curr=curr->next;
//                 }
//                 curr->next=NULL;
//                 delete delete_curr;
//                 return;
//             }else {
//                 for(int j=1; j<i-1; j++) {
//                     curr=curr->next;
//                 }
//                 curr->next=delete_curr->next;
//                 delete delete_curr;
//                 return;
//             }
//         }
//     }
// }

/**
 * Insert a new Node (with key=newKey) after an existing Node (with key=oldKey)
 * If there is no existing Node with key=oldKey, then no action.
 * PRE: head is the first Node in a linked_list (if NULL, linked_list is empty)
 * PRE: oldKey is the value to look for (in the key of an existing Node)
 * PRE: newKey is the value of the key in the new Node (that might be inserted)
 * POST: if no Node with key=oldKey was found, then the linked_list has not changed
 * POST: else a new Node (with key=newKey) is right after the Node with key = oldKey.
 */
void insert_after(Node *head, int oldKey, int newKey)
{
    // ******** WRITE YOUR CODE HERE ********
   if (head == nullptr) return;
   if(head->key == oldKey) {
    Node *newNode = new Node(newKey,head->next);
    head->next = newNode;
    return;
   }
   insert_after(head->next , oldKey, newKey);
}

// {
//     // ******** WRITE YOUR CODE HERE ********
//     Node *curr = new Node(newKey,NULL);
//     Node *find = head;
//     int curr_size = size(head);

//     //head
//     if (find->key == oldKey) {
//         curr->next = find->next;
//         find->next = curr;
//         return;      
//     }
//     //body and tail    
//     for(int i=1; i<curr_size; i++) {
//         find = find->next;
//         if (find->key == oldKey) {
//             if (i == curr_size-1) {
//                 find->next = curr;
//                 return;
//             } else {
//                 curr->next = find->next;
//                 find->next = curr;
//                 return;
//             }
//         }
//     }
// }

/**
 * Create a new linked_list by merging two existing linked_lists.
 * PRE: list1 is the first Node in a linked_list (if NULL, then it is empty)
 * PRE: list2 is the first Node in another linked_list (if NULL, then it is empty)
 * POST: A new linked_list is returned that contains new Nodes with the keys from
 * the Nodes in list1 and list2, starting with the key of the first Node of list1,
 * then the key of the first Node of list2, etc.
 * When one list is exhausted, the remaining keys come from the other list.
 * For example: [1, 2] and [3, 4, 5] would return [1, 3, 2, 4, 5]
 */
Node *interleave(Node *list1, Node *list2) 
{
    // ******** WRITE YOUR CODE HERE ********
    Node merged_list = Node(0,nullptr);
    Node *curr = &merged_list;
    while(list1 != nullptr) {
        curr->next = new Node(list1->key, nullptr);
        curr = curr->next;
        Node* temp = list1->next;
        list1 = list2;
        list2 = temp;
    }
    while(list2 != nullptr) {
        curr->next = new Node(list2->key, nullptr);
        curr = curr->next;
        list2 = list2->next;
    }
    return merged_list.next;
}


// {
//     // ******** WRITE YOUR CODE HERE ********
//     int size1 = size(list1), size2 = size(list2);
    
//     //In case one of the List is empty
//     if (size1 == 0) {
//         return list2;
//     }
//     if (size2 == 0) {
//         return list1;
//     }

//     //when none of the lists are empty
//     int min_size = std::min(size1, size2);
//     Node *merged_list = new Node(0, NULL);

//     Node *curr1 = list1, *curr2 = list2, *curr_merged = merged_list, *tail;
    
//     for (int i=1; i<min_size; i++) {
//         if (i == min_size-1) { //tail
//             curr_merged->key = curr1->key;
//             curr_merged->next = new Node(curr2->key, new Node(curr1->next->key, new Node(curr2->next->key, NULL)));
//             curr_merged = curr_merged->next->next->next;
//             if (size1 > size2) {
//                 tail = curr1->next->next;
//             } else {
//                 tail = curr2->next->next;
//             }
//         } else { //body
//             curr_merged->key = curr1->key;
//             curr_merged->next = new Node(curr2->key,new Node(0, NULL));
//             //iteration
//             curr1 = curr1->next;
//             curr2 = curr2->next;
//             curr_merged = curr_merged->next->next;
//         }  
//     }
//     //deal with reamining tail
//     for (int i=1; i<=std::abs(size1 - size2); i++) {
//         curr_merged->next = new Node(tail->key,NULL);

//         curr_merged = curr_merged->next;
//         tail = tail->next;
//     }

//     return merged_list;
// }
