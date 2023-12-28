#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;     
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList() {  
    if (head_ != nullptr && tail_ != nullptr) {
      tail_->next = nullptr;
      while (head_ != nullptr) {
        Node<T>* next = head_->next;
        delete head_;
        head_ = next;
      }
      tail_ = nullptr;
    }
  }

  void InsertInOrder(const T& data);
  void Reverse();

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

//=======================================================class definition
template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
  if (source.head_ == nullptr || source.tail_ == nullptr) {
    return;
  }
  head_ = new Node<T> (source.head_->data);
  Node<T>* current = head_;
  Node<T>* temp = source.head_->next;
  while (temp != source.head_) {
    current->next = new Node<T> (temp->data);
    temp = temp->next;
    current = current->next;
  }
  tail_ = current;
  tail_->next = head_;
  node_order_ = source.node_order_;
}

template<typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(const CircularLinkedList<T>& source) {
  if (&source == this || source.head_ == nullptr || source.tail_ == nullptr) {return *this;}
  if (head_ != nullptr && tail_ != nullptr) {   //delete
    tail_->next = nullptr;
    while (head_ != nullptr) {    
      Node<T>* next = head_->next;
      delete head_;
      head_ = next;
    }
  }
  head_ = new Node<T> (source.head_->data);   //deep copy;
  Node<T>* current = head_;
  Node<T>* temp = source.head_->next;
  while (temp != source.head_) {
    current->next = new Node<T> (temp->data);
    temp = temp->next;
    current = current->next;
  }
  tail_ = current;
  tail_->next = head_;
  node_order_ = source.node_order_;
  return *this;
}

template<typename T>
void CircularLinkedList<T>::Reverse() {
  if (node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
  } else {
    node_order_ = Order::kASC;
  }
  if (head_ == nullptr) return;
  Node<T>* current = head_;
  Node<T>* pre = tail_;
  while (current->next != head_) {
    Node<T>* next = current->next;
    current->next = pre;
    pre = current;
    current = next;
  }
  current->next = pre;
  tail_ = head_;
  head_ = current;
}

template<typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  if (head_ == nullptr && tail_ == nullptr) {head_ = new Node<T> (data); tail_ = head_;head_->next = tail_;tail_->next = head_;} else {
    auto* insert = new Node<T> (data);Node<T>* current = head_;
    if (node_order_ == Order::kASC) {
      if (current->data > data) {
        insert->next = head_;tail_->next = insert;head_ = insert;
      } else {
        while (current != tail_) {
          if (current->data <= data && current->next->data > data) {
            insert->next = current->next;
            current->next = insert;
            break;
          }
          current = current->next;
        }
        if (tail_->data <= data) {
          tail_->next = insert;
          insert->next = head_;
          tail_ = insert;
        }
      }
    } else {
      if (data >= current->data) {
        insert->next = head_;
        tail_->next = insert;
        head_ = insert;
      } else {
        while (current != tail_) {
          if (current->data > data && data >= current->next->data) {
            insert->next = current->next;
            current->next = insert;
            break;
          }
          current = current->next;
        }
        if (tail_->data > data) {tail_->next = insert;insert->next = head_;tail_ = insert;}
      }
    }
  }
}


#endif