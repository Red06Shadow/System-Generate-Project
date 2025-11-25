
template <typename T>
trails<T>::trails(const T __array[], size_t size) : __array__(nullptr), __size__(size)
{
    if (size == 0)
        return;
    if (!__array)
        throw std::runtime_error("Array sources is null");
    __array__ = new T[size];
    std::copy(__array, __array + size, __array__);
}
template <typename T>
trails<T>::trails(size_t size) : __array__(nullptr), __size__(size)
{
    if (size > 0)
        __array__ = new T[size];
}

template <typename T>
T trails<T>::at(size_t pos) const
{
    if (pos >= __size__)
        throw std::out_of_range("trails::at index out range");
    return __array__[pos];
}
template <typename T>
void trails<T>::assing(const trails<T> &__other) {
    delete[] (this->__array__);
    this->__array__ = __other.__array__;
    this->__size__ = __other.__size__;
}
template <typename T>
void trails<T>::copy(const trails<T> &__other) {
    *this = __other;
}
template <typename T>
void trails<T>::copy(const trails<T> &__other, size_t nelements) {
    if (nelements > __other.__size__)
        throw std::invalid_argument("nelements exceeds sources size");
    delete[] __array__;
    __size__ = nelements;

    if(__size__ > 0)
    {
        __array__ = new T[__size__];
        std::copy(__other.__array__, __other.__array__ + nelements, __array__);
    }
    else
        __array__ = nullptr;
}
