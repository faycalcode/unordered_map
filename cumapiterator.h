#ifndef CUMAPITERATOR_H
#define CUMAPITERATOR_H

#include <utility>
#include <stdexcept>

/*the const iterator*/

template <typename K,typename V>
class uMap;

template <typename K,typename V>
class citeratoruMap
{
	const uMap<K,V>& m_container;
	unsigned m_index = 0;
public:
	citeratoruMap(const uMap<K,V>&,unsigned = 0);
	citeratoruMap(const citeratoruMap& other);
	citeratoruMap& operator=(const citeratoruMap& other);
	V& operator=(const V&);
	~citeratoruMap() = default;

	std::pair<K,V> const& operator*() const;
	citeratoruMap& operator++();
	citeratoruMap& operator+(int);
	citeratoruMap& operator--();
	citeratoruMap& operator-(int);
	bool operator==(const citeratoruMap& other) const;
	bool operator!=(const citeratoruMap& other) const;
};

template <typename K,typename V>
citeratoruMap<K,V>::citeratoruMap(const uMap<K,V>& m,unsigned i): m_container(m),m_index(i) {}

template <typename K,typename V>
citeratoruMap<K,V>::citeratoruMap(const citeratoruMap<K,V>& other) : m_container(other.m_container),m_index(other.m_index) {}

template <typename K,typename V>
citeratoruMap<K,V>& citeratoruMap<K,V>::operator=(const citeratoruMap& other)
{
	m_container = other.m_container;
	m_index = other.m_index;
	return *this;
}

template <typename K,typename V>
std::pair<K,V> const& citeratoruMap<K,V>::operator*() const
{
	if(m_index < m_container.size()) return m_container.m_v[m_index];
	else throw std::out_of_range("Error iterator out of the container!");
}


template <typename K,typename V>
citeratoruMap<K,V>& citeratoruMap<K,V>::operator++()
{
	++m_index;
	return *this;
}

template <typename K,typename V>
citeratoruMap<K,V>& citeratoruMap<K,V>::operator+(int num)
{
	m_index += num;
	return *this;
}

template <typename K,typename V>
citeratoruMap<K,V>& citeratoruMap<K,V>::operator--()
{
	--m_index;
	return *this;
}

template <typename K,typename V>
citeratoruMap<K,V>& citeratoruMap<K,V>::operator-(int num)
{
	m_index-=num;
	return *this;
}

template <typename K,typename V>
bool citeratoruMap<K,V>::operator==(const citeratoruMap& other) const
{
	if(m_index == other.m_index) return true;
	else return false;
}

template <typename K,typename V>
bool citeratoruMap<K,V>::operator!=(const citeratoruMap& other) const { return !(*this == other); }

template <typename K,typename V>
V& citeratoruMap<K,V>::operator=(const V& value)
{
	m_container->m_v[m_index].second = value;
	return m_container->m_v[m_index].second;
}

#endif