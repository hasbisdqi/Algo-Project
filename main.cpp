#include <iostream>
using namespace std;

struct Book
{
    string title, author;
};

struct Node
{
    Book data;
    Node *next;
    Node *prev;
};

struct Node *createNode(Book data)
{
    Node *newNode = new Node;
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
};

void insertHead(Node **head, Book data)
{
    Node *newNode = createNode(data);
    newNode->next = *head;
    if (*head != NULL)
    {
        (*head)->prev = newNode;
    }
    *head = newNode;
}

void insertTail(Node **head, Book data)
{
    Node *newNode = createNode(data);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void deleteNode(Node **head, string key)
{
    if (*head == NULL)
    {
        cout << "List is empty" << endl;
        return;
    }
    Node *temp = *head;
    while (temp != NULL && temp->data.title != key)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        cout << "Node not found" << endl;
        return;
    }
    if (temp->prev != NULL)
    {
        temp->prev->next = temp->next;
    }
    else
    {
        *head = temp->next;
    }
    if (temp->next != NULL)
    {
        temp->next->prev = temp->prev;
    }
    free(temp);
}

void printFromHead(Node *head)
{
    if (head == NULL)
    {
        cout << "Book not found!" << endl;
    }
    Node *temp = head;
    while (temp != NULL)
    {
        cout << "Title: " << temp->data.title << endl;
        cout << "Author: " << temp->data.author << endl;
        cout << "=====================" << endl;
        temp = temp->next;
    }
    cout << endl;
}

void addBook(Node **head, bool front)
{
    Book newBook;
    cout << "Insert book's title: ";
    getline(cin, newBook.title);
    cout << "Insert book's author: ";
    getline(cin, newBook.author);
    if (front)
    {
        insertHead(head, newBook);
    }
    else
    {
        insertTail(head, newBook);
    }
    cout << "the book \"" << newBook.title << "\" is successfully added at " << front ? "front!" : "back!";
}

void deleteBook(Node **head) {
    string key;
    cout << "Insert title for delete: ";
    getline(cin, key);
    deleteNode(head, key);
    cout << "the book \"" << key << "\" is successfully deleted!";
}

int main()
{
    Node *head = NULL;
    int choice;
    bool running = true;

    while (running)
    {
        cout << "\n=== BOOK LIST MANAGEMENT MENU ===" << endl;
        cout << "1. Add Book at front" << endl;
        cout << "2. Add Book at back" << endl;
        cout << "3. Delete Book by title" << endl;
        cout << "4. Display Books" << endl;
        cout << "5. Exit Program" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        cin.ignore();

        switch (choice)
        {
        case 1:
            addBook(&head, true);
            break;

        case 2:
            addBook(&head, false);
            break;

        case 3:
            deleteBook(&head);
            break;

        case 4:
            printFromHead(head);
            break;

        case 5:
            cout << "\nExiting program. Goodbye!" << endl;
            running = false;
            break;

        default:
            cout << "\nInvalid option. Please try again." << endl;
            break;
        }

        if (running)
        {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
    }

    return 0;
}