/**
 * @file Tree.hpp
 *
 */

#ifndef TREE_HPP_
#define TREE_HPP_

//
// Data interpretation of ListTree::_dataStorage (depth-first order).
//
// Note, list iterators are guaranteed to remain
// the same when list size changes.
//
//  0 00 000 001 01 02 020 021 022 023 03	data
// -1  0   1   1  0  0   5   5   5   5  0	parent ref
//
// 0
//  00
//   000
//   001
//  01
//  02
//   020
//   021
//   022
//  03
//

#include <list>

template<typename T>
struct Node
{
	T data;
	typename std::list<Node<T>>::iterator parent;
};

template<typename T>
class ListTree;

template<typename T>
class NodeIterator
{
public:
	friend class ListTree<T>;

	/**
	 * Constructor.
	 *
	 * @param it			Current list iterator.
	 * @param dataStorage	List iterated over.
	 */
	NodeIterator(typename std::list<Node<T>>::iterator it,
	             std::list<Node<T>>& dataStorage);

	/**
	 * @return	Data access of node.
	 */
	T& operator*();

	/**
	 * Depth-first forward iteration.
	 */
	void operator++();
	/**
	 * Depth-first backward iteration.
	 */
	void operator--();

	/**
	 * Snaps this iterator to its parent.
	 */
	void toParent();
	/**
	 * Snaps this iterator to first sibling.
	 */
	void toSibling();
	/**
	 * Snaps this iterator to first child.
	 */
	void toChild();

	/**
	 * @return	true if iterated node has no parent.
	 */
	bool isRoot() const;

	bool operator==(const NodeIterator<T>& other) const;
	bool operator!=(const NodeIterator<T>& other) const;

private:
	typename std::list<Node<T>>::iterator _it;
	std::list<Node<T>>& _dataStorage;
};

template<typename T>
class ListTree
{
public:
	typedef NodeIterator<T> iterator;

public:
	/**
	 * Creates the root.
	 *
	 * @return	The root iterator.
	 */
	iterator setRoot(T data);

	/**
	 * @return	Beginning of tree (the root).
	 */
	iterator begin();
	/**
	 * @return	The node past the last one.
	 */
	iterator end();

	/**
	 * Inserts a node as the next child.
	 *
	 * @param it	Iterator to parent node.
	 * @param data	Data of new node.
	 * @return		Iterator to created node.
	 */
	iterator insertChild(iterator it,
	                     T data);
	/**
	 * Inserts a node as the next sibling.
	 *
	 * @param it	Iterator to node.
	 * @param data	Data of new node.
	 * @return		Iterator to created node.
	 */
	iterator insertSibling(iterator it,
	                       T data);

	/**
	 * Removes node and all descendants of parameter.
	 *
	 * The iterator passed as parameter will point to
	 * non-existing node after successful call.
	 *
	 * @param it	Iterator to node.
	 * @return		Iterator to node after the deleted branch.
	 */
	iterator eraseBranch(iterator it);

private:
	std::list<Node<T>> _dataStorage;
};

// Implementation

template<typename T>
inline NodeIterator<T>::NodeIterator(typename std::list<Node<T>>::iterator it,
                                     std::list<Node<T>>& dataStorage)
: _it(it), _dataStorage(dataStorage)
{
}

template<typename T>
inline T& NodeIterator<T>::operator*()
{
	return _it->data;
}

template<typename T>
inline void NodeIterator<T>::operator++()
{
	++_it;
}

template<typename T>
inline void NodeIterator<T>::operator--()
{
	--_it;
}

template<typename T>
inline void NodeIterator<T>::toParent()
{
	_it = _it->parent;
}

template<typename T>
inline void NodeIterator<T>::toSibling()
{
	for (typename std::list<Node<T>>::iterator it = ++_it;
		 it != _dataStorage.end();
		 ++it)
	{
		if (it->parent == _it)
			continue;

		if (it->parent == _it->parent)
		{
			_it = it;
			return;
		}

		break;
	}

	_it = _dataStorage.end();
}

template<typename T>
inline void NodeIterator<T>::toChild()
{
	typename std::list<Node<T>>::iterator it = _it;
	++it;

	if (_it->parent == it->parent)
		_it = it;
	else
		_it = _dataStorage.end();
}

template<typename T>
inline bool NodeIterator<T>::isRoot() const
{
	return _it->parent == _dataStorage.end();
}

template<typename T>
inline bool NodeIterator<T>::operator==(const NodeIterator<T>& other) const
{
	return (_it == other._it) && (&_dataStorage == &other._dataStorage);
}

template<typename T>
inline bool NodeIterator<T>::operator!=(const NodeIterator<T>& other) const
{
	return (_it != other._it) || (&_dataStorage != &other._dataStorage);
}

template<typename T>
inline typename ListTree<T>::iterator ListTree<T>::setRoot(T data)
{
	// TODO Should be handled differently

	if (!_dataStorage.empty())
	{
		// TODO Throw something?
	}

	_dataStorage.push_back( {data, _dataStorage.end()} );

	return iterator(_dataStorage.begin(), _dataStorage);
}

template<typename T>
inline typename ListTree<T>::iterator ListTree<T>::begin()
{
	return iterator(_dataStorage.begin(), _dataStorage);
}

template<typename T>
inline typename ListTree<T>::iterator ListTree<T>::end()
{
	return iterator(_dataStorage.end(), _dataStorage);
}

template<typename T>
inline typename ListTree<T>::iterator ListTree<T>::insertChild(iterator it,
                                                      T data)
{
	if (it._it == _dataStorage.end())
	{
		// TODO Throw something
	}

	typename std::list<Node<T>>::iterator listIt = it._it;
	++listIt;

	return iterator(_dataStorage.insert(listIt, {data, it._it}), _dataStorage);
}

template<typename T>
inline typename ListTree<T>::iterator ListTree<T>::insertSibling(iterator it,
                                                        T data)
{
	// TODO Implement
}

template<typename T>
inline typename ListTree<T>::iterator ListTree<T>::eraseBranch(iterator it)
{
	if (it._it == _dataStorage.end())
	{
		// TODO Throw something
	}

	typename std::list<Node<T>>::iterator last = it._it + 1;

	for (; last != _dataStorage.end(); ++last)
	{
		if (last->parent != it._it)
			break;
	}

	return iterator(_dataStorage.erase(it._it, last), _dataStorage);
}


#endif /* TREE_HPP_ */
