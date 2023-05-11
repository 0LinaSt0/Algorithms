namespace s21{

template<class T, class Container>
Stack<T, Container>::Stack(){

}

template<class T, class Container>
Stack<T, Container>::Stack(const Stack& other)
    : innerContainer_(other.innerContainer_) {
    
}

template<class T, class Container>
Stack<T, Container>::Stack(Stack&& other)
    : innerContainer_(std::move(other.innerContainer_)) {
    
}

template<class T, class Container>
Stack<T, Container>::~Stack(){

}

template<class T, class Container>
Stack<T, Container>& Stack<T, Container>::operator=(const Stack& other){
    innerContainer_ = other.innerContainer_;
    return *this;
}

template<class T, class Container>
Stack<T, Container>& Stack<T, Container>::operator=(Stack&& other){
    innerContainer_ = std::move(other.innerContainer_);
    return *this;
}

template<class T, class Container>
void Stack<T, Container>::push(const value_type& value){
    innerContainer_.push_back(value);
}

template<class T, class Container>
void Stack<T, Container>::push(value_type&& value){
    innerContainer_.push_back(value);
}

template<class T, class Container>
typename Stack<T, Container>::value_type Stack<T, Container>::pop(){
    T elem = top();
    innerContainer_.pop_back();
    return elem;
}

template<class T, class Container>
typename Stack<T, Container>::reference Stack<T, Container>::top(){
    return innerContainer_.back();
}

template<class T, class Container>
typename Stack<T, Container>::const_reference Stack<T, Container>::top() const{
    return innerContainer_.back();
}

}
