#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
#include <stack>
#include <time.h>

template< typename Key, typename Value >
class BST {
public:
	BST() : root_(nullptr) {}

	Value& operator[](const Key& key);

	class Node {
	public:

		Node(Key key) : key_(key), value_(), left_(nullptr), right_(nullptr) {}

		const Key& key();
		Value& value();
		Node* left();
		Node* right();

		int& lookup(const Key key);

	private:
		Key key_;
		Value value_;
		Node* left_;
		Node* right_;
	};
	class Iterator {
	public:
		Iterator(Node* root);


		bool operator==(const Iterator& other);
		bool operator!=(const Iterator& other);

		Iterator& operator++();
		const std::pair<const Key&, Value&> operator*();

	private:
		void leftmost(Node*p);
		Node* current_;
		std::stack<Node*> stack_;
	};
	Iterator end();
	Iterator begin();

private:
	Node * root_;

};

template<typename Key, typename Value>
inline BST<Key, Value>::Iterator::Iterator(Node * root)
{
	if (!root) {
		current_ = nullptr;
		return;
	}
	leftmost(root);
	current_ = stack_.top();
	stack_.pop();
}

template<typename Key, typename Value>
inline typename BST<Key, Value>::Iterator BST<Key, Value>::begin()
{
	return Iterator(root_);
}

template<typename Key, typename Value>
inline typename BST<Key, Value>::Iterator BST<Key, Value>::end()
{
	return Iterator(nullptr);
}

template<typename Key, typename Value>
inline bool BST<Key, Value>::Iterator::operator==(const Iterator & other)
{
	return current_ == other.current_;
}

template<typename Key, typename Value>
inline bool BST<Key, Value>::Iterator::operator!=(const Iterator & other)
{
	return !(*this == other);
}

template<typename Key, typename Value>
inline typename BST<Key, Value>::Iterator & BST<Key, Value>::Iterator::operator++()
{
	leftmost(current_->right());
	if (stack_.empty()) {
		current_ = nullptr;
		return *this;
	}
	current_ = stack_.top();
	stack_.pop();

	return*this;
}

template<typename Key, typename Value>
inline const std::pair<const Key&, Value&> BST<Key, Value>::Iterator::operator*()
{
	return std::pair<const Key&, Value&>(current_->key(), current_->value());
}

template<typename Key, typename Value>
inline void BST<Key, Value>::Iterator::leftmost(Node * ptr)
{
	while (ptr) {
		stack_.push(ptr);
		ptr = ptr->left();
	}
}

template<typename Key, typename Value>
inline Value & BST<Key, Value>::operator[](const Key & key)
{
	if (!root_) {
		root_ = new Node(key);
		return root_->value();
	}
	return root_->lookup(key);
}

template<typename Key, typename Value>
inline const Key & BST<Key, Value>::Node::key()
{
	return key_;
}

template<typename Key, typename Value>
inline Value & BST<Key, Value>::Node::value()
{
	return value_;
}

template<typename Key, typename Value>
inline Node * BST<Key, Value>::Node::left()
{
	return left_;
}

template<typename Key, typename Value>
inline Node * BST<Key, Value>::Node::right()
{
	return right_;
}

template<typename Key, typename Value>
inline int & BST<Key, Value>::Node::lookup(const Key key)
{
	if (key == key_) {
		return value();
	}
	if (key < key_) {
		if (!left_) {
			left_ = new Node(key);
			return left_->value();
		}
		else {
			return left_->lookup(key);
		}
	}
	if (key > key_) {
		if (!right_) {
			right_ = new Node(key);
			return right_->value();
		}
		else {
			return right_->lookup(key);
		}
	}
}
#endif