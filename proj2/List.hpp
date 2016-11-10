///////////////////////COP4530 Data Structure////////////////////////
///////////////////////Project 2: Doubly-Linked List Container///////
///////////////////////Yuze Liu//////////////////////////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//Since the textbook covers some of the function in example code.////
//I just use them directly.//////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
#include <iostream>
using namespace std;

//nested const_iterator class

//Default zero-parameter constructor
template<typename T>
List<T>::const_iterator::const_iterator() : current{ nullptr }
{}

//operator*() to return element
template<typename T>
const T & List<T>::const_iterator::operator*() const
{return retrieve(); }

// increment/decrement operators
template<typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator++()
{
    current = current->next;
    return *this;
}

template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
    const_iterator old = *this;
    ++(*this);
    return old;
}

template<typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator--()
{
    return current = current->prev;
}

template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int)
{
    const_iterator old = *this;
    --(*this);
    return old;
}

// comparison operators
template<typename T>
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const
{return current == rhs.current;}

template<typename T>
bool List<T>::const_iterator::operator!=(const const_iterator &rhs) const
{return !(*this == rhs);}

template<typename T>
List<T>::const_iterator::const_iterator(Node *p)
{
    current = p;
}

template<typename T>
T & List<T>::const_iterator::retrieve() const
{return current->data;}

//Iterators
template<typename T>
List<T>::iterator::iterator()
{}

template<typename T>
T & List<T>::iterator::operator*()
{
    return const_iterator::retrieve();
}

template<typename T>
const T & List<T>::iterator::operator*() const
{
    return const_iterator::retrieve();
}

template<typename T>
typename List<T>::iterator & List<T>::iterator::operator++()
{
    this->current = this->current->next;
    return *this;
}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
    iterator old = *this;
    ++(*this);
    return old;
}

template<typename T>
typename List<T>::iterator & List<T>::iterator::operator--()
{
    this->current = this->current->prev;
    return *this;
}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator--(int)
{
    iterator old = *this;
    --(*this);
    return old;
}

template<typename T>
List<T>::iterator::iterator(Node *p)
{
   this->current = p;

}

// List
template <typename T>
List<T>::List()
{
    init();
}

template <typename T>
List<T>::List(const List &rhs)
{
    init();
    for (auto & x : rhs)
    {
        push_back(x);
    }
}

template <typename T>
List<T>::List(List && rhs)
: theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
{
    rhs.theSize = 0;
    rhs.head = rhs.tail = nullptr;
}

template <typename T>
List<T>::List(int num, const T& val)
{
    init();
    for (int i=0; i <num; ++i)
        insert( begin(), val);
}

template <typename T>
List<T>::List(const_iterator start, const_iterator end)
{
    init();
    for (auto i=start; i != end; ++i)
        push_back(*i);
}
                      

template <typename T>
List<T>::~List()
{
    clear();
    delete head;
    delete tail;
}

template <typename T>
const typename List<T>::List& List<T>::operator=(const List &rhs)
{
    List copy = rhs;
    swap(*this, copy);
    return *this;
}

template <typename T>
typename List<T>::List & List<T>::operator=(List && rhs)
{
    swap(theSize, rhs.theSize);
    swap(head, rhs.head);
    swap(tail,rhs.tail);
    return *this;
}

template <typename T>
void List<T>::init()
{
   theSize = 0;
   head = new Node;
   tail = new Node;
   head->next = tail;
   tail->prev = head;
}

template <typename T>
int List<T>::size() const
{  return theSize;}

template <typename T>
bool List<T>::empty() const
{  return size() == 0;}

template <typename T>
void List<T>::clear()
{
    while (!empty() ) 
    {
        pop_front();
    }
}


template <typename T>
void List<T>::reverse()
{
    Node * Left = head;
    Node * Right = tail;
    Node * currLeft = head;
    Node * currRight = tail;
    
    Left = Left->next;
    Right = Right->prev;
    
    for (int i=0; i< size()/2; ++i)
    {
        currLeft->next = Right;
        Right = Right->prev;
        currLeft->next->prev = currLeft;
        
        currRight->prev = Left;
        Left = Left->next;
        currRight->prev->next = currRight;

        currLeft = currLeft->next;
        currRight = currRight->prev;
    }
    if (Left == Right) 
    {
        currRight->prev = Left;
        currLeft->next = Left;
                
        Left->prev = currLeft;
        Left->next = currRight;
    }
    else
    {            
        currRight->prev = currLeft;
        currLeft->next = currRight;
    }
}

template <typename T>
T & List<T>::front()
{
    return *begin();
}


template <typename T>
const T& List<T>::front() const
{
    return *begin();
}


template <typename T>
T & List<T>::back()
{
    return *--end();
}


template <typename T>
const T & List<T>::back() const 
{
    return *--end();
}
   
template <typename T>
void List<T>::push_front(const T & val)
{
    insert( begin(), val);
}

template <typename T>
void List<T>::push_front(T && val)
{
    insert( begin(), move(val));
}

template <typename T>
void List<T>::push_back(const T & val)
{
    insert( end(), val);
}

template <typename T>
void List<T>::push_back(T && val)
{
    insert( end(), move(val));
}

template <typename T>
void List<T>::pop_front()
{
    erase( begin() );
}

template <typename T>
void List<T>::pop_back()
{
    erase( --end() );
}

template <typename T>
void List<T>::remove(const T &val)
{
    for(iterator i=begin(); i != end(); ++i)
        if (*i == val)
            erase(i); 
}

template <typename T>
void List<T>::print(std::ostream& os, char ofc) const 
{
    for (const_iterator x= begin(); x != end(); ++x)
        cout << *x << ofc;
}

template <typename T>
typename List<T>::iterator List<T>::begin()
{ return iterator( head->next );}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const
{
    return iterator( head->next );
}

template <typename T>
typename List<T>::iterator List<T>::end()
{ return iterator( tail);}

template <typename T>
typename List<T>::const_iterator List<T>::end() const 
{ return iterator( tail);}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val)
{
    Node *p = itr.current;
    ++theSize;
    return iterator( p->prev = p->prev->next = new Node (val, p->prev, p) );
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T && val)
{
    Node *p = itr.current;
    ++theSize;
    return iterator( p->prev = p->prev->next = new Node ( move(val), p->prev, p) );

}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator itr)
{
    Node * m = itr.current;
    iterator returnVal(m->next);
    m->prev->next = m->next;
    m->next->prev = m->prev;
    delete m;
    --theSize;
    return returnVal;
}


template <typename T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end)
{
    for( iterator itr = start; itr != end;)
        itr = erase( itr);
    return end;
}

// overloading comparison operators
template <typename T>
bool operator==(const List<T> & lhs, const List<T> &rhs)
{
    if (lhs.size() != rhs.size())
        return false;
    else
    {
        auto left = lhs.begin();
        for (auto right = rhs.begin(); right != rhs.end(); ++right)
        {
            if (*right != *left)
                return false;
            ++left;
        }
        return true;
    }
}

template <typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs)
{
    if (lhs.size() != rhs.size())
        return true;
    else
    {
        auto left = lhs.begin();
        for (auto right = rhs.begin(); right != rhs.end(); ++right)
        {
            if (*right != *left)
                return true;
            ++left;
        }
        return false;
    }

}

// overloading output operator
template <typename T>
std::ostream & operator<<(std::ostream &os, const List<T> &l)
{
    l.print(os, ' ');
    return os;
}
