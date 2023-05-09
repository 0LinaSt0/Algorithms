#pragma once

#include <deque>

namespace s21{

template< class T, class Container = std::deque<T> >
class Stack{
public:
    using container_type    = Container;
    using value_type        = Container::value_type;
    using size_type         = Container::size_type;
    using reference         = Container::reference;
    using const_reference   = Container::const_reference;

    Stack();
    Stack(const Stack& other);
    Stack(Stack&& other);
    ~Stack();

    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other);

    void push(const value_type& value);
    
    void push(value_type&& value);

    void pop();

    reference top();

    const_reference top() const;

private:

};

}
