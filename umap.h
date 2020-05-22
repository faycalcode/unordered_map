#ifndef UMAP_H
#define UMAP_H
#include "umapiterator.h"

#include <stdexcept>
#include <vector>

/*
1) probleme avec les objets const et les iterateurs
2) find(k) const; = erreur
*/

template <typename K, typename V>
class uMap {
	std::vector<std::pair<K,V>> m_v = {};
public:
	friend class iteratoruMap<K,V>;
	uMap();
	~uMap();
	uMap(const uMap& m);
	uMap(const std::initializer_list<std::pair<K,V>>&);
	uMap(uMap&&) noexcept;
	uMap& operator=(const uMap&);
	uMap& operator=(uMap&&) noexcept;

	/*iterateurs*/ //signatures vues sur ccpreference
	iteratoruMap<K,V> begin() noexcept; // un probleme a regler avec les iterators sur des objets const
	const iteratoruMap<K,V> begin() const noexcept;
	const iteratoruMap<K,V> cbegin() const noexcept;
	iteratoruMap<K,V> end() noexcept;
	const iteratoruMap<K,V> end() const noexcept;
	const iteratoruMap<K,V> cend() const noexcept;

	/*capacity*/
	size_t size() const noexcept;
	bool empty() const noexcept;

	/*lookup*/
	const V& at(const K&) const;
	unsigned count(const K&) const noexcept;
	iteratoruMap<K,V> find(const K&) noexcept; //tj le même probleme pas possible de mettre const car création d'iterateur sur const = probleme

	/*modifiers*/
	std::pair<iteratoruMap<K,V>,bool> insert(const std::pair<K,V>&);
	std::pair<iteratoruMap<K,V>, bool> insert_or_assign(const std::pair<K,V>&);
	V& operator[](const K&);
	void clear() noexcept;
	void swap(uMap<K,V>&) noexcept;

	//iteratoruMap<k,v> erase(const iteratoruMap<k,v>&);
	//iteratoruMap<k,v> erase(const iteratoruMap<k,v>&, const iteratoruMAp<k,v>&);
	//size_type erase(const k&);
};

/*constructors*/
template <typename K, typename V>
uMap<K,V>::uMap() {}

template <typename K, typename V>
uMap<K,V>::~uMap() {}

template <typename K, typename V>
uMap<K,V>::uMap(const uMap& m) :
	m_v(m.m_v) {}

template <typename K, typename V>
uMap<K,V>::uMap(const std::initializer_list<std::pair<K,V>>& l) :
	m_v(l) {}

template <typename K, typename V>
uMap<K,V>::uMap(uMap&& m) noexcept:
	m_v(std::move(m.m_v)) {}

template <typename K, typename V>
uMap<K,V>& uMap<K,V>::operator=(const uMap& m)
{
	m_v = m.m_v;
	return *this;
}

template <typename K,typename V>
uMap<K,V>& uMap<K,V>::operator=(uMap&& m) noexcept
{
	m_v = std::move(m.m_v);
	return *this;
}

/*iterators*/
template <typename K,typename V>
iteratoruMap<K,V> uMap<K,V>::begin() noexcept { return iteratoruMap<K,V>(*this); }

template <typename K, typename V>
const iteratoruMap<K,V> uMap<K,V>::begin() const noexcept { return iteratoruMap<K,V>(*this); }

template <typename K,typename V>
const iteratoruMap<K,V> uMap<K,V>::cbegin() const noexcept { return iteratoruMap<K,V>(*this); }

template <typename K,typename V>
iteratoruMap<K,V> uMap<K,V>::end() noexcept { return iteratoruMap<K,V>(*this,(unsigned)size()); }

template <typename K,typename V>
const iteratoruMap<K,V> uMap<K,V>::end() const noexcept { return iteratoruMap<K,V>(*this,(unsigned)size()); }

template <typename K,typename V>
const iteratoruMap<K,V> uMap<K,V>::cend() const noexcept { return iteratoruMap<K,V>(*this,(unsigned)size()); }


/*capacity*/
template <typename K, typename V>
size_t uMap<K,V>::size() const noexcept { return m_v.size(); }

template <typename K, typename V>
bool uMap<K,V>::empty() const noexcept { return (size() == 0); }


/*lookup*/
template <typename K, typename V>
const V& uMap<K,V>::at(const K& key) const
{
	for(unsigned i=0; i<size(); ++i){
		if(key == m_v[i].first) return m_v[i].second;
	}
	throw std::out_of_range("Key not found");
}

template <typename K, typename V>
unsigned uMap<K,V>::count(const K& key) const noexcept
{
	for (unsigned i = 0; i < m_v.size(); ++i) {
		if (m_v[i].first == key) return 1;
	}
	return 0;
}

template <typename K, typename V>
iteratoruMap<K,V> uMap<K,V>::find(const K& key) noexcept
{
	for(unsigned i=0; i<size(); ++i){
		if(key == m_v[i].first) return iteratoruMap<K,V>(*this, i);
	}
	return iteratoruMap<K,V>(*this, (unsigned)size());
}


/*modifier*/

template <typename K,typename V>
std::pair<iteratoruMap<K,V>,bool> uMap<K,V>::insert(const std::pair<K,V>& p)
{
	unsigned i;
	for(i=0;i<size();++i){
		if(p.first == m_v[i].first) return std::pair<iteratoruMap<K,V>,bool>(iteratoruMap<K,V>(*this,i),false);
	}
	m_v.push_back(p);
	return std::pair<iteratoruMap<K,V>,bool>(end()-1,true);
}

template <typename K, typename V>
std::pair<iteratoruMap<K,V>,bool> uMap<K,V>::insert_or_assign(const std::pair<K,V>& p)
{
	unsigned i;
	for(i=0;i<size();++i){
		if( m_v[i].first == p.first ) {
			m_v[i].second = p.second;
			return std::pair<iteratoruMap<K,V>,bool>(iteratoruMap<K,V>(*this,i),false);
		}
	}
	m_v.push_back(p);
	return std::pair<iteratoruMap<K,V>,bool>(end()-1,true);
}

template <typename K,typename V>
V& uMap<K,V>::operator[](const K& key)
{
	iteratoruMap<K,V> it = find(key);
	if(it == end()){
		m_v.push_back(std::pair<K,V>(key,{}));
	}
	return (*it).second;
}


template <typename K,typename V>
void uMap<K,V>::clear() noexcept { m_v.clear(); }

template <typename K, typename V>
void uMap<K,V>::swap(uMap& other) noexcept { m_v.swap(other.m_v); }

#endif