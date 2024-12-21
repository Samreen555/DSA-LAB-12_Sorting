#include <iostream>
#include<string>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <iomanip>  // for controlling the output format

using namespace std;
using namespace std::chrono;

// Node structure for the linked list
struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

// Linked List class
class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    // Add a new node at the end
    void append(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Bubble Sort for linked list
    void bubbleSort() {
        if (!head) return;
        bool swapped;
        do {
            swapped = false;
            Node* temp = head;
            while (temp && temp->next) {
                if (temp->data > temp->next->data) {
                    swap(temp->data, temp->next->data);
                    swapped = true;
                }
                temp = temp->next;
            }
        } while (swapped);
    }

    // Selection Sort for linked list
    void selectionSort() {
        Node* temp = head;
        while (temp) {
            Node* minNode = temp;
            Node* nextNode = temp->next;
            while (nextNode) {
                if (nextNode->data < minNode->data) {
                    minNode = nextNode;
                }
                nextNode = nextNode->next;
            }
            swap(temp->data, minNode->data);
            temp = temp->next;
        }
    }

    // Binary Insertion Sort for linked list
    void binaryInsertionSort() {
        if (!head || !head->next) return;
        Node* sorted = nullptr;
        Node* current = head;
        while (current) {
            Node* next = current->next;
            if (!sorted || sorted->data >= current->data) {
                current->next = sorted;
                sorted = current;
            }
            else {
                Node* temp = sorted;
                while (temp->next && temp->next->data < current->data) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
            current = next;
        }
        head = sorted;
    }

    // Print list for verification
    void printList() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Generate a random list
    static LinkedList generateRandomList(int size) {
        LinkedList list;
        for (int i = 0; i < size; ++i) {
            list.append(rand() % 1000);  // Random numbers between 0 and 999
        }
        return list;
    }
};

int main() {
    srand(time(0)); // Initialize random number generator

    // Array of ranges for random number generation
    int ranges[] = { 10, 100, 1000, 10000 };

    // Table header with improved alignment using setw
    cout << "---------------------------------------------------------------\n";
    cout << "| " << setw(15) << "Range (1-x)"
        << "| " << setw(15) << "Bubble Sort"
        << "| " << setw(15) << "Selection Sort"
        << "| " << setw(22) << "Binary Insertion Sort" << "|\n";
    cout << "---------------------------------------------------------------\n";

    // Loop for each data range
    for (int range : ranges) {
        LinkedList list1 = LinkedList::generateRandomList(100, range);
        LinkedList list2 = list1;
        LinkedList list3 = list1;

        // Measure time for Bubble Sort
        auto start = high_resolution_clock::now();
        list1.bubbleSort();
        auto end = high_resolution_clock::now();
        duration<double> bubbleTime = duration_cast<duration<double>>(end - start);

        // Measure time for Selection Sort
        start = high_resolution_clock::now();
        list2.selectionSort();
        end = high_resolution_clock::now();
        duration<double> selectionTime = duration_cast<duration<double>>(end - start);

        // Measure time for Binary Insertion Sort
        start = high_resolution_clock::now();
        list3.binaryInsertionSort();
        end = high_resolution_clock::now();
        duration<double> binaryTime = duration_cast<duration<double>>(end - start);

        // Output the table row with improved formatting
        cout << "| " << setw(15) << "1-" + to_string(range)
            << "| " << setw(15) << fixed << setprecision(8) << bubbleTime.count()
            << "| " << setw(15) << fixed << setprecision(8) << selectionTime.count()
            << "| " << setw(22) << fixed << setprecision(8) << binaryTime.count() << " |\n";
    }

    cout << "-------------------------------------------------------------------------------\n";
    return 0;
}

