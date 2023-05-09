#include "../includes/stack.hpp"

namespace s21{

template< class T, class Container = std::deque<T> >
Stack::Stack(){

}

template< class T, class Container = std::deque<T> >
Stack::Stack(const Stack& other){
    (void)other;
}

template< class T, class Container = std::deque<T> >
Stack::Stack(Stack&& other){
    (void)other;
}

template< class T, class Container = std::deque<T> >
Stack::~Stack(){

}

template< class T, class Container = std::deque<T> >
Stack& Stack::operator=(const Stack& other){
    (void)other;
    return *this;
}

template< class T, class Container = std::deque<T> >
Stack& Stack::operator=(Stack&& other){
    (void)other;
    return *this;
}

template< class T, class Container = std::deque<T> >
void Stack::push(const value_type& value){
    (void)value;
}

template< class T, class Container = std::deque<T> >
void Stack::push(value_type&& value){
    (void)value;
}

template< class T, class Container = std::deque<T> >
void Stack::pop(){

}

template< class T, class Container = std::deque<T> >
reference Stack::top(){

}

template< class T, class Container = std::deque<T> >
const_reference Stack::top() const{

}


}

