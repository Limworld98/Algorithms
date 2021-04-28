//require : expression Tree

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
        stack = new treeNode*[max]; 
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

void visit(struct treeNode* t)
{
    cout << t->info << " ";
}

void traverse(struct treeNode *t)
{
    if (t != z)
    {
        traverse(t->l);
        visit(t);
        traverse(t->r);
    }
}

int main()
{
    char c; Stack stack(50);
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

    traverse(stack.pop());
    cout << endl;
    return 0;
}