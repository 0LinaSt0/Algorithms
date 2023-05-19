namespace s21{

template< class T, class Container >
Queue<T, Container>::Queue(const Queue<T, Container>& other){
    qct_ = other.qct_;
}

template< class T, class Container >
Queue<T, Container>::Queue(Queue<T, Container>&& other){
    qct_ = std::move(other.qct_);
}

template< class T, class Container >
Queue<T, Container>::~Queue() { }

template< class T, class Container >
Queue<T, Container>& Queue<T, Container>::operator=(
                        const Queue<T, Container>& other){
    qct_ = other.qct_;
    return *this;
}

template< class T, class Container >
Queue<T, Container>& Queue<T, Container>::operator=(
                        Queue<T, Container>&& other){
    qct_ = std::move(other.qct_);
    return *this;
}

template< class T, class Container >
void Queue<T, Container>::push(
        const Queue<T, Container>::value_type& value){
    qct_.push_back(value);
}

template< class T, class Container >
void Queue<T, Container>::push(Queue<T, Container>::value_type&& value){
    qct_.push_back(std::move(value));
}

template< class T, class Container >
void Queue<T, Container>::pop(){
    qct_.pop_front();
}

template< class T, class Container >
typename Queue<T, Container>::reference Queue<T, Container>::front(){
    return qct_.front();
}

template< class T, class Container >
typename Queue<T, Container>::const_reference
            Queue<T, Container>::front() const{
    return qct_.front();
}

template< class T, class Container >
typename Queue<T, Container>::size_type Queue<T, Container>::size() const{
    return qct_.size();
}

}
