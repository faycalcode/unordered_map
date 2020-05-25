#ifndef UMAPITERATOR_H
#define UMAPITERATOR_H

#include <utility>
#include <stdexcept>

template <typename K, typename V>
class uMap;

template <typename K, typename V>
class iteratoruMap
{
	uMap<K,V>& m_container; //avec & operator*(), sinon const uMap<k,v> 
	unsigned m_index = 0;
public:
	iteratoruMap(uMap<K,V>&, unsigned = 0);
	iteratoruMap(const iteratoruMap& other);
	iteratoruMap& operator=(const iteratoruMap& other);
	V& operator=(const V&);
	~iteratoruMap() = default;

	std::pair<K,V>& operator*();
	iteratoruMap& operator++();
	iteratoruMap& operator+(int);
	iteratoruMap& operator--();
	iteratoruMap& operator-(int);
	bool operator==(const iteratoruMap& other) const;
	bool operator!=(const iteratoruMap& other) const;
};

template <typename K, typename V>
iteratoruMap<K,V>::iteratoruMap(uMap<K,V>& m, unsigned i) : m_container(m), m_index(i) {}

template <typename K, typename V>
iteratoruMap<K,V>::iteratoruMap(const iteratoruMap<K,V>& other) : m_container(other.m_container), m_index(other.m_index) {}

template <typename K, typename V>
iteratoruMap<K,V>& iteratoruMap<K,V>::operator=(const iteratoruMap& other)
{ 
	m_container = other.m_container;
	m_index = other.m_index;
	return *this;
}

template <typename K, typename V>
std::pair<K,V>& iteratoruMap<K,V>::operator*()
{
	if(m_index < m_container.size()) return m_container.m_v[m_index];
	else throw std::out_of_range("Error iterator out of the container!");
}

template <typename K, typename V>
iteratoruMap<K,V>& iteratoruMap<K,V>::operator++()
{
	++m_index;
	return *this;
}

template <typename K, typename V>
iteratoruMap<K,V>& iteratoruMap<K,V>::operator+(int num)
{
	m_index += num;
	return *this;
}

template <typename K, typename V>
iteratoruMap<K,V>& iteratoruMap<K,V>::operator--()
{
	--m_index;
	return *this;
}

template <typename K, typename V>
iteratoruMap<K,V>& iteratoruMap<K,V>::operator-(int num)
{
	m_index-=num;
	return *this;
}

template <typename K, typename V>
bool iteratoruMap<K,V>::operator==(const iteratoruMap& other) const 
{
	if (m_index == other.m_index) return true;
	else return false;
}

template <typename K, typename V>
bool iteratoruMap<K,V>::operator!=(const iteratoruMap& other) const { return !(*this == other); }

template <typename K, typename V>
V& iteratoruMap<K,V>::operator=(const V& value)
{
	m_container->m_v[m_index].second = value;
	return m_container->m_v[m_index].second;
}

#endif