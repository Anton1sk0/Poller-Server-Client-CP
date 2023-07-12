#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <iomanip>
#include <string>
#include <mutex>

using namespace std;

template <typename T, typename U>
struct Node {
    T key;
    U data;
    Node<T, U> *next;

    Node(T key, U data, Node<T,U> *next) : key(key), data(data), next(next) {
    }
};

template <typename T, typename U>
class List {
private:
    Node<T, U> *head;
    int count;
    mutex guardmutex;

public:

    List() : head(nullptr), count(0) {
    }

    Node<T,U> * getFirst() {
        return head;
    }

    virtual ~List() {
        clear();
    }

    void print(ostream & out = cout) {
        Node<T,U> *current = head;

        while (current != NULL) {
            out << setw(40) << left << current->key << setw(20) << left << current->data << endl;
            
            current = current->next;
        }

        if (head == nullptr) {
            out << "list is empty " << endl;
        }
    }
      
    string Tostring() {
        Node<T,U> *current = head;
        string result;
        while (current != NULL) {
            result += "Name: " + current->key + ", Party: " + current->data + "\n";
            current = current->next;
        }

        if (head == nullptr) {
            cout << "list is empty " << endl;
        }
        return result;
    }

    int getCount() {
        return count;
    }

    U search(T key) {
        lock_guard<mutex> lock(guardmutex);
        Node<T,U> *current = head;
        
        while (current != nullptr) {
            if (current->key == key) {
                return current->data;
            }
            current = current->next;
        }

        return U();
    }

    U searchByPosition(int position) {
        Node<T,U> *current = head;

        while (current != nullptr) {
            if (position == 0) {
                return current->data;
            }
            current = current->next;
            position--;
        }

        return "";
    }

    void add(T key, U data) {
        lock_guard<mutex> lock(guardmutex);
        Node<T,U> *newNode = new Node<T,U>(key, data, nullptr);

        if (head == nullptr) {
            head = newNode;
        } else {
            Node<T,U> *current = head;

            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        count++;
    }

    void add(T key) {
        lock_guard<mutex> lock(guardmutex);
        add(key, "");
    }

    void removeFirst() {
        if (head == nullptr) {
            printf("u trying to remove the first ellement of an empty list \n");
            return;
        }

        Node<T,U> *temp = head;
        head = head->next;
        delete temp;

        count--;
    }

    void remove(T key) {
        lock_guard<mutex> lock(guardmutex);
        if (head == nullptr) {
            return;
        }

        Node<T,U> *current = head;
        Node<T,U> *previous = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (previous == nullptr) {
                    // remove first node
                    head = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;

                count--;
                return;
            }
            previous = current;
            current = current->next;
        }

        count--;
    }

    T* keysToArray() {
        int n = this->count;

        T * array = new T[n];

        Node<T,U> *current = head;

        int i = 0;

        while (current != nullptr) {
            array[i++] = current->key;
            current = current->next;
        }

        return array;
    }

    T* dataToArray() {
        int n = this->count;

        T * array = new T[n];

        Node<T,U> *current = head;

        int i = 0;

        while (current != nullptr) {
            array[i++] = current->data;
            current = current->next;
        }

        return array;
    }

    void append(List<T,U>* other) {
        lock_guard<mutex> lock(guardmutex);
        if (other == nullptr) {
            return;
        }
        if (this->head == nullptr) {
            this->head = other->head;
        } else {
            Node<T,U>* current = this->head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = other->head;
        }
        this->count += other->count;
        other->head = nullptr;
        delete other;
    }

    void clear() {
        Node<T,U> *current = head;
        while (current != nullptr) {
            Node<T,U> *next = current->next;
            delete current;
            current = next;
        }

        this->head = nullptr;
    }
};

#endif /* LIST_H */

