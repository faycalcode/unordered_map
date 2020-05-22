#ifndef UMAPSPECIAL_H
#define UMAPSPECIAL_H

#include "umapiterator.h"

#include <stdexcept>
#include <vector>

template <typename V>
class uMap<const char*,V> {
	std::vector<std::pair<const char*,V>> m_v ={};
public:
	friend class iteratoruMap<const char*,V>;
	uMap();
	~uMap();
	uMap(const uMap& m);
	uMap(const std::initializer_list<std::pair<const char*,V>>&);
	uMap(uMap&&) noexcept;
	uMap& operator=(const uMap&);
	uMap& operator=(uMap&&) noexcept;

	/*iterateurs*/
	iteratoruMap<const char*,V> begin() noexcept;
	const iteratoruMap<const char*,V> begin() const noexcept;
	const iteratoruMap<const char*,V> cbegin() const noexcept;
	iteratoruMap<const char*,V> end() noexcept;
	const iteratoruMap<const char*,V> end() const noexcept;
	const iteratoruMap<const char*,V> cend() const noexcept;

	/*capacity*/
	size_t size() const noexcept;
	bool empty() const noexcept;

	/*lookup*/
	const V& at(const char*) const;
	unsigned count(const char*) const noexcept;
	iteratoruMap<const char*,V> find(const char*) noexcept;

	/*modifiers*/
	std::pair<iteratoruMap<const char*,V>,bool> insert(const std::pair<const char*,V>&);
	std::pair<iteratoruMap<const char*,V>, bool> insert_or_assign(const std::pair<const char*,V>&);
	V& operator[](const char*);
	void clear() noexcept; 
	void swap(uMap<const char*,V>&) noexcept;
	//iteratoruMap<k,v> erase(const iteratoruMap<k,v>&);
	//iteratoruMap<k,v> erase(const iteratoruMap<k,v>&, const iteratoruMAp<k,v>&);
	//size_type erase(const k&);
};

/*constructors*/
template <typename V>
uMap<const char*,V>::uMap() {}

template <typename V>
uMap<const char*,V>::~uMap() {}

template <typename V>
uMap<const char*,V>::uMap(const uMap& m):
	m_v(m.m_v) {}

template <typename V>
uMap<const char*,V>::uMap(const std::initializer_list<std::pair<const char*,V>>& l) :
	m_v(l) {}

template <typename V>
uMap<const char*,V>::uMap(uMap&& m) noexcept:
	m_v(std::move(m.m_v)) {}

template <typename V>
uMap<const char*,V>& uMap<const char*,V>::operator=(const uMap& m)
{
	m_v = m.m_v;
	return *this;
}

template <typename V>
uMap<const char*,V>& uMap<const char*,V>::operator=(uMap&& m) noexcept
{
	m_v = std::move(m.m_v);
	return *this;
}


/*iterators*/
template <typename V>
iteratoruMap<const char*,V> uMap<const char*,V>::begin() noexcept { return iteratoruMap<const char*,V>(*this); }

template <typename V>
const iteratoruMap<const char*,V> uMap<const char*,V>::begin() const noexcept { return iteratoruMap<const char*,V>(*this); }

template <typename V>
const iteratoruMap<const char*,V> uMap<const char*,V>::cbegin() const noexcept{ return iteratoruMap<const char*,V>(*this); }

template <typename V>
iteratoruMap<const char*,V> uMap<const char*,V>::end() noexcept { return iteratoruMap<const char*,V>(*this,(unsigned)size()); }

template <typename V>
const iteratoruMap<const char*,V> uMap<const char*,V>::end() const noexcept { return iteratoruMap<const char*,V>(*this,(unsigned)size()); }

template <typename V>
const iteratoruMap<const char*,V> uMap<const char*,V>::cend() const noexcept { return iteratoruMap<const char*,V>(*this,(unsigned)size()); }


/*capacity*/
template <typename V>
size_t uMap<const char*,V>::size() const noexcept { return m_v.size(); }

template <typename V>
bool uMap<const char*,V>::empty() const noexcept { return (size() == 0); }


/*lookup*/
template <typename V>
const V& uMap<const char*,V>::at(const char* key) const
{
	for(unsigned i=0; i<size(); ++i){
		if(std::strcmp(key,m_v[i].first) == 0) return m_v[i].second;
	}
	throw std::out_of_range("Key not found");
}

template <typename V>
unsigned uMap<const char*,V>::count(const char* key) const noexcept
{
	for(unsigned i = 0; i < size(); ++i) {
		if(std::strcmp(m_v[i].first,key) == 0) return 1;
	}
	return 0;
}

template <typename V>
iteratoruMap<const char*,V> uMap<const char*,V>::find(const char* key) noexcept
{
	for(unsigned i=0; i<size(); ++i){
		if(std::strcmp(m_v[i].first, key) == 0 ) return iteratoruMap<K,V>(*this,i);
	}
	return iteratoruMap<K,V>(*this,(unsigned)size());
}

/*modifier*/

template <typename V>
std::pair<iteratoruMap<const char*,V>,bool> uMap<const char*,V>::insert(const std::pair<const char*,V>& p)
{
	unsigned i;
	for(i=0;i<size();++i){
		if(std::strcmp(p.first, m_v[i].first) == 0) return std::pair<iteratoruMap<const char*,V>,bool>(iteratoruMap<const char*,V>(*this,i),false);
	}
	m_v.push_back(p);
	return std::pair<iteratoruMap<const char*,V>,bool>(end()-1,true);
}

template <typename V>
std::pair<iteratoruMap<const char*,V>,bool> uMap<const char*,V>::insert_or_assign(const std::pair<const char*,V>& p)
{
	unsigned i;
	for(i=0;i<size();++i){
		if(std::strcmp(p.first, m_v[i].first) == 0 ) {
			m_v[i].second = p.second;
				return std::pair<iteratoruMap<const char*,V>,bool>(iteratoruMap<const char*,V>(*this,i),false);
		}
	}
	m_v.push_back(p);
	return std::pair<iteratoruMap<const char*,V>,bool>(end()-1,true);
}

template <typename V>
V& uMap<const char*,V>::operator[](const char* key)
{
	iteratoruMap<const char*,V> it = find(key);
	if(it == end()){
		m_v.push_back(std::pair<const char*,V>(key,{}));
	}
	return (*it).second;
}

template <typename V>
void uMap<const char*,V>::clear() noexcept { m_v.clear(); }

template <typename V>
void uMap<const char*,V>::swap(uMap& other) noexcept { m_v.swap(other.m_v); }

#endif