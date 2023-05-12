#pragma once

#include <iostream>
#include <deque>

namespace s21{

template< class T, class Container = std::deque<T> >
class Queue{
public:
    using container_type    = Container;
    using value_type	    = typename container_type::value_type;
    using size_type	        = typename container_type::size_type;
    using reference	        = typename container_type::reference;
    using const_reference	= typename container_type::const_reference;

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

    size_type size() const;

private:
    container_type qct_;
};

}

#include "../srcs/queue.tpp"
