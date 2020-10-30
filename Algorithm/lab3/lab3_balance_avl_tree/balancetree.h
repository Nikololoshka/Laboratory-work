#pragma once

#include "binarytree.h"

template <class T>
class BalanceTree : public BinaryTree<T>
{
public:
    BalanceTree();
    void insert(T value) override;
    void remove(T value) override;

protected:
    Node<T> *insertImpl(Node<T> *node, T value) override;
    Node<T> *removeImpl(Node<T> *node, T value) override;
    Node<T> *removeMin(Node<T> *node);

    int height(Node<T> *node);
    Node<T> *singleRightRotate(Node<T> *node);
    Node<T> *singleLeftRotate(Node<T> *node);
    Node<T> *doubleRightRotate(Node<T> *node);
    Node<T> *doubleLeftRotate(Node<T> *node);
};

template<class T>
inline BalanceTree<T>::BalanceTree()
    : BinaryTree<T>()
{
}

template<class T>
inline void BalanceTree<T>::insert(T value)
{
    this->root_ = insertImpl(this->root_, value);
}

template<class T>
inline void BalanceTree<T>::remove(T value)
{
    this->root_ = removeImpl(this->root_, value);
}

template<class T>
inline Node<T>* BalanceTree<T>::insertImpl(Node<T>* node, T value)
{
    if (node == nullptr) {
        ++this->size_;
        return new Node<T>(value, nullptr);
    } else if (value < node->data_) {
        node->left_ = insertImpl(node->left_, value);
        if (height(node->left_) - height(node->right_) == 2) {
            if (value < node->left_->data_)
                node = singleRightRotate(node);
            else
                node = doubleRightRotate(node);
        }
    } else if (value > node->data_) {
        node->right_ = insertImpl(node->right_, value);
        if (height(node->right_) - height(node->left_) == 2) {
            if (value > node->right_->data_)
                node = singleLeftRotate(node);
            else
                node = doubleLeftRotate(node);
        }
    }
    node->height = std::max(height(node->left_), height(node->right_)) + 1;
    return node;
}

template<class T>
inline Node<T>* BalanceTree<T>::removeImpl(Node<T>* node, T value)
{
    if (node == nullptr)
        return nullptr;

    Node<T> *temp = nullptr;

    if (value < node->data_)
        node->left_ = removeImpl(node->left_, value);
    else if (value > node->data_)
        node->right_ = removeImpl(node->right_, value);
    else if (node->left_ != nullptr && node->right_ != nullptr) {
        temp = this->minImpl(node->right_);
        node->data_ = temp->data_;
        node->right_ = removeImpl(node->right_, node->data_);
    } else {
        temp = node;
        if (node->left_ == nullptr)
            node = node->right_;
        else if (node->right_ == nullptr)
            node =node->left_;

        delete temp;
    }
    if (node == nullptr)
        return  node;

    node->height = std::max(height(node->left_), height(node->right_)) +1 ;

    if(height(node->left_) - height(node->right_) == 2) {
        if(height(node->left_->left_) - height(node->left_->right_) == 1)
            return singleLeftRotate(node);
        else
            return doubleLeftRotate(node);
    } else if(height(node->right_) - height(node->left_) == 2) {
        if(height(node->right_->right_) - height(node->right_->left_) == 1)
            return singleRightRotate(node);
        else
            return doubleRightRotate(node);
    }
    return node;
}

template<class T>
inline Node<T>* BalanceTree<T>::removeMin(Node<T>* node)
{
    if (node->left_ == nullptr)
        return node->right_;
    node->left_ = removeMin(node->left_);
    return balance(node);
}


template<class T>
inline int BalanceTree<T>::height(Node<T>* node)
{
    return node != nullptr ? node->height : -1;
}


template<class T>
Node<T> *BalanceTree<T>::singleRightRotate(Node<T> *node)
{
    Node<T> *temp = node->left_;
    node->left_ = temp->right_;
    temp->right_ = node;
    node->height = std::max(height(node->left_), height(node->right_)) + 1;
    temp->height = std::max(height(node->left_), node->height) + 1;
    return temp;
}

template<class T>
Node<T> *BalanceTree<T>::singleLeftRotate(Node<T> *node)
{
    Node<T> *temp = node->right_;
    node->right_ = temp->left_;
    temp->left_ = node;
    node->height = std::max(height(node->left_), height(node->right_)) + 1;
    temp->height = std::max(height(node->right_), node->height) + 1;
    return temp;
}

template<class T>
Node<T> *BalanceTree<T>::doubleRightRotate(Node<T> *node)
{
    node->left_ = singleLeftRotate(node->left_);
    return singleRightRotate(node);
}

template<class T>
Node<T> *BalanceTree<T>::doubleLeftRotate(Node<T> *node)
{
    node->right_ = singleLeftRotate(node->right_);
    return singleRightRotate(node);
}
