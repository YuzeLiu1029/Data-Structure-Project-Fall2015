#ifndef DL_STACK_H
#define DL_STACK_H
#include <iostream>
#include <vector>

using namespace std;

namespace cop4530 
{           
  template <typename T>
  class Stack 
   {
      public:
          Stack();  // zero-argument constructor
          ~Stack(); // destructor
          Stack(const Stack<T>&); //copy constructor
          Stack(Stack<T> &&); //move constructor
          Stack<T>& operator=(const Stack <T>&); //copy assignment operator=
          Stack<T> & operator=(Stack<T> &&); //move assignmeny operator=
          bool empty() const; //returns true if the Stack contains no elements
          void clear(); //delete all elements from the stack
          void push(const T& x); //adds x to stack. copy version
          void push(T && x); //adds x to stack, move version
          void pop(); // removes and discards the most recently elements
          T& top();
          const T& top() const;
          int size() const; //returns the number of the elements
          void print(std::ostream & os, char ofc =' ') const; 

          vector<T> getVec() const;
      private:
          vector<T> stack;
    };  

    //none-member global functions
        
    template <typename T>
    std::ostream& operator<< (std::ostream& os,const Stack<T>& a);
        
    template <typename T>
    bool operator== (const Stack<T>&, const Stack <T>&);
   
    template <typename T>
    bool operator!= (const Stack<T>&, const Stack <T>&);
 
    template <typename T>
    bool operator< (const Stack<T>& a, const Stack <T>& b);

    #include "stack.hpp"
}                    

#endif 
