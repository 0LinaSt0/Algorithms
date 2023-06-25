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

    Queue() = default;
    Queue(const Queue& other);
    Queue(Queue&& other);
    ~Queue();

    Queue& operator=(const Queue& other);
    Queue& operator=(Queue&& other);

    // Adding an element by reference
    void push(const value_type& value);

    // Adding an element by r-value reference
    void push(value_type&& value);

    /**
     * Getting an element from the queue
     * followed by its removal from the queue
     */
    void pop();

    /**
     * Accessing the first element
     * @return reference to the first element
     */
    reference front();

    /**
     * Accessing the first element
     * @return const reference to the first element
     */
    const_reference front() const;

     /**
     * @return the number of elements
     */
    size_type size() const;

private:
    container_type qct_;
};

}

#include "../srcs/queue.tpp"
