#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
class indexOutOfRangeException : public std::exception {
 public:
  virtual const char * what() const throw() { return "Index out of range"; };
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(0), next(NULL), prev(NULL) {}
    Node(const T & data, Node * next, Node * prev) : data(data), next(next), prev(prev) {}
  };
  Node * head;
  Node * tail;
  int size;

 public:
  LinkedList() : head(NULL), tail(NULL), size(0) {}

  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * n = rhs.head;
    while (n != NULL) {
      addBack(n->data);
      n = n->next;
    }
  }

  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      while (head != NULL) {
        Node * temp = head->next;
        delete head;
        head = temp;
      }
      tail = NULL;
      size = 0;
      Node * n = rhs.head;
      while (n != NULL) {
        addBack(n->data);
        n = n->next;
      }
      size = rhs.size;
    }
    return *this;
  }

  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
  }

  int getSize() const { return size; }

  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }
  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }
  Node * removeHelper(const T & item, Node * cur) {
    if (cur == NULL) {
      return NULL;
    }
    if (item == cur->data) {
      Node * ans = cur->next;
      delete cur;
      return ans;
    }
    cur->next = removeHelper(item, cur->next);
    return cur;
  }
  bool remove(const T & item) {
    head = removeHelper(item, head);
    if (head != NULL) {
      return true;
    }
    else {
      return false;
    }
  }
  T & operator[](int index) {
    if (index < 0 || index >= size) {
      throw indexOutOfRangeException();
    }
    else {
      Node * cur = head;
      for (int i = 0; i < index; i++) {
        cur = cur->next;
      }
      return cur->data;
    }
  }
  const T & operator[](int index) const {
    if (index < 0 || index >= size) {
      throw indexOutOfRangeException();
    }
    else {
      Node * cur = head;
      for (int i = 0; i < index; i++) {
        cur = cur->next;
      }
      return cur->data;
    }
  }
  int find(const T & item) {
    int ans = 0;
    Node * cur = head;
    while (cur != NULL) {
      if (cur->data == item) {
        return ans;
      }
      cur = cur->next;
      ans++;
    }
    return -1;
  }
};

#endif
