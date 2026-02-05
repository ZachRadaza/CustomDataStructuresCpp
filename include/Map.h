#pragma once

#include "ArrayList.h"

#include <functional>
#include <cstddef>
#include <utility>
#include <stdexcept>

template <typename Key, typename Value>
class Map{
private:
    struct keyValuePair{
        Key key;
        Value value;
    };

    ArrayList<keyValuePair> **list;
    size_t listLength;
    size_t size_;

    void validateCapacity(){
        if(listLength == 0){
            listLength = 8;
            list = new ArrayList<keyValuePair>*[listLength];

            for(size_t i = 0; i < listLength; ++i){
                list[i] = new ArrayList<keyValuePair>();
            }

            return;
        }

        const double maxLoad = 0.75;
        const double load = static_cast<double>(size_) / static_cast<double>(listLength);

        if(load <= maxLoad)
            return;

        size_t newLength = listLength * 2;
        ArrayList<keyValuePair> **newList = new ArrayList<keyValuePair>*[newLength];
        std::hash<Key> hasher;

        for(size_t i = 0; i < listLength; ++i){
            newList[i] = new ArrayList<keyValuePair>();
        }

        for(size_t i = 0; i < newLength; ++i){
            ArrayList<keyValuePair> *old = list[i];

            for(size_t j = 0; j < old->size(); ++j){
                const keyValuePair &element = old->get(j);
                size_t index = hasher(element.key) % newLength;
                newList[i]->add(element);
            }
        }

        for(size_t i = 0; i < listLength; ++i)
            delete list[i];
        

        delete[] list;
        list = newList;
        listLength = newLength;
    }

    int containsKey(const size_t index, const Key &key) const{
        for(size_t i = 0; i < list[index]->size(); ++i){
            if(list[index]->get(i).key == key)
                return i;
        }

        return -1;
    }

public:
    Map()
        : list(new ArrayList<keyValuePair>*[8]), size_(0), listLength(8){

        for(size_t i = 0; i < listLength; ++i){
            list[i] = new ArrayList<keyValuePair>();
        }
    }

    ~Map(){
        clear();
    }

    void insert(const Key &key, const Value &val){
        validateCapacity();

        std::hash<Key> hasher;
        const size_t index = hasher(key) % listLength;

        if(containsKey(index, key) > -1)
            return;

        list[index]->add({ key, val });

        ++size_;
    }

    void insert(const Key &key, const Value &&val){
        validateCapacity();

        std::hash<Key> hasher;
        const size_t index = hasher(key) % listLength;

        if(containsKey(index, key) > -1)
            return;

        list[index]->add({ key, std::move(val) });

        ++size_;
    }


    Value &find(const Key &key){
        std::hash<Key> hasher;
        const size_t index = hasher(key) % listLength;

        int indexKey = containsKey(index, key);

        if(indexKey > -1)
            return list[index]->get(indexKey).value;
        else
            throw std::out_of_range("Key does not exist");
    }

    const Value &find(const Key &key) const{
        std::hash<Key> hasher;
        const size_t index = hasher(key) % listLength;

        int indexKey = containsKey(index, key);

        if(indexKey > -1)
            return list[index]->get(indexKey).value;
        else
            throw std::out_of_range("Key does not exist");
    }

    bool contains(const Key &key) const{
        std::hash<Key> hasher;
        const size_t index = hasher(key) % listLength;

        return containsKey(index, key) > -1;
    }

    bool erase(const Key &key){
        std::hash<Key> hasher;
        const size_t index = hasher(key) % listLength;

        int indexKey = containsKey(index, key);

        if(indexKey > -1){
            list[index]->remove(indexKey);
            --size_;
            return true;
        } else 
            throw false;
    }

    bool isEmpty() const{
        return size_ == 0;
    }

    size_t size() const{
        return size_;
    }

    void clear(){

    }
};