template <typename T,bool ORDER,bool REPETITION>
GenericUrn<T, ORDER, REPETITION>::GenericUrn(uint k,const std::vector<T>& elements)
            :m_urn { static_cast<uint>(elements.size()),k },
             m_elements { elements }{}

template <typename T,bool ORDER,bool REPETITION>
uint GenericUrn<T, ORDER, REPETITION>::n() const
{
    return m_urn.n();
}

template <typename T,bool ORDER,bool REPETITION>
uint GenericUrn<T, ORDER, REPETITION>::k() const
{
    return m_urn.k();
}

template <typename T,bool ORDER,bool REPETITION>
const T& GenericUrn<T, ORDER, REPETITION>::at(uint index) const
{
    return m_elements.at(m_urn.at(index));
}

template <typename T,bool ORDER,bool REPETITION>
const T& GenericUrn<T, ORDER, REPETITION>::operator[](uint index) const
{
    return m_elements[m_urn[index]];
}

template <typename T,bool ORDER,bool REPETITION>
[[nodiscard]] bool GenericUrn<T, ORDER, REPETITION>::next()
{
    return m_urn.next();
}