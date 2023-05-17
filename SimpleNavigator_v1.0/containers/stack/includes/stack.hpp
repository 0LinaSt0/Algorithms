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

    Stack() = default;
    Stack(const Stack& other) = default;
    Stack(Stack&& other) = default;
    ~Stack() = default;

    Stack& operator=(const Stack& other) = default;
    Stack& operator=(Stack&& other) = default;

    // Adding an element
    void push(const value_type& value);
    
    // Adding an element
    void push(value_type&& value);

    /**
     * Getting an element from the stack
     * followed by its removal from the stack
     */
    value_type pop();

    /**
     * Getting an element from the stack without its removal from the stack
     * @return reference to the stack element
     */
    reference top();

    /**
     * Getting an element from the stack without its removal from the stack
     * @return const reference to the stack element
     */
    const_reference top() const;

    /**
     * @return size of stack
     */
    size_type size() const;

    /**
     * @return if stack empty
     */
    bool empty() const;

private:
    container_type inner_container_;

};

}

#include "../srcs/stack.tpp"
