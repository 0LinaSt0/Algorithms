#include "../includes/queue.hpp"

namespace s21{
    
template< class T, class Container = std::deque<T> >
Queue::Queue(){

}

template< class T, class Container = std::deque<T> >
Queue::Queue(const Queue& other){
    (void)other;
}

template< class T, class Container = std::deque<T> >
Queue::Queue(Queue&& other){
    (void)other;
}

template< class T, class Container = std::deque<T> >
Queue::~Queue(){

}

template< class T, class Container = std::deque<T> >
Queue& Queue::operator=(const Queue& other){
    (void)other;
    return *this;
}

template< class T, class Container = std::deque<T> >
Queue& Queue::operator=(Queue&& other){
    (void)other;
    return *this;
}

template< class T, class Container = std::deque<T> >
void Queue::push(const value_type& value){

}

template< class T, class Container = std::deque<T> >
void Queue::push(value_type&& value){

}

template< class T, class Container = std::deque<T> >
void Queue::pop(){

}

template< class T, class Container = std::deque<T> >
reference Queue::front(){

}

template< class T, class Container = std::deque<T> >
const_reference Queue::front() const{
    
}

}
