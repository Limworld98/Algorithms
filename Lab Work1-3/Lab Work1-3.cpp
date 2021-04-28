#include <iostream>

using namespace std;

template<typename itemType>
class Node 
{
public :
    itemType key;
    Node<itemType>* next = NULL;
    Node() {};
    ~Node() {};
};


template <typename itemType>
class Stack2 
{
public:
    Stack2() 
    {
        head = NULL;
    };
    ~Stack2();
    void push(itemType v);
    itemType pop();
    int empty();
private:
    Node<itemType>* head;
};


template<typename itemType>
Stack2<itemType>::~Stack2()
{
    head = NULL;
}

template <typename itemType>
void Stack2<itemType>::push(itemType v) 
{
    Node<itemType>* mynode = new Node<itemType>;
    mynode->key = v;

    if (empty())
    {
        head = mynode;
    }
    else
    {
        mynode->next = head;
        head = mynode;
    }
}

template<typename itemType>
itemType Stack2<itemType>::pop()
{
    if (empty())
    {
        cout << "enter precise expression\n";
    }
    else
    {
        Node<itemType>* temp = head;
        head = head->next;
        return temp->key;
    }
}

template<typename itemType>
int Stack2<itemType>::empty()
{
    if (head == NULL)
    {
        return 1;
    }
    else
        return 0;
}

int main() {
    char c; Stack2<double> acc; double x,y,z;
    while ((c = cin.get()) != '\n')
    {
        x = 0;
        while (c == ' ')
            cin.get(c);

        if (c == '+')
            x = acc.pop() + acc.pop();
        if (c == '-')
        {
            y = acc.pop();
            z = acc.pop();
            x = z - y;
        }
        if (c == '*')
            x = acc.pop() * acc.pop();
        if (c == '/')
        {
            y = acc.pop();
            z = acc.pop();
            x = z / y;
        }
        while (c >= '0' && c <= '9')
        {
            x = 10 * x + (c - '0');
            cin.get(c);
        }
        acc.push(x);
    }
    cout << fixed;
    cout.precision(2);
    cout << acc.pop() << "\n";
}