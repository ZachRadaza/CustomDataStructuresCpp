#pragma once

#include <cstddef>
#include <stdexcept>

template <typename Type>
class TreeSet {
private:
    struct Node{
        Type value;
        Node *left;
        Node *right;

        Node(const Type& v)
            : value(v), left(nullptr), right(nullptr) {}

        Node(Type&& v)
            : value(std::move(v)), left(nullptr), right(nullptr) {}
    };

    Node *root;
    size_t size_;

    bool add(Node *&node, const Type &value){
        if(!node){
            node = new Node(value);
            return true;
        } else if (value < node->value)
            return add(node->left, value);
        else if (value > node->value)
            return add(node->right, value);

        return false;
    }

    bool add(Node *&node, Type &&value){
        if(!node){
            node = new Node(std::move(value));
            return true;
        } else if(value < node->value)
            return add(node->left, std::move(value));
        else if(value > node->value)
            return add(node->right, std::move(value));

        return false;
    }

    bool contains(Node *node, const Type &value) const{
        if(!node) 
            return false;
        else if(value < node->value) 
            return contains(node->left, value);
        else if(value > node->value) 
            return contains(node->right, value);

        return true;
    }

    Node *findMin(Node *node) const{
        while(node && node->left)
            node = node->left;
        
        return node;
    }

    bool remove(Node *&node, const Type &value){
        if(!node) 
            return false;

        if(value < node->value)
            return remove(node->left, value);
        else if(value > node->value)
            return remove(node->right, value);

        if(!node->left && !node->right){
            delete node;
            node = nullptr;
        } else if(!node->left){
            Node* temp = node;
            node = node->right;
            delete temp;
        } else if(!node->right){
            Node* temp = node;
            node = node->left;
            delete temp;
        } else {
            Node* successor = findMin(node->right);
            node->value = successor->value;
            remove(node->right, successor->value);
        }

        return true;
    }

    void clear(Node* node) {
        if(!node) 
            return;

        clear(node->left);
        clear(node->right);

        delete node;
    }

public:
    TreeSet()
        : root(nullptr), size_(0) {}

    ~TreeSet() {
        clear();
    }

    bool add(const Type &value){
        bool added = add(root, value);
        if(added)
            ++size_;

        return added;
    }

    bool add(Type &&value){
        bool added = add(root, std::move(value));
        if(added) 
            ++size_;

        return added;
    }

    bool contains(const Type& value) const{
        return contains(root, value);
    }

    bool remove(const Type &value){
        bool removed = remove(root, value);
        if(removed)
            --size_;

        return removed;
    }

    bool empty() const{
        return size_ == 0;
    }

    size_t size() const{
        return size_;
    }

    void clear(){
        clear(root);
        root = nullptr;
        size_ = 0;
    }
};