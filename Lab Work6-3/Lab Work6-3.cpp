﻿#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <time.h>

#define infoNIL 0
#define itemMIN -1

using namespace std;

typedef int itemType;
typedef double infoType;

queue<int> myQueue;

class BST
{
private:
    struct node
    {
        itemType key;
        infoType info;

        struct node* l, * r;

        node(itemType k, infoType i, struct node* ll, struct node* rr)  // node 생성시 초기값 부여 가능 
        {
            key = k;
            info = i;
            l = ll;
            r = rr;
        };
    };
    struct node* head, * z; // z : List의 끝을 대표하는 node pointer – NULL에 해당
public:

    BST(int max)
    {
        z = new node(0, infoNIL, 0, 0);
        head = new node(itemMIN, infoNIL, z, z);
    }

    ~BST() {};

    infoType  BSTsearch(itemType v);
    void BSTinsert(itemType v, infoType info);
    infoType BSTdelete(itemType v);
    void Inorder();
    void InorderTra(node *t);
};

infoType BST::BSTsearch(itemType v)
{
    struct node* x = head->r;
    z->key = v;  // 아래 반복문을 간결히 만들기 위함

    while (v != x->key)
    {
        x = (v < x->key) ? x->l : x->r;
    }
    return x->info;
}

void BST::BSTinsert(itemType v, infoType info)
{
    struct node* p, * x;
    p = head;
    x = head->r;
    while (x != z)
    {
        p = x;
        x = (v < x->key) ? x->l : x->r;
        info = info + 1.0;
    }
    info = info + 1.0;
    x = new node(v, info, z, z);

    if (v < p->key)
    {
        p->l = x;
        info = info + 1.0;
    }
    else
    {
        p->r = x;
        info = info + 1.0;
    }
}

infoType BST::BSTdelete(itemType v)
{
    struct node* x = head->r, * p, * t, * c;
    p = head;

    while (x->key != v && x != z)
    {
        p = x;
        x = (v < x->key) ? x->l : x->r;
    }

    if (x == z)
        return x->info;
    else
        t = x;

    if (t->r == z)
        x = t->l;
    else if (t->r->l == z)
    {
        x = t->r;
        x->l = t->l;
    }
    else
    {
        c = x->r;

        while (c->l->l != z)
            c = c->l;

        x = c->l;
        c->l = x->r;
        x->l = t->l;
        x->r = t->r;
    }

    free(t);

    if (v < p->key)
        p->l = x;
    else
        p->r = x;

    return x->info;
}

void BST::InorderTra(node *t)
{
    if (t != z)
    {
        InorderTra(t->l);
        myQueue.push(t->key);
        InorderTra(t->r);      
    }
}

void BST::Inorder()
{
    struct node* p, * x;
    p = head;
    x = head->r;
    InorderTra(x);
}


void initRandAry(int** t, int num)
{
    for (int i = 0; i < num; i++)
    {
        t[i] = new int[2];
        t[i][0] = (1 + rand() % num);
        t[i][1] = i + 1;
    }

    vector<vector<int>>ary(num, vector<int>(2, 0));

    for (int i = 0; i < num; i++)
    {
        ary[i][0] = t[i][0];
        ary[i][1] = t[i][1];
    }

    sort(ary.begin(), ary.end());

    for (int i = 0; i < num; i++)
    {
        t[i][0] = ary[i][0];
        t[i][1] = ary[i][1];
    }
}

void showAry(int* t)
{
    for (int i = 0; i < 20; i++)
        cout << t[i] << " ";
    cout << "\n";
}

int main()
{
    //----------------------------------init arrays
    srand((unsigned)time(NULL));

    int* a, ** temp, n, ntemp; // for dynamic allocation
    infoType myInfo = 0.0, infoSum = 0.0;

    cin >> n;
    a = new int[n];
    temp = new int* [n];
    initRandAry(temp, n);

    for (int i = 0; i < n; i++)
    {
        a[i] = temp[i][1];
    }

    BST T1(n);
    BST T3(n);

    //----------------------------------input data
    //1. T1생성후 Inorder한다
    //2. Inorder하며 key를 queue에 넣어준다
    //3. front & pop 하며 T3를 생성한다.

    for (int i = 0; i < n; i++)
    {
        T1.BSTinsert(a[i], myInfo);
        myInfo = 0.0;
    }

    T1.Inorder();

    while (myQueue.empty() == false)
    {
        T3.BSTinsert(myQueue.front(), myInfo);
        myQueue.pop();
        myInfo = 0.0;
    }

    for (int i = 0; i < n; i++)
    {
        infoSum += T1.BSTsearch(a[i]);
    }

    cout << "T1 :" << infoSum / (double)n << endl;

    for (int i = 0; i < n; i++)
    {
        infoSum += T3.BSTsearch(a[i]);
    }

    cout << "T3 :" << infoSum / (double)n;

    //----------------------------------free arrays

    for (int i = 0; i < n; i++)
        delete[] temp[i];

    delete[] a;
    delete[] temp;
}
