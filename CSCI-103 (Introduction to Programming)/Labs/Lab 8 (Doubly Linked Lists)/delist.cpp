// TA Zachary helped me
// First, used no tail pointer but had pesky bug
// Now using tail pointer

#include "delist.h"
#include <cstddef>
#include <iostream>

using namespace std;

// Constructs an empty Double-Ended List
DEList::DEList()
{
  head = NULL;
  tail = NULL;
  count = 0;
}

// Destructor to clean-up memory of current list
DEList::~DEList()
{
  DEItem* curr = head;
  while(curr != NULL)
  {
   DEItem* temp = curr->next;
   delete curr;
   curr = temp;
  }
}

// returns a Boolean 'true' if the list is empty
bool DEList::empty()
{
  if(head != NULL)
  {
    return false;
  }
  else {
    return true;
  }
}

// returns number of items in the list
int DEList::size()
{
  return count; // constant time
}

// returns front item or -1 if empty list
int DEList::front()
{
  if(head == NULL)
  {
    return -1;
  }
  return head -> val;
}

// returns back item or -1 if empty list
int DEList::back()
{
  if(head == NULL)
  {
    return -1;
  }
  return tail -> val;
}

// Adds a new integer to the front of the list
void DEList::push_front(int new_val)
{
  if(head==NULL)
  {
    head = new DEItem;
    head -> val = new_val;
    head -> next = NULL;
    tail = head;
  }
  else
  {
    DEItem* temp = new DEItem;
    temp -> val = new_val;
    temp -> next = head; // Makes this the first element.
    temp -> prev = NULL;
    head -> prev = temp; // Changes head
    head = temp;
  }
  count++; // Element count
}

// Adds a new integer to the back of the list
void DEList::push_back(int new_val)
{
  if(count == 0)
  {
    head = new DEItem;
    head -> val = new_val;
    head -> next = NULL;
    tail = head;
  }
  else
  {
    DEItem* temp = new DEItem;
    temp -> val = new_val;
    tail -> next = temp; // Changes tail to end value
    temp -> next = NULL; // Last value ends with NULL
    temp -> prev = tail;
    tail = temp;
  }
  count++;
}

// Removes the front item of the list (if it exists)
void DEList::pop_front()
{
  if(head != NULL)
  {
    DEItem* curr = head;
    head = curr -> next;
    curr -> prev = NULL;
    delete curr;
    count--;
  }
}

// Removes the back item of the list (if it exists)
void DEList::pop_back()
{
  if(tail != NULL)
  {
    DEItem* curr = tail;
    tail = curr -> prev;
    delete curr;
    count--;
    if(count==0)
    {
      head = tail;
    }
  }
}