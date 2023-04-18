/** \file queue.cpp
 *  \brief     This file contains queue implementation using pointers.
 *  \author    Sergei Rogov
 *  \date      18.04.2023
 *  \copyright University of Nicosia.
 */

#include <iostream>
using namespace std;

typedef double Entry;
enum errorCode {success, underflow, overflow};
struct Node {
    Entry entry;
    Node *next;
    Node();
    Node(int, Node* = NULL);
};

class Queue {
public:
    Queue();
    bool empty() const;
    errorCode retrieve(Entry &item) const;
    errorCode serve();
    errorCode retrieveAndServe(Entry &item);
    errorCode append(const Entry &item);
    void clear();
    int size() const;
    void print() const;
    ~Queue();
    Queue(const Queue &original);
    Queue& operator=(const Queue &original);
private:
    Node *front, *rear;
};

int main(){
    Queue Q, Q1, Q2;
    Entry x;
    for(int i=0; i<10; i++){
        Q.append(i);
    }
    Q.print();
    while(Q.retrieve(x) == success){
        Q.serve();
        Q1.append(x);
    }
    Q=Q1;
    Q1.print();
    Q2=Q1=Q;
    Q.print();
    Q1.print();
    Q2.print();
    Q2.clear();
    Q2.print();
    return 0;
}

Node::Node(){
    if (this != NULL)
        next = NULL;
}
 
Node::Node(int item, Node *n){
    if (this != NULL){
        entry = item;
        next = n;
    }
}

Queue::Queue(){
    front = rear = NULL;
}

bool Queue::empty() const{
    return front == NULL;
}

errorCode Queue::retrieve(Entry &item) const{
    if(empty()) return underflow;
    item = front->entry;
    return success;
}

errorCode Queue::serve(){
    if(empty()) return underflow;
    Node *temp = front;
    front = front->next;
    if(front == NULL)
        rear = NULL;
    return success;
}

errorCode Queue::retrieveAndServe(Entry &item){
    if(empty()) return underflow;
    item = front->entry;
    Node *temp = front;
    front = front->next;
    if(front == NULL)
        rear = NULL;
    return success;
}

errorCode Queue::append(const Entry &item){
    Node *temp = new Node(item);
    if (temp == NULL) return overflow;
    if (empty()) 
        front = temp;
    else
        rear->next = temp;
    rear = temp;
    return success;
}

void Queue::clear(){
    while(!empty())
        serve();
}

int Queue::size() const{
    int count = 0;
    Node *temp = front;
    while (temp != NULL){
        count++;
        temp = temp->next;
    }
    return count;
}

void Queue::print() const{
    if(empty()) cout << "Queue is empty!\n";
    else{
        Node *temp = front;
        while (temp != NULL){
            cout << temp->entry << " ";
            temp = temp->next;
        }
        cout << endl;
    }

}

Queue::~Queue(){
    while (!empty())
        serve();
}

Queue& Queue::operator=(const Queue &original){
    if (this != &original){
        while (!empty()) serve();
        if (original.front != NULL){
            Node *newCopy, *originalNode = original.front;
            front = newCopy = new Node(originalNode->entry);
            while (originalNode->next != NULL){
                originalNode = originalNode->next;
                newCopy->next = new Node(originalNode->entry);
                newCopy = newCopy->next;
            }
            rear = newCopy;
        }
    }
    return *this;
}

Queue::Queue(const Queue &original){
    Node *newCopy, *originalNode = original.front;
    if (originalNode == NULL) front = NULL;
    else{
        front = newCopy = new Node(originalNode->entry);
        while (originalNode->next != NULL){
            originalNode = originalNode->next;
            newCopy->next = new Node(originalNode->entry);
            newCopy = newCopy->next;
        }
        rear = newCopy;
    }
}