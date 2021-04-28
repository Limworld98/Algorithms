#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <time.h>

#define infoNIL 0
#define itemMIN -1
#define black 0
#define red 1

using namespace std;

queue<int> myQueue;

typedef int itemType;
typedef double infoType;

class RBtree
{
private:
    struct node {
        itemType key, tag;
        infoType Info;
        struct node* l, * r;
        node(itemType k, infoType i, itemType t, struct node* ll, struct node* rr)
        {
            key = k; Info = i; tag = t; l = ll; r = rr;
        }
    };

    struct node* head, * tail, * x, * p, * g, * gg, * z;
public:
    RBtree(int max)
    {
        z = new node(0, infoNIL, black, 0, 0);
        z->l = z;
        z->r = z;
        head = new node(itemMIN, infoNIL, black, z, z);
    }

    void insert(itemType k, infoType* i)
    {
        x = head; p = head; g = head;
        while (x != z)
        {
            gg = g;
            g = p;
            p = x;

            x = (k < x->key) ? x->l : x->r;
            if (x->l->tag && x->r->tag)
            {
                split(k);
            }
            *i += 1.0;
        }
        x = new node(k, *i, red, z, z);
        if (k < p->key)
            p->l = x;
        else
            p->r = x;

        split(k);
        head->r->tag = black;
    }

    struct node* rotate(itemType k, struct node* y)
    {
        struct node* high, * low;
        high = (k < y->key) ? y->l : y->r;
        if (k < high->key)
        {
            low = high->l;
            high->l = low->r;
            low->r = high;
        }

        else
        {
            low = high->r;
            high->r = low->l;
            low->l = high;
        }
        if (k < y->key)
            y->l = low;
        else y->r =
            low;

        return low;
    }

    void split(itemType k)
    {
        x->tag = red;
        x->l->tag = black;
        x->r->tag = black;

        if (p->tag)
        {
            g->tag = red;
            if (k < g->key != k < p->key)
                p = rotate(k, g);
            x = rotate(k, gg);
            x->tag = black;
        }
    }

    infoType search(itemType k, infoType* i)
    {
        // Red-Black Tree의 값을 탐색 기능 구현
        struct node* x = head->r;
        z->key = k;  

        while (k != x->key)
        {
            x = (k < x->key) ? x->l : x->r;
            *i += 1.0;
        }

        return *i;
    }
};

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

    infoType  BSTsearch(itemType v, infoType* info);
    void BSTinsert(itemType v, infoType* info);
    infoType BSTdelete(itemType v);
    void Inorder();
    void InorderTra(node* t);
};

infoType BST::BSTsearch(itemType v, infoType* info)
{
    struct node* x = head->r;
    z->key = v;  // 아래 반복문을 간결히 만들기 위함

    while (v != x->key)
    {
        x = (v < x->key) ? x->l : x->r;
    }
    return x->info;
}

void BST::BSTinsert(itemType v, infoType* info)
{

    struct node* p, * x;
    p = head;
    x = head->r;
    while (x != z)
    {
        p = x;
        x = (v < x->key) ? x->l : x->r;
        *info = *info + 1.0;
    }
    *info = *info + 2.0; //이후 추가적인 비교까지 미리 추가한다.

    x = new node(v, *info, z, z);

    if (v < p->key)
    {
        p->l = x;
    }
    else
    {
        p->r = x;
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

void BST::InorderTra(node* t)
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

    int* a, * b, ** temp, n; // for dynamic allocation
    infoType myInfo = 0.0, infoSum = 0.0, t1_sum = 0.0, t2_sum = 0.0, t3_sum = 0.0;

    cin >> n;
    a = new int[n];
    b = new int[n];
    temp = new int* [n];
    initRandAry(temp, n);

    for (int i = 0; i < n; i++)
    {
        a[i] = temp[i][1];
    }

    for (int i = 0; i < n; i++)
    {
        b[i] = i + 1;
    }

    BST T1(n);
    BST T2(n);
    RBtree T3(n);

    //----------------------------------input data
    //1. T1생성후 Inorder한다
    //2. Inorder하며 key를 queue에 넣어준다
    //3. front & pop 하며 T2,T3를 생성한다.

    for (int i = 0; i < n; i++)
    {
        T1.BSTinsert(a[i], &myInfo);
        t1_sum += myInfo;
        myInfo = 0.0;
    }

    T1.Inorder();

    while (myQueue.empty() == false)
    {
        T2.BSTinsert(myQueue.front(), &myInfo);
        t2_sum += myInfo;
        myInfo = 0.0;
        T3.insert(myQueue.front(), &myInfo);
        t3_sum += myInfo;
        myInfo = 0.0;
        myQueue.pop();
    }
    cout << "T1의 구축 시 평균 비교 횟수:" << t1_sum / (double)n << endl;
    cout << "T2의 구축 시 평균 비교 횟수:" << t2_sum / (double)n << endl;
    cout << "T3의 구축 시 평균 비교 횟수:" << t3_sum / (double)n << endl;

    for (int i = 0; i < n; i++)
    {
        infoSum += T1.BSTsearch(b[i], &myInfo);
        myInfo = 0.0;
    }

    cout << "T1의 평균 탐색 비교 횟수:" << infoSum / (double)n << endl;

    infoSum = 0.0;

    for (int i = 0; i < n; i++)
    {
        infoSum += T2.BSTsearch(b[i], &myInfo);
        myInfo = 0.0;
    }

    cout << "T2의 평균 탐색 비교 횟수:" << infoSum / (double)n << endl;

    infoSum = 0.0;

    for (int i = 0; i < n; i++)
    {
        infoSum += T3.search(b[i], &myInfo);
        myInfo = 0.0;
    }

    cout << "T3의 평균 탐색 비교 횟수:" << infoSum / (double)n << endl;

    //----------------------------------free arrays

    for (int i = 0; i < n; i++)
        delete[] temp[i];

    delete[] a;
    delete[] temp;
}
