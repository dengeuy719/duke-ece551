#ifndef _BSTMAP_H__
#define _BSTMAP_H__

#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "assert.h"
#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node(K key, V value) : key(key), value(value), left(NULL), right(NULL) {}
  };
  Node * root;

  static Node * const & find(Node * const & cur, const K key) {
    if (cur == NULL) {
      return cur;
    }

    if (key < cur->key) {
      return find(cur->left, key);
    }
    else if (key > cur->key) {
      return find(cur->right, key);
    }
    else {
      return cur;
    }
  }
  static Node *& find(Node *& cur, const K key) {
    return const_cast<Node *&>(find(const_cast<Node * const &>(cur), key));
  }
  const K minGreaterKey(Node *& cur) {
    assert(cur != NULL);
    assert(cur->right != NULL);

    Node * finder = cur->right;
    K res = finder->key;

    while (finder->left != NULL) {
      finder = finder->left;
      res = finder->key;
    }
    return res;
  }
  void deleteall(Node *& cur) {
    if (cur != NULL) {
      deleteall(cur->left);
      deleteall(cur->right);
      delete cur;
      cur = NULL;
    }
  }

 public:
  BstMap() : root(NULL) {}

  void add(const K & key, const V & value) {
    Node *& nodeToAdd = find(root, key);
    if (nodeToAdd == NULL) {
      nodeToAdd = new Node(key, value);
    }
    else {
      nodeToAdd->value = value;
    }
  }

  const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * const & nodeToLookUp = find(root, key);
    if (nodeToLookUp == NULL) {
      throw std::invalid_argument("cannot find key");
    }
    else {
      return nodeToLookUp->value;
    }
  }

  void remove(const K & key) {
    Node *& nodeToRemove = find(root, key);
    if (nodeToRemove == NULL) {
      throw std::invalid_argument("cannot find key");
    }
    else {
      if (nodeToRemove->left == NULL) {
        Node * temp = nodeToRemove->right;
        delete nodeToRemove;
        nodeToRemove = temp;
      }
      else if (nodeToRemove->right == NULL) {
        Node * temp = nodeToRemove->left;
        delete nodeToRemove;
        nodeToRemove = temp;
      }
      else {
        K mgKey = minGreaterKey(nodeToRemove);
        V mgValue = lookup(mgKey);
        remove(mgKey);
        nodeToRemove->key = mgKey;
        nodeToRemove->value = mgValue;
      }
    }
  }

  ~BstMap<K, V>() { deleteall(root); }

  void inorder() { inorderRev(root); }

  void inorderRev(Node * root) {
    if (root != NULL) {
      inorderRev(root->left);
      std::cout << root->key << ", ";
      inorderRev(root->right);
    }
  }
};

#endif
