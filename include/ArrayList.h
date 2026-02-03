#include <cstddef>
#include <utility>
#include <stdexcept>

template <typename Type>
class ArrayList{
private:
    Type *data_;        // Pointer to first element of array
    size_t size_;       // size_ of ArrayList
    size_t capacity_;   // size_ Allocated

    void validateSize(){
        if(size_ < capacity_) 
            return;

        size_t newCapacity = 0;
        if(capacity_ == 0)
            newCapacity = 2;
        else
            newCapacity = capacity_ * 2;

        Type *newData = new Type[newCapacity];
        for(size_t i = 0; i < size_; ++i)
            newData[i] = std::move(data_[i]);
        
        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

public:
    ArrayList()
        : data_(nullptr), size_(0), capacity_(0) {}

    ~ArrayList(){
        clear();
    }

    // copies object into data
    // ex. std::string s = "adfasdf";
    // ex. foo.add(s);
    void add(const Type &value){
        validateSize();
        data_[size_++] = value;
    }

    // moves object into data
    // ex. foo.add("asdfadsf");
    void add(Type &&value){
        validateSize();
        data_[size_++] = std::move(value);
    }

    void add(const Type &value, size_t index){
        validateSize();

        for(size_t i = index + 1; i < size_; ++i){
            data_[i] = data_[i - 1];
        }

        data_[index] = value;
        ++size_;
    }

    void add(Type &&value, size_t index){
        validateSize();

        for(size_t i = index + 1; i < size_; ++i){
            data_[i] = data_[i - 1];
        }

        data_[index] = std::move(value);
        ++size_;
    }

    bool remove(size_t index){
        if(index >= size_)
            return false;

        for(size_t i = index; i < size_ - 1; ++i)
            data_[i] = std::move(data_[i + 1]);

        --size_;
        return true;
    }
    
    Type &get(size_t index){
        if(index >= size_)
            throw std::out_of_range("Out of Range");

        return data_[index];
    }

    const Type &get(size_t index) const{
        if(index >= size_)
            throw std::out_of_range("Out of Range");

        return data_[index];
    }

    bool contains(const Type &value) const{
        for(size_t i = 0; i < size_; ++i){
            if(data_[i] == value)
                return true;
        }

        return false;
    }

    int find(const Type &value) const{
        for(size_t i = 0; i < size_; ++i){
            if(data_[i] == value)
                return static_cast<int>(i);
        }

        return -1;
    }

    size_t size(){
        return size_;
    }

    bool isEmpty() const{
        return size_ == 0;
    }

    void clear(){
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }
};