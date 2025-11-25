
template <typename T>
iterators::iterator<T>::iterator(const T *__arrarptr)
{
    __arrarptr__ = __arrarptr;
}
template <typename T>
bool iterators::iterator<T>::operator==(const iterator<T> &otro) const
{
    return this->__arrarptr__ == otro.__arrarptr__;
}
template <typename T>
bool iterators::iterator<T>::operator!=(const iterator<T> &otro) const
{
    return this->__arrarptr__ != otro.__arrarptr__;
}
template <typename T>
T &iterators::iterator<T>::operator*()
{
    return *const_cast<T *>(__arrarptr__);
}
template <typename T>
T *iterators::iterator<T>::operator->()
{
    return const_cast<T *>(__arrarptr__);
}
template <typename T>
iterators::iterator<T>::~iterator() {
    __arrarptr__ = nullptr;
}


template <typename T>
iterators::reverse_iterator<T>::reverse_iterator(const T *__arrarptr)
{
    __arrarptr__ = __arrarptr;
}
template <typename T>
bool iterators::reverse_iterator<T>::operator==(const iterators::reverse_iterator<T> &otro) const
{
    return this->__arrarptr__ == otro.__arrarptr__;
}
template <typename T>
bool iterators::reverse_iterator<T>::operator!=(const iterators::reverse_iterator<T> &otro) const
{
    return this->__arrarptr__ != otro.__arrarptr__;
}
template <typename T>
T &iterators::reverse_iterator<T>::operator*()
{
    return *const_cast<T *>(__arrarptr__);
}
template <typename T>
T *iterators::reverse_iterator<T>::operator->()
{
    return const_cast<T *>(__arrarptr__);
}
template <typename T>
iterators::reverse_iterator<T>::~reverse_iterator() {
    __arrarptr__ = nullptr;
}