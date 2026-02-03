#include <cstddef>
#include <utility>
#include <stdexcept>

template <typename Type>
class Stack{
private:
    Type *data_;
    size_t size_;
    size_t capacity_;

    void validateCapacity(){
        if(size_ < capacity_){
            return;
        }

        if(capacity_ == 0)
            capacity_ = 1;
        else
            capacity_ *= 2;
        
        Type *newData = new Type[capacity_];

        for(size_t i = 0; i < size_; ++i)
            newData[i] = std::move(data_[i]);

        delete[] data_;
        data_ = newData;
    }
public:
    Stack()
        : data_(nullptr), size_(0), capacity_(0) {}

    ~Stack(){
        clear();
    }

    void push(const Type &value){
        validateCapacity();

        data_[size_] = value;

        ++size_;
    }

    void push(Type &&value){
        validateCapacity();

        data_[size_] = std::move(value);

        ++size_;
    }

    Type pop(){
        if(isEmpty())
            throw std::out_of_range("out of ragne");

        Type ret = std::move(data_[--size_]);

        return ret;
    }

    Type &peek(){
        if(isEmpty())
            std::out_of_range("out of range");
        return data_[size_ - 1];
    }

    const Type &peek() const{
        if(isEmpty())
            std::out_of_range("out of range");
        return data_[size_ - 1];
    }

    void clear(){
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }

    bool isEmpty() const{
        return size_ == 0;
    }

    size_t size(){
        return size_;
    }
};