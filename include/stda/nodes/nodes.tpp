size_t node::base::countofelements = 0, node::base::countofpoints = 0, node::base::countofarrays = 0, node::base::countofvector = 0, node::base::countofmaping = 0, node::base::countofother = 0;

template <typename T>
node::point<T>::point(const T &__value) : base(node::_S_point)
{
    value = __value;
    base::countofpoints++;
}
template <typename T>
node::point<T>::point(const point<T> &other) : base(other)
{
    std::copy(value, other.value);
}
template <typename T>
node::point<T>::point(point<T> &&other) : base(std::move(other))
{
    other.value = std::move(value);
}

template <typename T>
const T &node::point<T>::get() const
{
    return value;
}
template <typename T>
void node::point<T>::set(const T &__value)
{
    value = __value;
}

template <typename T>
node::point<T>::~point()
{
    // if constexpr T ==
    // value.~T();
}
template <size_t N>
node::array<N>::array(const std::initializer_list<node::base *> &list) : base(node::_S_array)
{
    size_t size = list.size();
    size_t n = 0;
    size = size < N ? size : N;
    while (n < size)
    {
        values[n] = *(list.begin() + n);
        n++;
    }
    for (size_t i = n; i < N; i++)
        values[i] = nullptr;
    base::countofarrays++;
}
template <size_t N>
node::array<N>::array(const array &other) : base(other)
{
    for (size_t i = 0; i < N; i++)
        std::copy(values[i], other.values[i]);
}
template <size_t N>
node::array<N>::array(array &&other) : base(std::move(other))
{
    for (size_t i = 0; i < N; i++)
    {
        values[i] = other.values[i];
        other.values[i] = nullptr;
    }
}
template <size_t N>
node::array<N>::~array()
{
    for (size_t i = 0; i < N; i++)
        if (values[i] != nullptr)
            delete values[i];
}
template <size_t N>
node::base *&node::array<N>::operator[](size_t pos)
{
    return values[pos];
}
template <size_t N>
const node::base *node::array<N>::at(size_t pos) const
{
    if (pos >= N)
        throw std::runtime_error("Error acceso ilegal");
    return values[pos];
}
template <size_t N>
void node::array<N>::replace(node::base *element, size_t pos)
{
    if (pos >= N)
        throw std::runtime_error("Error acceso ilegal");
    delete values[pos];
    values[pos] = *element;
}
template <size_t N>
void node::array<N>::remove(size_t pos)
{
    if (pos >= N)
        throw std::runtime_error("Error acceso ilegal");
    delete values[pos];
    values[pos] = nullptr;
}

node::vector::vector(const std::initializer_list<base *> &list) : node::base(node::_S_vector)
{
    values = std::vector(list);
    base::countofvector++;
}
node::vector::vector(const std::vector<base *> &factor) : node::base(node::_S_vector)
{
    values = factor;
    base::countofvector++;
}
node::vector::vector(const node::vector &other) : node::base(node::_S_vector)
{
    values = std::move(other.values);
    base::countofvector++;
}
node::vector::vector(node::vector &&other) : node::base(std::move(other))
{
    values = other.values;
}
void node::vector::insert(size_t pos, base *value)
{
    values.insert(values.begin() + pos, value);
}
void node::vector::insert(const std::vector<base *>::iterator &pos, base *value)
{
    values.insert(pos, value);
}
void node::vector::replace(size_t pos, base *value)
{
    values[pos] = value;
    // Why!?
}
void node::vector::remove(size_t pos)
{
    values.erase(values.begin() + pos);
}
void node::vector::remove(const std::vector<base *>::iterator &pos)
{
    values.erase(pos);
}
node::vector::~vector()
{
    for (auto &&i : values)
        if (i != nullptr)
            delete i;
}

template <typename _Key>
node::mapped<_Key>::mapped(const std::initializer_list<std::pair<_Key, base *>> &list) : node::base(node::_S_mapped)
{
    values = std::map<_Key, base *>(list);
    base::countofmaping++;
}
template <typename _Key>
node::mapped<_Key>::mapped(const std::map<_Key, base *> &factor) : node::base(node::_S_mapped)
{
    values = factor;
    base::countofmaping++;
}
template <typename _Key>
node::mapped<_Key>::mapped(const node::mapped<_Key> &other) : node::base(node::_S_mapped)
{
    std::copy(values, other.values);
    base::countofmaping++;
}
template <typename _Key>
node::mapped<_Key>::mapped(node::mapped<_Key> &&other) : node::base(std::move(other))
{
    values = std::move(other);
}
template <typename _Key>
node::mapped<_Key>::~mapped()
{
    for (auto &&i : values)
        delete i->second;
    values.clear();
}