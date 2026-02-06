#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename Type>
class LinkedList{
private:
    struct Node{
        Type value_;
        Node *next;
    };

    Node *head;
    size_t size_; // Length of list

    void addNode(Node *node){
        if(head == nullptr)
            head = node;
        else {
            Node *current = head;
            while(current->next != nullptr){
                current = current->next;
            }

            current->next = node;
        }

        ++size_;
        return;
    }

public:
    LinkedList()
        : head(nullptr), size_(0) {}

    ~LinkedList(){
        clear();
    }

    void add(const Type &value){
        addNode(new Node{ value, nullptr });
    }

    void add(Type &&value){
        addNode(new Node{ std::move(value), nullptr });
    }

    bool remove(size_t index){
        if(index >= size_ || head == nullptr)
            return false;

        if(index == 0){
            Node *toDelete = head;
            head = head->next;

            delete toDelete;
            --size_;
            return true;
        }

        Node *current = head;
        for(size_t i = 0; i + 1 < size_; ++i)
            current = current->next;
        
        Node *toDelete = current->next;
        current->next = toDelete->next;

        delete toDelete;

        --size_;
        return true;
    }

    Type &get(size_t index){
        if(index >= size_)
            throw std::out_of_range("out of range");

        Node *current = head;
        for(size_t i = 0; i < index; ++i){
            current = current->next;
        }

        return current->value_;
    }

    const Type &get(size_t index) const{
        if(index >= size_)
            throw std::out_of_range("out of range");

        Node *current = head;
        for(size_t i = 0; i < index; ++i){
            current = current->next;
        }

        return current->value_;
    }

    size_t size(){
        return size_;
    }

    bool contains(const Type &value) const{
        Node *current = head;
        while(current != nullptr){
            if(value == current->value_)
                return true;
            
            current = current->next;
        }

        return false;
    }

    void clear(){
        while(head != nullptr){
            Node *toDelete = head;
            head = head->next;
            delete toDelete;
        }

        size_ = 0;
    }

    bool isEmpty() const{
        return head == nullptr;
    }
};