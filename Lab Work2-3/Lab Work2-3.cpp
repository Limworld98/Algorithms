// require : expression tree with search system(print level)

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

int getLevelUtil(struct treeNode* t, char data, int level)
{
    if (t == z)
        return 0;

    if (t->info == data)
        return level;

    int downlevel = getLevelUtil(t->l, data, level + 1);
    
    if (downlevel != 0)
        return downlevel;

    downlevel = getLevelUtil(t->r, data, level + 1);
    return downlevel;
}

int getLevel(struct treeNode* t, char data)
{
    return getLevelUtil(t, data, 1);
}

int main()
{
    char c,key; Stack stack(50);
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


    treeNode* t = stack.pop();

    
    cin >> key;
    // search level of keynode
    int level = getLevel(t, key);

    if (level)
        cout << getLevel(t, key) << endl;
    else
        cout << "not found" << endl;

    return 0;
}