/** \file stack.cpp
 *  \brief     This file contains stack implementation using pointers.
 *  \author    Sergei Rogov
 *  \date      16.04.2023
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

class Stack {
public:
    Stack();
    bool empty() const;
    errorCode top(Entry &) const;
    errorCode pop();
    errorCode topAndPop(Entry &);
    errorCode push(const Entry &);
    int size() const;
    void print() const;
    void clear();
    ~Stack();
    Stack(const Stack &original);
    Stack& operator=(const Stack &original);
private:
    Node *topNode;
};

int main(){
    Stack S, S1, S2;
    Entry x;
    for(int i=9; i>0; i--){
        S.push(i);
    }
    S1 = S2 = S;
    S.print();
    S1.print();
    S2.print();
    cout << "--------------\n";
    S1.topAndPop(x);
    cout << x << endl;
    S1.print();
    cout << "-------------- now\n";
    while(S2.top(x)==success){
        S2.print();
        cout << S2.size() << ' ';
        cout << x << endl;
        S2.pop();
        cout << "--------------\n";
    }
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

Stack::Stack(){
    topNode = NULL;
}

bool Stack::empty() const{
    return topNode == NULL;
}

errorCode Stack::top(Entry & item) const{
    if(empty()) return underflow;
    item = topNode->entry;
    return success;
}

errorCode Stack::pop(){
    if(empty()) return underflow;
    Node *temp = topNode;
    topNode = topNode->next;
    delete temp;
    return success;
}

errorCode Stack::topAndPop(Entry & item){
    if(empty()) return underflow;
    item = topNode->entry;
    Node *temp = topNode;
    topNode = topNode->next;
    delete temp;
    return success;
}

errorCode Stack::push(const Entry & item){
    Node *temp = new Node;
    if(temp==NULL) return overflow;
    temp->entry = item;
    temp->next = topNode;
    topNode = temp;
    return success;
}

int Stack::size() const{
    int count = 0;
    Node *temp = topNode;
    while(temp != NULL){
        count++;
        temp = temp -> next;
    }
    return count;
}

void Stack::print() const{
    Node *temp = topNode;
    while(temp != NULL){
        cout << temp->entry << " ";
        temp = temp -> next;
    }
    cout << endl;
}

void Stack::clear(){
    while(!empty())
        pop();
}

Stack::~Stack(){
    while (!empty())
        pop();
}

Stack& Stack::operator=(const Stack &original){
    if (this != &original){
        while (!empty()) pop();
        if (original.topNode != NULL){
            Node *newCopy, *originalNode = original.topNode;
            topNode = newCopy = new Node(originalNode->entry);
            while (originalNode->next != NULL){
                originalNode = originalNode->next;
                newCopy->next = new Node(originalNode->entry);
                newCopy = newCopy->next;
            }
        }
    }
    return *this;
}

Stack::Stack(const Stack &original){
    Node *newCopy, *originalNode = original.topNode;
    if (originalNode == NULL) topNode = NULL;
    else{
        topNode = newCopy = new Node(originalNode->entry);
        while (originalNode->next != NULL){
            originalNode = originalNode->next;
            newCopy->next = new Node(originalNode->entry);
            newCopy = newCopy->next;
        }
    }
}