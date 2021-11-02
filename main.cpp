#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class Node
{
public:
    int data;
    Node *next;
    //Node() {}
};

class SLL
{
    Node *start;

public:
    SLL()
    {
        start = NULL;
    }
    Node *createNode(int value);
    void insertAtEnd(int value); //this->value
    void insertBefore(int value, int ele);
    void insertAfter(int value, int ele);
    void deleteNode(int value);
    void display();
    void reverseList();
    void sortList();
    void deleteAlternateNodes();
    void insertNodeWhileSorted(int value);
};

Node *SLL::createNode(int value)
{
    Node *temp = new Node();
    temp->data = value;
    temp->next = NULL;
    //cout<<temp->data;
    return temp;
}

void SLL::insertAtEnd(int value)
{
    Node *temp = createNode(value);
    //cout<<temp->data;
    if (start == NULL)
    {
        start = temp;
    }
    else
    {
        Node *curr;
        for (curr = start; curr->next != NULL; curr = curr->next)
            ;
        curr->next = temp;
        //cout<<curr->data;
    }
    cout << "Inserted Node at Last. " << endl;
}

void SLL::display()
{
    if (start == NULL)
    {
        cout << "The List is Empty" << endl;
        return;
    }
    cout << "Elements of list are: " << endl;
    Node *curr;
    for (curr = start; curr->next != NULL; curr = curr->next)
    {
        cout << curr->data << "->";
    }
    cout << curr->data;
}

void SLL::insertAfter(int value, int ele)
{
    Node *temp = createNode(value);
    Node *curr;
    for (curr = start; curr->next != NULL; curr = curr->next)
    {
        if (curr->data == ele)
        {
            temp->next = curr->next;
            curr->next = temp;
            return;
        }
    }
    if (curr->data == ele)
    {
        curr->next = temp;
    }
    else
        cout << "Element not found" << endl;
}

void SLL::insertBefore(int value, int ele)
{
    Node *temp = createNode(value);
    if (start->data == ele)
    {
        temp->next = start;
        start = temp;
        return;
    }
    Node *curr;
    for (curr = start; curr->next /*->next*/ != NULL; curr = curr->next)
    {
        if (curr->next->data == ele)
        {
            temp->next = curr->next;
            curr->next = temp;
            return;
        }
    }
    /*Logic 2
    for(curr=start; curr->next!= NULL; curr = curr->next)
    {
        if(curr->data==ele)
        {
            temp->next=curr;
            prev->next=temp;
            return;
        }
        prev=curr;
    }
    */
    /*
    if(curr->next->data==ele)
    {
        temp->next=curr->next;
        curr->next=temp;
        return;
    }
    else*/
    cout << "Element not found" << endl;
}

void SLL::deleteNode(int value)
{
    if (start == NULL)
    {
        cout << "The List is Empty" << endl;
        return;
    }
    if (start->data == value)
    {
        Node *temp = start->next;
        delete start;
        start = temp;
        return;
    }
    /*
    if(start->next==NULL)
    {
        cout<<"Element not found"<<endl;
        return;
    }*/
    Node *curr;
    for (curr = start; curr->next /*->next*/ != NULL; curr = curr->next)
    {
        if (curr->next->data == value)
        {
            Node *temp = curr->next->next;
            delete curr->next;
            curr->next = temp;
            return;
        }
    }
    /*
    if(curr->next->data==value)
    {
        Node* temp=curr->next->next;
        delete curr->next;
        curr->next=temp;
        return;
    }
    else*/
    cout << "Element not found" << endl;
    return;
}

void SLL::reverseList()
{
    Node *ptr1, *ptr2, *ptr3;
    if (start == NULL)
    {
        cout << "List is empty" << endl;
        return;
    }
    if (start->next == NULL)
    {
        return;
    }
    ptr1 = start;
    ptr2 = ptr1->next;
    ptr3 = ptr2->next;
    ptr1->next = NULL;
    ptr2->next = ptr1;
    while (ptr3 != NULL)
    {
        ptr1 = ptr2;
        ptr2 = ptr3;
        ptr3 = ptr3->next;
        ptr2->next = ptr1;
    }
    start = ptr2;
}

void SLL::sortList()
{
    Node *ptr, *s;
    int value;
    if (start == NULL)
    {
        cout << "The List is empty" << endl;
        return;
    }
    ptr = start;
    while (ptr != NULL)
    {
        for (s = ptr->next; s != NULL; s = s->next)
        {
            if (ptr->data > s->data)
            {
                value = ptr->data;
                ptr->data = s->data;
                s->data = value;
            }
        }
        ptr = ptr->next;
    }
}

void SLL::deleteAlternateNodes()
{
    if (start == NULL)
        return;
    Node *prev = start;
    Node *node = start->next;
    while (prev != NULL && node != NULL)
    {
        prev->next = node->next;
        delete node;
        prev = prev->next;
        if (prev != NULL)
            node = prev->next;
    }
}

void SLL::insertNodeWhileSorted(int value)
{
    insertAtEnd(value);
    sortList();
}

int main()
{
    int choice;
    SLL sl;
    while (1)
    {
        cout << endl;
        cout << "----------------------------------" << endl;
        cout << " Operations on singly linked list " << endl;
        cout << "----------------------------------" << endl;
        cout << "0. Insert Node at End" << endl;
        cout << "1. Insert Node before an Element" << endl;
        cout << "2. Insert Node after an Element" << endl;
        cout << "3. Delete Node" << endl;
        cout << "4. Traverse/Display the List" << endl;
        cout << "5. Reverse the List" << endl;
        cout << "6. Sort the List" << endl;
        cout << "7. Delete Alternate Nodes" << endl;
        cout << "8. Insert Node while keeping List sorted" << endl;
        cout << "999. Exit" << endl;
        cout << "Enter your choice : ";
        cin >> choice;
        int val, ele;
        switch (choice)
        {
        case 0:
            cout << "Enter value: ";
            cin >> val;
            sl.insertAtEnd(val);
            break;
        case 1:
            cout << "Enter value: ";
            cin >> val;
            cout << "Enter element before which value must be added: ";
            cin >> ele;
            sl.insertBefore(val, ele);
            break;
        case 2:
            cout << "Enter value: ";
            cin >> val;
            cout << "Enter element after which value must be added: ";
            cin >> ele;
            sl.insertAfter(val, ele);
            break;
        case 3:
            cout << "Enter value: ";
            cin >> val;
            sl.deleteNode(val);
            break;
        case 4:
            sl.display();
            break;
        case 5:
            sl.reverseList();
            break;
        case 6:
            sl.sortList();
            break;
        case 7:
            sl.deleteAlternateNodes();
            break;
        case 8:
            cout << "Enter value: ";
            cin >> val;
            sl.insertNodeWhileSorted(val);
            break;
        case 999:
            cout << "Exiting..." << endl;
            exit(0);
            break;
        default:
            cout << "Wrong choice" << endl;
        }
        cout << endl;
    }
    return 0;
}
