#pragma once

#include "ArrayList.h"

#include <cstddef>
#include <functional>
#include <utility>

template <typename Type>
class HashSet{
private:
    ArrayList<Type>** list;
    size_t size_;
    size_t numberOfBuckets;

    void validateListSize(){
        const double maxLoad = 0.75;

        if(numberOfBuckets == 0){
            numberOfBuckets = 8;
            list = new ArrayList<Type>*[numberOfBuckets];

            for(size_t i = 0; i < numberOfBuckets; ++i)
                list[i] = new ArrayList<Type>();

            return;
        }
        
        
        if((static_cast<double>(size_) / static_cast<double>(numberOfBuckets)) <= maxLoad)
            return;

        size_t newNumBuckets = numberOfBuckets * 2;
        ArrayList<Type> **newList = new ArrayList<Type>*[newNumBuckets];

        for(size_t i = 0; i < newNumBuckets; ++i){
            newList[i] = new ArrayList<Type>();
        }

        std::hash<Type> hasher;
        for(size_t i = 0; i < numberOfBuckets; ++i) {
            ArrayList<Type>* oldBucket = list[i];

            for(size_t j = 0; j < oldBucket->size(); ++j){
                const Type& element = oldBucket->get(j);
                size_t newBucket = hasher(element) % newNumBuckets;
                newList[newBucket]->add(element);
            }
        }

        for(size_t i = 0; i < numberOfBuckets; ++i)
            delete list[i];

        delete[] list;
        list = newList;
        numberOfBuckets = newNumBuckets;
    }

    bool contains(const Type &value, size_t bucketNum) const{
        ArrayList<Type> *bucket = list[bucketNum];
        for(int i = 0; i < bucket->size(); ++i){
            if(bucket->get(i) == value)
                return true;
        }

        return false;
    }

public:
    HashSet()
        : list(new ArrayList<Type>*[8]), size_(0), numberOfBuckets(8) {
        for(size_t i = 0; i < numberOfBuckets; ++i){
            list[i] = new ArrayList<Type>();
        }
    }

    ~HashSet(){
        clear();
    }

    void add(const Type &value){
        validateListSize();

        std::hash<Type> hasher;
        size_t bucketNum = hasher(value) % numberOfBuckets;
        
        if(contains(value, bucketNum))
            return;

        list[bucketNum]->add(value);

        ++size_;
    }

    void add(Type &&value){
        validateListSize();

        std::hash<Type> hasher;
        size_t bucketNum = hasher(value) % numberOfBuckets;
        
        if(contains(value, bucketNum))
            return;

        list[bucketNum]->add(std::move(value));

        ++size_;
    }

    bool contains(const Type &value) const{
        if(numberOfBuckets == 0)
            return false;

        std::hash<Type> hasher;
        size_t bucketNum = hasher(value) % numberOfBuckets;

        return contains(value, bucketNum);
    }

    void remove(const Type &value){
        if(numberOfBuckets == 0)
            return;
        
        std::hash<Type> hasher;
        size_t bucketNum = hasher(value) % numberOfBuckets;

        ArrayList<Type> *bucket = list[bucketNum];
        for(int i = 0; i < bucket->size(); ++i){
            if(bucket->get(i) == value){
                bucket->remove(i);
                --size_;
                return;
            }
        }

        return;
    }

    bool isEmpty() const{
        return size_ == 0;
    }

    size_t size() const{
        return size_;
    }

    void clear(){
        if(list){
            for(size_t i = 0; i < numberOfBuckets; ++i)
                delete list[i];
            
            delete[] list;
        }

        list = nullptr;
        size_ = 0;
        numberOfBuckets = 0;
    }
};