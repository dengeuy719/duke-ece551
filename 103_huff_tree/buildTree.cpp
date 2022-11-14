#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t q;
  for (size_t i = 0; i < 257; ++i) {
    if (counts[i] != 0) {
      q.push(new Node(i, counts[i]));
    }
  }
  while (q.size() > 1) {
    Node * l = q.top();
    q.pop();
    Node * r = q.top();
    q.pop();
    Node * newNode = new Node(l, r);
    q.push(newNode);
  }
  Node * root = q.top();
  return root;
}
