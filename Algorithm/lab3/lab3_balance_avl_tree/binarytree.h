#pragma once

#include <iostream>

class MyWindow;

template <typename T>
struct Node
{
	Node(T value, Node *parent) : 
		data_(value),
		left_(nullptr),
		right_(nullptr),
		parent_(parent),
        height(0)
	{
	}
    bool isLeftChildren()
    {
        return this == parent_->left_;
    }
	T data_;
	Node<T> *left_;
	Node<T> *right_;
	Node<T> *parent_;
	int height;
};

template <class T>
class BinaryTree
{
public:
	BinaryTree();
	virtual ~BinaryTree();

	int size() const;
	int count(T value) const;
	virtual void insert(T value);
	virtual void remove(T value);
	bool contains(T value);
	Node<T> *find(T value);
	void unique();
	void clear();
    T next(T value);
    T prev(T value);
    T min();
    T max();
	void print();

protected:
	virtual Node<T> *insertImpl(Node<T> *node, T value);
	virtual Node<T> *removeImpl(Node<T> *node, T value);
	Node<T> *containsImpl(Node<T> *node, T value);
	Node<T> *findImpl(Node<T> *node, T value);
	int countImpl(Node<T> *node, T value) const;
	Node<T> *minImpl(Node<T> *node);
	Node<T> *maxImpl(Node<T> *node);
	Node<T> *freeTree(Node<T> *node);
	void printImpl(Node<T> *node, int level);

	int size_;
	Node<T> *root_;

    friend MyWindow;
};

template <class T>
BinaryTree<T>::BinaryTree() 
	: size_ (0), root_ (nullptr)
{
}

template <class T>
BinaryTree<T>::~BinaryTree()
{
    clear();
}

template<class T>
inline int BinaryTree<T>::size() const
{
	return size_;
}

template<class T>
inline int BinaryTree<T>::count(T value) const
{
	return countImpl(root_, value);
}

template<class T>
inline void BinaryTree<T>::insert(T value)
{
	root_ = insertImpl(root_, value);
}

template<class T>
inline void BinaryTree<T>::remove(T value)
{
	removeImpl(root_, value);
}

template<class T>
inline bool BinaryTree<T>::contains(T value)
{
	return containsImpl(root_, value);
}

template<class T>
inline Node<T> * BinaryTree<T>::find(T value)
{
	return findImpl(root_, value);
}

template<class T>
inline void BinaryTree<T>::unique()
{
	Node<T> *node = this->min();
	
	while (node != nullptr) {
        int num = count(node->data_);
		if (num >= 2) {
            for (int i = 1; i < num; i++)
				this->remove(node->data_);

			node = this->min();
		} else {
            node = next(node);
		}
	}
}

template<class T>
inline void BinaryTree<T>::clear()
{
	root_ = freeTree(root_);
}

template<class T>
inline T BinaryTree<T>::next(T value)
{
    Node<T> *node = this->find(value);
    if (node != nullptr) {
        if (node->right_ != nullptr)
            return minImpl(node->right_)->data_;
        Node<T> *temp = node->parent_;
        while (temp != nullptr && node == temp->right_) {
            node = temp;
            temp = temp->parent_;
        }
        if (temp != nullptr)
            return temp->data_;
    }
    return T();
}

template<class T>
inline T BinaryTree<T>::prev(T value)
{
    Node<T> *node = this->find(value);
    if (node != nullptr) {
        if (node->left_ != nullptr)
            return maxImpl(node->left_)->data_;
        Node<T> *temp = node->parent_;
        while (temp != nullptr && node == temp->left_) {
            node = temp;
            temp = temp->parent_;
        }
        if (temp != nullptr)
            return temp->data_;
    }
    return T();
}

template<class T>
inline T BinaryTree<T>::min()
{
    return minImpl(root_)->data_;
}

template<class T>
inline T BinaryTree<T>::max()
{
    return maxImpl(root_)->data_;
}

template<class T>
inline void BinaryTree<T>::print()
{
	printImpl(root_, 0);
}

template<class T>
inline Node<T> *BinaryTree<T>::insertImpl(Node<T> *node, T value)
{
	if (node == nullptr) {
		++size_;
		node = new Node<T>(value, nullptr);
		return node;
	}
	else if (value < node->data_) {
		if (node->left_ == nullptr) {
			node->left_ = new Node<T>(value, node);
			++size_;
		} else {
			insertImpl(node->left_, value);
		}
	}
	else if (value >= node->data_) {
		if (node->right_ == nullptr) {
			node->right_ = new Node<T>(value, node);
			++size_;
		} else {
			insertImpl(node->right_, value);
		}
	}
	return node;
}

template<class T>
inline Node<T>* BinaryTree<T>::removeImpl(Node<T> *node, T value)
{
	if (node == nullptr)
		return node;
	if (value < node->data_)
		node->left_ = removeImpl(node->left_, value);
	else if (value > node->data_)
		node->right_ = removeImpl(node->right_, value);
	else if (node->left_ != nullptr && node->right_ != nullptr) {
		node->data_ = minImpl(node->right_)->data_;
		node->right_ = removeImpl(node->right_, node->data_);
	}
	else {
		Node<T> *temp = node;
		Node<T> *parent = node->parent_;
		if (node->left_ != nullptr) 
			node = node->left_;
		else 
			node = node->right_;
		
		delete temp;
		node->parent_ = parent;
		--size_;
	}
	return node;
}

template<class T>
inline Node<T>* BinaryTree<T>::containsImpl(Node<T>* node, T value)
{
	if (node == nullptr)
		return false;
	if (value == node->data_)
		return true;
	if (value < node->data_)
		return containsImpl(node->left_, value);
	else
		return containsImpl(node->right_, value);
}

template<class T>
inline Node<T>* BinaryTree<T>::findImpl(Node<T>* node, T value)
{
    if (node == nullptr)
        return  nullptr;
    if (value == node->data_)
		return node;
	if (value < node->data_)
		return findImpl(node->left_, value);
	else
		return findImpl(node->right_, value);
}

template<class T>
inline int BinaryTree<T>::countImpl(Node<T>* node, T value) const
{
	if (node == nullptr)
		return 0;
	if (node->data_ == value)
		return ((value < node->data_) ?
				countImpl(node->left_, value) : 
				countImpl(node->right_, value)) + 1;

	return ((value < node->data_) ?
			countImpl(node->left_, value) :
			countImpl(node->right_, value));
}

template<class T>
inline Node<T>* BinaryTree<T>::minImpl(Node<T> *node)
{
	if (node->left_ == nullptr)
		return node;
	return minImpl(node->left_);
}

template<class T>
inline Node<T>* BinaryTree<T>::maxImpl(Node<T> *node)
{
	if (node->right_ == nullptr)
		return node;
	return maxImpl(node->right_);
}

template<class T>
inline Node<T>* BinaryTree<T>::freeTree(Node<T>* node)
{
	if (node != nullptr) {
		freeTree(node->left_);
		freeTree(node->right_);
		delete node;
		--size_;
	}
	return nullptr;
}

template<class T>
inline void BinaryTree<T>::printImpl(Node<T>* node, int level)
{
	if (node != nullptr) {
		printImpl(node->left_, level + 1);
		for (int i = 0; i < level; i++)
			std::cout << "    ";

		std::cout << node->data_ << std::endl;
		printImpl(node->right_, level + 1);
	}
}
