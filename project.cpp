#include <iostream>

using namespace std;


struct Node {
    double data;
    Node* next;
    Node(double value) : data(value), next(NULL) {}
};


void displayList(Node* head) {
    Node* current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}


void append(Node*& head, Node*& tail, double value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
}

// Merge Sort Recursive Functions
Node* merge(Node* left, Node* right, int& comparisons, int& swaps) {
    Node dummy(0);
    Node* tail = &dummy;

    while (left && right) {
        comparisons++;
        cout << "Comparing " << left->data << " and " << right->data << endl;

        if (left->data <= right->data) {
            cout << "No swap needed.\n";
            tail->next = left;
            left = left->next;
        } else {
            cout << "Swapping " << left->data << " and " << right->data << endl;
            tail->next = right;
            right = right->next;
            swaps++;
        }
        tail = tail->next;
        displayList(dummy.next);
    }

    if (left) tail->next = left;
    if (right) tail->next = right;

    return dummy.next;
}

Node* mergeSortHelper(Node* head, int& comparisons, int& swaps) {
    if (!head || !head->next) return head;

    Node* slow = head;
    Node* fast = head->next;

    
    cout << "Dividing the list:\n";
    displayList(head);

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* right = slow->next;
    slow->next = NULL;

    cout << "Left part before merge:\n";
    displayList(head);
    cout << "Right part before merge:\n";
    displayList(right);

    Node* left = mergeSortHelper(head, comparisons, swaps);
    right = mergeSortHelper(right, comparisons, swaps);

    return merge(left, right, comparisons, swaps);
}

// Merge Sort Visualization 
void mergeSortVisualizer(Node*& head) {
    cout << "\nStarting Merge Sort Visualization...\n" << endl;

    int comparisons = 0, swaps = 0;
    head = mergeSortHelper(head, comparisons, swaps);

    cout << "Merge Sort Completed.\n";
    cout << "Total comparisons: " << comparisons << ", Total swaps: " << swaps << endl;
}


// Insertion Sort Visualization
void insertionSortVisualizer(Node* head) {
    cout << "\nStarting Insertion Sort Visualization...\n" << endl;
    if (!head) return;

    Node* sorted = NULL;  
    Node* current = head;

    int pass = 0;  

    while (current) {
        Node* next = current->next;
        Node* prev = NULL, * temp = sorted;

        pass++;
        cout << "\nPass " << pass << ":\n";
        cout << "Inserting element " << current->data << " into the sorted part.\n";

        
        while (temp && temp->data < current->data) {
            prev = temp;
            temp = temp->next;
        }

        
        if (prev == NULL) {
            current->next = sorted;
            sorted = current;
        } else {
            current->next = prev->next;
            prev->next = current;
        }

        
        current = next;

        
        cout << "Current sorted list: ";
        displayList(sorted);
    }

    
    head = sorted;
    cout << "\nInsertion Sort Completed.\n";
}


        
        
        
// Selection Sort Visualization
void selectionSortVisualizer(Node* head) {
    cout << "\nStarting Selection Sort Visualization...\n" << endl;
    if (!head) return;

    Node* current = head;
    int pass = 0;  

    while (current) {
        Node* min = current;
        Node* nextNode = current->next;

        
        while (nextNode) {
            if (nextNode->data < min->data) {
                min = nextNode;
            }
            nextNode = nextNode->next;
        }

        
        if (min != current) {
            pass++;
            cout << "\nPass " << pass << ":\n";
            cout << "Start with element " << current->data << ".\n";
            cout << "Look for the smallest element in the remaining part of the list.\n";
            cout << "Found smallest element " << min->data << ".\n";
            cout << "Swapping " << current->data << " and " << min->data << ".\n";

            swap(current->data, min->data);
            displayList(head);  

            cout << "After Pass " << pass << ": ";
            displayList(head);  
        }

        current = current->next;
    }

    cout << "\nSelection Sort Completed.\n";
}


// Bubble Sort Visualization 
void bubbleSortVisualizer(Node* head) {
    cout << "\nStarting Bubble Sort Visualization...\n" << endl;
    if (!head) return;

    bool swapped;
    int pass = 0;

    do {
        pass++;
        swapped = false;
        Node* current = head;

        cout << "Pass " << pass << ":\n";
        while (current && current->next) {
            cout << "Comparing " << current->data << " and " << current->next->data << endl;
            if (current->data > current->next->data) {
                cout << "Swapping " << current->data << " and " << current->next->data << endl;
                swap(current->data, current->next->data);
                swapped = true;
                displayList(head);
            } else {
                cout << "No swap needed.\n";
            }
            current = current->next;
        }
        if (swapped) {
            cout << "After Pass " << pass << ": ";
            displayList(head);
        } else {
            cout << "List is sorted. Exiting early.\n";
        }
    } while (swapped);

    cout << "Bubble Sort Completed.\n";
}

// Input Validation Functions
double getValidNumber() {
    double value;
    while (true) {
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a valid number: ";
        } else {
            cin.ignore(10000, '\n');
            return value;
        }
    }
}

int getValidChoice(int min, int max) {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail() || value < min || value > max) {
            cin.clear();
            cin.ignore(10000, '\n');
            if (min == 2) {
                cout << "Invalid input. Please enter a number greater than or equal to 2: ";
            } else {
                cout << "Invalid input. Please enter a number between " << min << " and " << max << ": ";
            }
        } else {
            cin.ignore(10000, '\n');
            return value;
        }
    }
}

string getYesNoInput() {
    string response;
    while (true) {
        cin >> response;
        if (response == "y" || response == "n") {
            return response;
        }
        cout << "Invalid input. Please enter 'y' or 'n': ";
    }
}


int main() {
    do {
        Node* head = NULL;
        Node* tail = NULL;
        int n, choice;

        cout << "Enter number of elements: ";
        n = getValidChoice(2, 1000000);

        cout << "Enter the elements:\n";
        for (int i = 0; i < n; i++) {
            cout << "Element " << i + 1 << ": ";
            double element = getValidNumber();
            append(head, tail, element);
        }

        cout << "\nChoose Sorting Algorithm for Visualization:\n";
        cout << "1. Bubble Sort\n2. Merge Sort\n3. Insertion Sort\n4. Selection Sort\n";
        cout << "Enter choice: ";
        choice = getValidChoice(1, 4);

        switch (choice) {
            case 1:
                bubbleSortVisualizer(head);
                break;
            case 2:
                mergeSortVisualizer(head);
                break;
            case 3:
                insertionSortVisualizer(head);
                break;
            case 4:
                selectionSortVisualizer(head);
                break;
        }

        cout << "\nSorted Linked List: ";
        displayList(head);

        cout << "\nDo you want to sort another list? (y/n): ";
        if (getYesNoInput() == "n") break;

    } while (true);

    cout << "Exiting program. Goodbye!" << endl;
    return 0;
}

