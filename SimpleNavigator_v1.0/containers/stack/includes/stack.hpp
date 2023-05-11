#pragma once

#include <deque>

namespace s21{

template<class T, class Container = std::deque<T>>
class Stack{
public:
    using container_type    = Container;
    using value_type        = typename container_type::value_type;
    using size_type         = typename container_type::size_type;
    using reference         = typename container_type::reference;
    using const_reference   = typename container_type::const_reference;

    Stack();
    Stack(const Stack& other);
    Stack(Stack&& other);
    ~Stack();

    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other);

    void push(const value_type& value);
    
    void push(value_type&& value);

    value_type pop();

    reference top();

    const_reference top() const;

private:
    container_type innerContainer_;

};

}

#include "../srcs/stack.tpp"
