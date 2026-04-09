#ifndef SRC_HPP
#define SRC_HPP

#include <iostream>
#include <cstdio>

template <typename T>
class LinkedList {
protected:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& val = T(), Node* n = nullptr, Node* p = nullptr) : data(val), next(n), prev(p) {}
    };
    Node* head;
    Node* tail;
    int sz;

public:
    LinkedList() : head(nullptr), tail(nullptr), sz(0) {}

    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), sz(0) {
        Node* curr = other.head;
        while (curr) {
            pushBack(curr->data);
            curr = curr->next;
        }
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this == &other) return *this;
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = tail = nullptr;
        sz = 0;
        Node* curr = other.head;
        while (curr) {
            pushBack(curr->data);
            curr = curr->next;
        }
        return *this;
    }

    virtual ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void pushFront(T val) {
        Node* newNode = new Node(val, head, nullptr);
        if (head) {
            head->prev = newNode;
        } else {
            tail = newNode;
        }
        head = newNode;
        sz++;
    }

    void pushBack(T val) {
        Node* newNode = new Node(val, nullptr, tail);
        if (tail) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
        sz++;
    }

    T popFront() {
        if (!head) return T();
        Node* temp = head;
        T val = temp->data;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        sz--;
        return val;
    }

    T popBack() {
        if (!tail) return T();
        Node* temp = tail;
        T val = temp->data;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        sz--;
        return val;
    }

    int size() const {
        return sz;
    }

    void print() const {
        Node* curr = head;
        while (curr) {
            std::cout << curr->data << " ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }

    virtual const char* name() {
        return "LinkedList";
    }

    virtual T peak() {
        return T();
    }

    virtual T pop() {
        return T();
    }

    virtual void push(T val) {
    }
};

template <typename T>
class Stack : public LinkedList<T> {
public:
    virtual const char* name() {
        return "Stack";
    }

    virtual T peak() {
        if (this->head) {
            return this->head->data;
        }
        return T();
    }

    virtual T pop() {
        return this->popFront();
    }

    virtual void push(T val) {
        this->pushFront(val);
    }
};

template <typename T>
class Queue : public LinkedList<T> {
public:
    virtual const char* name() {
        return "Queue";
    }

    virtual T peak() {
        if (this->head) {
            return this->head->data;
        }
        return T();
    }

    virtual T pop() {
        return this->popFront();
    }

    virtual void push(T val) {
        this->pushBack(val);
    }
};

#endif
