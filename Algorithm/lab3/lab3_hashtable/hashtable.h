#pragma once

#include <list>
#include <vector>
#include <iostream>

template <class T>
class HashTable
{
public:
	HashTable();
	void insert(const char key, const T value);
	void remove(char key);
	void print();
	int size();

	T &operator[](char key);

private:
	const int CAPACITY;
	int computeHash(char value);
	int size_;
	std::vector<std::list<std::pair<char, T>>> table;
};

template <class T>
HashTable<T>::HashTable() : CAPACITY(17), size_(0) {
  table.resize(CAPACITY);
}

template <class T>
void HashTable<T>::insert(const char key, const T value) {
    table[computeHash(key)].emplace_back(key, value);
    ++size_;
}

template <class T>
void HashTable<T>::remove(char key) {
  table[computeHash(key)].remove_if(
      [&key](std::pair<char, T> &el) { return el.first == key; });
  --size_;
}

template <class T>
void HashTable<T>::print() {
  for (int i = 0; i < CAPACITY; ++i) {
	  std::cout << "[" << i << "] ";
    for (auto &j : table[i]) {
      std::cout << "[" << j.first << ", " << j.second << "] ";
    }
	std::cout << std::endl;
  }
}

template <class T>
int HashTable<T>::size() {
  return size_;
}

template <class T>
T &HashTable<T>::operator[](char key) {
  for (auto &el : table[computeHash(key)]) {
    if (el.first == key) return el.second;
  }
  this->insert(key, T());
  return table[computeHash(key)].back().second;
}

template <class T>
int HashTable<T>::computeHash(char value) {
  return static_cast<int>(value) % CAPACITY;
}
