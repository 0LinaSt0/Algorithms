namespace s21{

template<class T, class Container>
void Stack<T, Container>::push(const value_type& value){
    inner_container_.push_back(value);
}

template<class T, class Container>
void Stack<T, Container>::push(value_type&& value){
    inner_container_.push_back(std::move(value));
}

template<class T, class Container>
typename Stack<T, Container>::value_type Stack<T, Container>::pop(){
    T elem = top();
    inner_container_.pop_back();
    return elem;
}

template<class T, class Container>
typename Stack<T, Container>::reference Stack<T, Container>::top(){
    return inner_container_.back();
}

template<class T, class Container>
typename Stack<T, Container>::const_reference Stack<T, Container>::top() const{
    return inner_container_.back();
}

template<class T, class Container>
typename Stack<T, Container>::size_type Stack<T, Container>::size() const{
    return inner_container_.size();
}

template<class T, class Container>
bool Stack<T, Container>::empty() const{
    return size() == 0;
}

}
