#include "circular-queue.h"
#include <iostream>
using namespace std;

const CircularQueue::QueueItem CircularQueue::EMPTY_QUEUE = -999;

CircularQueue::CircularQueue()
{
    capacity_ = 16;
    items_ = new QueueItem[ capacity_ ];
    head_ = 0;
    tail_ = 0;
    size_ = 0;
}

CircularQueue::CircularQueue(unsigned int capacity)
{
    items_ = new QueueItem[ capacity ];
    head_ = 0;
    tail_ = 0;
    capacity_ = capacity;
    size_ = 0;
}

CircularQueue::~CircularQueue()
{
    delete[] items_;
    items_ = nullptr;
}

bool CircularQueue::empty() const
{
    if( size_ == 0 ) return true;
    return false;
}

bool CircularQueue::full() const
{
    if( size_ == capacity_ ) return true;
    else return false;
}

int CircularQueue::size() const
{
    return size_;
}

bool CircularQueue::enqueue(QueueItem value)
{
    if( full( ) ) return false;
    items_[ tail_ ] = value;
    tail_ = ( tail_ + 1 ) % capacity_;
    size_ ++;
    return true;
}

CircularQueue::QueueItem CircularQueue::dequeue()
{
    if( empty() ) return EMPTY_QUEUE;
    QueueItem ret_val = items_[ head_ ];
    head_ = ( head_ + 1 ) % capacity_;
    size_ --;
    return ret_val;
}

CircularQueue::QueueItem CircularQueue::peek() const
{
    if( empty() ) return EMPTY_QUEUE;
    return items_[ head_ ];
}

void CircularQueue::print() const
{
    for( int i = head_; i < size_ + head_; i ++ )
        cout << items_[ i % 8 ] << endl;
}