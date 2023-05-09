#pragma once

#include <deque>

namespace s21{

template< class T, class Container = std::deque<T> >
class Queue{
public:
    using container_type    = Container;
    using value_type	    = Container::value_type;
    using size_type	        = Container::size_type;
    using reference	        = Container::reference;
    using const_reference	= Container::const_reference;

    Queue();
    Queue(const Queue& other);
    Queue(Queue&& other);
    ~Queue();

    Queue& operator=(const Queue& other);
    Queue& operator=(Queue&& other);

    void push(const value_type& value);
    
    void push(value_type&& value);

    void pop();

    reference front();

    const_reference front() const;

private:

};

}
