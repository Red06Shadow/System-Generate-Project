
template <typename T>
void algoritm::view(const T array[], size_t size)
{
    std::cout << '[';
    for (size_t i = 0; i < size; i++)
        std::cout << array[i] << (size - 1 == i ? "" : ", ");
    std::cout << ']' << std::endl;
}

template <typename T>
void algoritm::view(const trails<T>& array)
{
    std::cout << '[';
    for (size_t i = 0; i < array.size(); i++)
        std::cout << array[i] << (array.size() - 1 == i ? "" : ", ");
    std::cout << ']' << std::endl;
}

template <typename T>
void algoritm::copy(T _destine_[], const T _sources[], size_t _sdestine_, size_t _ssources)
{
    size_t s = (_sdestine_ <= _ssources) ? _sdestine_ : _ssources;
    for (size_t i = 0; i < s; i++)
        _destine_[i] = _sources[i];
}
template <typename T>
void algoritm::copy(std::vector<T> &_destine_, const std::vector<T> &_sources)
{
    if (_destine_.capacity() < _sources.size())
        _destine_.reserve(_sources.capacity());
    for (size_t i = 0; i < _sources.size(); i++)
        _destine_[i] = _sources[i];
    std::string h;
}
size_t algoritm::bitforaround(size_t n)
{
    unsigned char i = sizeof(size_t) * 8;
    while (--i >= 0)
    {
        if ((n & ((size_t)(1) << i)) != 0)
            break;
    }
    return (size_t)(1) << (unsigned char)(i + 1);
}
template <typename T>
void algoritm::copy(std::vector<T> &_destine_, const T _sources[], size_t _ssources)
{
    if (_destine_.capacity() < _ssources)
        _destine_.reserve(bitforaround(_ssources));
    for (size_t i = 0; i < _ssources; i++)
        _destine_[i] = _sources[i];
}
template <typename U>
size_t algoritm::size(const U _sources[])
{
    return std::strlen((char *)(_sources)) / size_t(sizeof(U));
}
template <typename Q>
void algoritm::qickshort(Q array[], size_t size)
{
    size_t sizeless = 0, sizeequals = 0, sizegreather = 0;
    Q pivote = array[0];
    Q arrayless[size], arrayequals[size], arraygreathers[size];
    for (size_t i = 0; i < size; i++)
    {
        if (array[i] > pivote)
        {
            arraygreathers[sizegreather] = array[i];
            sizegreather++;
        }
        else if (array[i] < pivote)
        {
            arrayless[sizeless] = array[i];
            sizeless++;
        }
        else
        {
            arrayequals[sizeequals] = array[i];
            sizeequals++;
        }
    }
    if (sizeless > 0)
    {
        qickshort(arrayless, sizeless);
        algoritm::copy<Q>(array, arrayless, size, sizeless);
    }
    if (sizeequals > 0)
    {
        if (sizeequals != size)
            qickshort(arrayequals, sizeequals);
        algoritm::copy<Q>(array + sizeless, arrayequals, size, sizeequals);
    }
    if (sizegreather > 0)
    {
        qickshort(arraygreathers, sizegreather);
        algoritm::copy<Q>(array + sizeless + sizeequals, arraygreathers, size, sizegreather);
    }
}

// Escribir codigop para QickShortTwoPivote
template <typename Q>
void algoritm::qickshort2(Q array[], size_t size)
{
    size_t sizeless = 0, sizebetewn = 0, sizeequals1 = 0, sizeequals2 = 0, sizegreather = 0;
    Q pivote1 = array[0], pivote2 = array[size - 2];
    if (pivote1 > pivote2)
        std::swap(pivote1, pivote2);
    Q arrayless[size], arraybetewn[size], arrayequals1[size], arrayequals2[size], arraygreathers[size];
    for (size_t i = 0; i < size; i++)
    {
        Q __ayx = array[i];
        if (__ayx > pivote2)
        {
            arraygreathers[sizegreather] = __ayx;
            sizegreather++;
        }
        else if (__ayx < pivote1)
        {
            arrayless[sizeless] = __ayx;
            sizeless++;
        }
        else if (__ayx > pivote1 && __ayx < pivote2)
        {
            arraybetewn[sizebetewn] = __ayx;
            sizebetewn++;
        }
        else if (__ayx == pivote1)
        {
            arrayequals1[sizeequals1] = __ayx;
            sizeequals1++;
        }
        else
        {
            arrayequals2[sizeequals2] = array[i];
            sizeequals2++;
        }
    }
    if (sizeless > 0)
    {
        qickshort(arrayless, sizeless);
        algoritm::copy<Q>(array, arrayless, size, sizeless);
    }
    if (sizeequals1 > 0)
    {
        if (sizeequals1 != size)
            qickshort(arrayequals1, sizeequals1);
        algoritm::copy<Q>(array + sizeless, arrayequals1, size, sizeequals1);
    }
    if (sizebetewn > 0)
    {
        qickshort(arraybetewn, sizebetewn);
        algoritm::copy<Q>(array + sizeless + sizeequals1, arraybetewn, size, sizebetewn);
    }
    if (sizeequals2 > 0)
    {
        if (sizeequals2 != size)
            qickshort(arrayequals2, sizeequals2);
        algoritm::copy<Q>(array + sizeless + sizeequals1 + sizebetewn, arrayequals2, size, sizeequals2);
    }
    if (sizegreather > 0)
    {
        qickshort(arraygreathers, sizegreather);
        algoritm::copy<Q>(array + sizeless + sizeequals1 + sizebetewn + sizeequals2, arraygreathers, size, sizegreather);
    }
}
template <typename Q>
size_t algoritm::binarysearch(Q array[], Q element, size_t size)
{
    size_t position = size / 2, pivote = size / 2;
    Q actual;
    while ((actual = array[position]) != element)
    {
        if (actual < element)
        {
            if (pivote > 1)
                pivote /= 2;
            position += pivote;
        }
        else
        {
            if (pivote > 1)
                pivote /= 2;
            position -= pivote;
        }
        if (position == 0 || position == size)
            return -1;
    }
    return position;
}