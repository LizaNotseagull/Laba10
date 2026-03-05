#ifndef HEADER_H
#define HEADER_H

// ќбъ€влени€ классов

class Stack {
public:
    struct Node;
    Stack();
    Stack(const Stack& other);
    ~Stack();
    void Push(int data);
    void PushNode(Node* node);
    Node* PopNode();
    bool IsEmpty() const;
    int Top() const;
    void Print() const;
    Node* GetHead() const;
    void Clear();
private:
    Node* Head;
};

class Queue {
public:
    struct Node;
    Queue();
    Queue(const Queue& other);
    ~Queue();
    void Push(int data);
    int Pop();
    bool IsEmpty() const;
    Node* GetHead() const;
    Node* GetTail() const;
    void Print() const;
    void Clear();
private:
    Node* Head;
    Node* Tail;
};

class CommonList {
public:
    struct Node;
    CommonList();
    CommonList(const CommonList& other);
    ~CommonList();
    void PushBack(int data);
    Node* GetNode(int index) const;
    Node* InsertBeforeSecond(int M);
    void InsertSorted(int data);
    Node* GetLast() const;
    void Print() const;
    bool RemoveFirst(int val);
    Node* Find(int val) const;
    void Clear();
private:
    Node* Head;
};


void N_1();
void N_2();
void N_3();
void N_4();
void N_5();

#endif