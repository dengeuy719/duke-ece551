#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    // the first addfront
    IntList il;
    //[0]
    il.addFront(0);
    IntList::Node * l1 = il.head;
    assert(il.head != NULL);
    assert(il.head == il.tail);
    assert(il.getSize() == 1);
    assert(il[0] == 0);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    //l1
    assert(l1->data == 0);
    assert(l1->next == NULL);
    assert(l1->prev == NULL);
    //[1,0]
    il.addFront(1);
    IntList::Node * l2 = il.head;
    assert(il.head != NULL);
    assert(il.tail == l1);
    assert(il.getSize() == 2);
    assert(il[0] == 1);
    assert(il[1] == 0);
    //l2
    assert(l2->data == 1);
    assert(l2->next == l1);
    assert(l2->prev == NULL);
    //l1
    assert(l1->data == 0);
    assert(l1->next == NULL);
    assert(l1->prev == l2);
    //[1,0,2]
    il.addBack(2);
    IntList::Node * l3 = il.tail;
    assert(il.head == l2);
    assert(il.tail != NULL);
    assert(il.getSize() == 3);
    assert(il[0] == 1 && il[1] == 0 && il[2] == 2);
    //l3
    assert(l3->data == 2);
    assert(l3->next == NULL);
    assert(l3->prev == l1);
    //l1
    assert(l1->data == 0);
    assert(l1->next == l3);
    assert(l1->prev == l2);
    //l2
    assert(l2->data == 1);
    assert(l2->next == l1);
    assert(l2->prev == NULL);
  }
  // many more tester methods
  void testAddBack() {
    IntList il;
    //[0]
    il.addBack(0);
    IntList::Node * l1 = il.tail;
    assert(il.head != NULL && il.head == il.tail);
    assert(il.getSize() == 1);
    assert(il.head->data == 0);
    assert(il.head->next == NULL);
    assert(il.head->prev == NULL);
    assert(il[0] == 0);
    //l1
    assert(l1->data == 0);
    assert(l1->next == NULL);
    assert(l1->prev == NULL);
    //[0,1]
    il.addBack(1);
    IntList::Node * l2 = il.tail;
    assert(il.head == l1);
    assert(il.tail != NULL);
    assert(il.getSize() == 2);
    assert(il[0] == 0);
    assert(il[1] == 1);
    //l2
    assert(il.tail->data == 1);
    assert(il.tail->next == NULL);
    assert(il.tail->prev == l1);
    //l1
    assert(l1->data == 0);
    assert(l1->next == l2);
    assert(l1->prev == NULL);
    //[2,0,1]
    il.addFront(2);
    IntList::Node * l3 = il.head;
    assert(il.head != NULL);
    assert(il.tail == l2);
    assert(il.getSize() == 3);
    assert(il[0] == 2 && il[1] == 0 && il[2] == 1);
    //l1
    assert(l1->data == 0);
    assert(l1->next == l2);
    assert(l1->prev == l3);
    //l2
    assert(l2->data == 1);
    assert(l2->next == NULL);
    assert(l2->prev == l1);
    //l3
    assert(l3->data == 2);
    assert(l3->next == l1);
    assert(l3->prev == NULL);
  }
  void testRemove() {
    IntList il;
    il.addBack(0);
    IntList::Node * l0 = il.tail;
    il.addBack(1);
    IntList::Node * l1 = il.tail;
    il.addBack(2);
    il.addBack(3);
    IntList::Node * l3 = il.tail;
    //0 1 2 3
    assert(il.remove(4) == false);
    assert(il.remove(2) == true);
    //0 1   3
    assert(il.head == l0);
    assert(il.tail == l3);
    assert(il.getSize() == 3);
    assert(il[0] == 0 && il[1] == 1 && il[2] == 3);
    //l0
    assert(l0->data == 0);
    assert(l0->next == l1);
    assert(l0->prev == NULL);
    //l1
    assert(l1->data == 1);
    assert(l1->next == l3);
    assert(l1->prev == l0);
    //l3
    assert(l3->data == 3);
    assert(l3->next == NULL);
    assert(l3->prev == l1);

    assert(il.remove(3) == true);
    //0 1
    assert(il.head == l0);
    assert(il.tail == l1);
    assert(il.getSize() == 2);
    assert(il[0] == 0 && il[1] == 1);
    //l1
    assert(l1->data == 1);
    assert(l1->next == NULL);
    assert(l1->prev == l0);
    //l0
    assert(l0->data == 0);
    assert(l0->next = l1);
    assert(l0->prev == NULL);
    //   1
    assert(il.remove(0) == true);
    assert(il.head == l1);
    assert(il.tail == l1);
    assert(il.getSize() == 1);
    assert(il[0] == 1);
    //l1
    assert(l1->data == 1);
    assert(l1->next == NULL);
    assert(l1->prev == NULL);
    //
    assert(il.remove(1) == true);
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  void testCopy() {
    IntList * il1 = new IntList();
    il1->addBack(1);
    IntList * il2 = new IntList();
    il2->addBack(1);
    assert(il1->head != il2->head);
    assert(il1->tail != il2->tail);
    IntList * il3 = new IntList(*il1);
    assert(il1->head != il3->head);
    assert(il1->tail != il3->tail);
    il3->addBack(2);
    *il2 = *il3;
    assert(il2->getSize() == 2);
    assert(il3->head != il2->head);
    assert(il3->tail != il2->tail);
    delete il1;
    delete il2;
    delete il3;
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testRemove();
  t.testCopy();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
