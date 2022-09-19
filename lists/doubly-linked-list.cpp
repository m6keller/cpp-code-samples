#include "doubly-linked-list.h"

#include <iostream>

DoublyLinkedList::Node::Node(DataType data)
{
    value = data;
    next = NULL;
    prev = NULL;
}

DoublyLinkedList::DoublyLinkedList()
{
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
    Node* cur = head_;
    Node* temp;
    while( cur != NULL )
    {
        temp = cur;
        cur = cur->next;
        delete temp;
    }
    head_ = NULL;
    tail_ = NULL;
}

unsigned int DoublyLinkedList::size() const
{
    return size_;
}

unsigned int DoublyLinkedList::capacity() const
{
    return CAPACITY;
}

bool DoublyLinkedList::empty() const
{
    if( size_ == 0 ) return true;
    return false;
}

bool DoublyLinkedList::full() const
{
    if( size_ == CAPACITY ) return true;
    return false;
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
    if( size_ == 0 ) return 0;
    if( index >= size_ ) index = size_ - 1;
    Node* cur = head_;
    while( index > 0 )
    {
        cur = cur->next;
        index --;
    }
    return cur->value;
}

unsigned int DoublyLinkedList::search(DataType value) const
{
    if( size_ == 0 ) return 0;
    Node* cur = head_;
    unsigned int index = 0;
    while( cur != NULL && cur->value != value )
    {
        index ++;
        cur = cur-> next;
    }
    if( index >= size_ ) return size_;
    return index;
}

void DoublyLinkedList::print() const
{
    Node *cur = head_;
    while( cur != NULL )
    {
        std::cout << cur->value << std::endl;
        cur = cur->next;
    }
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
    if( size_ == 0 ) return NULL;
    if( index >= size_ ) return NULL;
    Node* cur = head_;

    while( index > 0 )
    {
        cur = cur->next;
        index --;
    }
    return cur;
}

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{

    if( full( ) ) return false;
    if( index > size_ ) return false;
    if( index == size_ && size_ != 0 ) return insert_back( value );
    if( index == 0 ) return insert_front( value );
    if( size_ == 0 ) return insert_front( value );

    Node* newNode = new Node( value );
    Node* cur = head_;
    while( index > 1 )
    {
        cur = cur->next;
        index --;
    }
    cur->next->prev = newNode;
    newNode->next = cur->next;
    cur->next = newNode;
    newNode->prev = cur;
    size_ ++;
    return true;
}

bool DoublyLinkedList::insert_front(DataType value)
{
    if( full( ) ) return false;
    Node* cur = new Node( value );
    if( size_ == 0 )
    {
        head_ = cur;
        tail_ = cur;
        size_ ++;
        return true;
    }
    cur->next = head_;
    head_->prev = cur;
    head_ = cur;
    size_ ++;
    return true;
}

bool DoublyLinkedList::insert_back(DataType value)
{
    if( full( ) ) return false;
    if( size_ == 0 ) return insert_front( value );
    Node* cur = new Node( value );
    tail_->next = cur;
    cur->prev = tail_;
    tail_ = cur;
    size_ ++;
    return true;
}

bool DoublyLinkedList::remove(unsigned int index)
{
    if( index >= size_ ) return false;
    if( index == 0 ) return remove_front( );
    if( index == size_ - 1 ) return remove_back( );
    if( empty( ) ) return false;
    Node* cur = head_;
    while( index > 0 )
    {
        cur->prev = cur;
        cur = cur->next;
        index --;
    }
    cur->next->prev = cur->prev;
    cur->prev->next = cur->next;
    delete cur;
    size_ --;
    return true;
}

bool DoublyLinkedList::remove_front()
{
    if( empty() ) return false;
    Node* temp = head_;
    if( size_ == 1 )
    {
        tail_ = NULL;
        head_ = NULL;
        delete temp;
        size_ --;
        return true;
    }
    head_ = head_->next;
    head_->prev = NULL;
    size_ --;
    delete temp;
    return true;
}

bool DoublyLinkedList::remove_back()
{
    if( empty() ) return false;
    if( size_ == 1 ) return remove_front();
    Node* cur = head_;
    while( cur->next != NULL )
    {
        cur = cur->next;
    }
    tail_ = cur->prev;
    tail_->next = NULL;
    delete cur;
    size_ --;
    return true;
}

bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
    if( index >= size_ || size_ == 0 ) return false;
    Node* cur = head_;
    while( index > 0 )
    {
        cur = cur->next;
        index --;
    }
    cur->value = value;
    return true;
}


