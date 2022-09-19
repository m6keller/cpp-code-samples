#include "dynamic-stack.h"
#include <iostream>

const DynamicStack::StackItem DynamicStack::EMPTY_STACK = -999;

DynamicStack::DynamicStack()
{
    capacity_ = init_capacity_ = 16;
    size_ = 0;
    items_ = new StackItem[ init_capacity_ ];
}

DynamicStack::DynamicStack(unsigned int capacity)
{
    init_capacity_ = capacity_ = capacity;
    size_ = 0;
    items_ = new StackItem[ capacity ];
}

DynamicStack::~DynamicStack()
{
    delete[] items_;
}

bool DynamicStack::empty() const
{
    if( size_ == 0 ) return true;
    return false;
}

int DynamicStack::size() const
{
    return size_;
}

void DynamicStack::push(StackItem value)
{
    if( size_ == capacity_ )
    {
        capacity_ = capacity_ * 2;
        StackItem *temp = items_;
        items_ = new StackItem[ capacity_ ];
        for( int i = 0; i < size_ ; i ++ ) items_[ i ] = temp[ i ];
        delete[] temp;
    }
    items_[size_] = value;
    size_ ++;
}

DynamicStack::StackItem DynamicStack::pop()
{
    if( empty() ) return EMPTY_STACK;
    StackItem ret_val = items_[size_ - 1];
    items_[size_ - 1] = NULL;
    size_--;
    if( size_ <= capacity_ / 4 && capacity_ / 2 >= init_capacity_ )
    {
        capacity_ = capacity_ / 2;
        StackItem *temp = items_;
        items_ = new StackItem[ capacity_ ];
        for( int i = 0; i < size_ ; i ++ ) items_[ i ] = temp[ i ];
        delete[] temp;
    }
    return ret_val;
}

DynamicStack::StackItem DynamicStack::peek() const
{
    if( empty () ) return EMPTY_STACK;
    return items_[size_ - 1];
}

void DynamicStack::print() const
{
    for( int i = 0; i < size_; i ++ )
    {
        std::cout << items_[i] << "\n" << std::endl;
    }
}
