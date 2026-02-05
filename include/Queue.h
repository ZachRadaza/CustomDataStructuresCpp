#pragma once

#include <cstddef>
#include <utility>
#include <stdexcept>

template <typename Type>
class Queue{
private:
    struct Node{
        Type value_;
        Node *next;
    };

    Node *head;
    Node *tail;
    size_t size_;

public:
    Queue()
        : head(nullptr), tail(nullptr), size_(0) {}

    ~Queue(){
        clear();
    }

    void enqueue(const Type &value){
        Node *newNode = new Node{ value, nullptr };

        if(tail == nullptr){
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        ++size_;
    }

    void enqueue(Type &&value){
        Node *newNode = new Node{ std::move(value), nullptr };

        if(tail == nullptr)
            head = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
        ++size_;
    }

    void dequeue(){
        if(head == nullptr)
            throw std::out_of_range("out of range");

        Node *toDelete = head;
        head = head->next;

        delete toDelete;

        --size_;
        if(head == nullptr)
            tail = nullptr;
    }

    Type &front(){
        return head->value_;
    }

    const Type &front() const{
        if(head == nullptr)
            throw std::out_of_range("out of range");

        return head->value_;
    }

    bool isEmpty() const{
        return head == nullptr;
    }

    size_t size() const{
        return size_;
    }

    void clear(){
        while(head != nullptr){
            Node *toDelete = head;
            head = head->next;
            delete toDelete;
        }

        tail = nullptr;
        size_ = 0;
    }
};