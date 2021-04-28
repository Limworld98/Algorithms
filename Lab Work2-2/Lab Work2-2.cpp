#include <iostream>

using namespace std;

typedef int itemType;

struct treeNode
{
    char info;
    struct treeNode* l, * r;
};

struct treeNode* x, * z;

class Stack
{
public:
    Stack(int max = 100)
    {
        stack = new treeNode * [max];
        p = 0;
    };
    ~Stack() {};
    inline void push(treeNode* v) { stack[p++] = v; };
    inline treeNode* pop() { return stack[--p]; };
    inline int empty() { return !p; };
private:
    treeNode** stack;
    int p;
};

class Queue
{
public:
    Queue(int max = 100)
    {
        queue = new treeNode * [max];
        head = 0;
        tail = 0;
        size = 0;
    };
    ~Queue() {};
    void put(treeNode* v);
    treeNode* get();
    int empty();
private:
    treeNode** queue;
    int head,tail,size;
};


void Queue::put(treeNode* v)
{
    queue[tail++] = v;
}

treeNode* Queue::get()
{
    treeNode* t = queue[head++];
    return t;
}

int Queue::empty() 
{
    if (head == tail)
        return 1;
    else
        return 0;
}

void visit(struct treeNode* t)
{
    cout << t->info << " ";
}

int main()
{
    char c; Queue queue(50); Stack stack(50);
    z = new treeNode;
    z->l = z;
    z->r = z;

    while ((c = cin.get()) != '\n')
    {
        while (c == ' ')
            cin.get(c);

        x = new treeNode;
        x->info = c;
        x->l = z;
        x->r = z;

        if (c == '+' || c == '*' || c == '-')
        {
            x->r = stack.pop();
            x->l = stack.pop();
        }
        stack.push(x);
    }

    // make expression tree

    treeNode* t = stack.pop();

    queue.put(t); //put top of stack into queue
    while (!queue.empty())
    {
        t = queue.get();
        visit(t);
        if (t->l != z) 
            queue.put(t->l);
        if (t->r != z) 
            queue.put(t->r);
    }
    cout << endl;
    return 0;
}