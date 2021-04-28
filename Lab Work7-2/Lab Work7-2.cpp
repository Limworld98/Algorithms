#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>

#define infoNIL 0
#define itemMIN -1
#define black 0
#define red 1

using namespace std;

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

class HashTable 
{
private:
    struct node
    {
        itemType id;
        infoType info;
        node* next;
        node(itemType key, infoType i) 
        { 
            id = key; 
            info = i; 
            next = NULL; }
    };

    int size;
    node** List;   

public:
    HashTable(int max) :size(max)
    {
        List = new node * [max];
    }

    void insert(itemType key, infoType info, infoType *i)
    {
        int h_key = key % size;
        node* temp = new node(key, info);

        if (List[h_key] == NULL) 
        { 
            List[h_key] = temp; 
        }
        else 
        {
            temp->next = List[h_key];
            List[h_key] = temp;
        }
    }

    infoType search(itemType key, infoType *i)
    {
        int h_key = key % size;

        node* temp = List[h_key];

        while ((temp != NULL) && (*i += 1.0))
        {
            if (temp->id == key)
            {
                return temp->info;
            }
            else
            {
                temp = temp->next;
            }         
        }
        return NULL;
    }

};

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

    int* a,** temp, n, ntemp; // for dynamic allocation
    infoType myInfo = 0.0, t3cnt = 0.0, h11cnt = 0.0, h101cnt = 0.0, h1009cnt = 0.0;

    cin >> n;
    a = new int[n];
    temp = new int* [n];
    initRandAry(temp, n);

    for (int i = 0; i < n; i++)
    {
        a[i] = temp[i][1];
    }


    RBtree T3(n);
    HashTable h11(11), h101(101), h1009(1009);
    
    //----------------------------------build

    for (int i = 0; i < n; i++)
    {
        T3.insert(a[i], &myInfo);
        t3cnt += myInfo;
        myInfo = 0.0;
        h11.insert(a[i],i, &myInfo);
        h11cnt += myInfo;
        myInfo = 0.0;
        h101.insert(a[i], i, &myInfo);
        h101cnt += myInfo;
        myInfo = 0.0;
        h1009.insert(a[i], i, &myInfo);
        h1009cnt += myInfo;
        myInfo = 0.0;
    }

    cout << "T3의 구축 시 평균 비교 회수 :" << t3cnt / (double)n << endl;
    cout << "Hash Table 크기가 11인 경우의 구축시 평균 비교 회수 :" << h11cnt / (double)n << endl;
    cout << "Hash Table 크기가 101인 경우의 구축시 평균 비교 회수 :" << h101cnt / (double)n << endl;
    cout << "Hash Table 크기가 1009인 경우의 구축시 평균 비교 회수 :" << h1009cnt / (double)n << endl;

    t3cnt = 0.0;
    h11cnt = 0.0;
    h101cnt = 0.0;
    h1009cnt = 0.0;

    //---------------------------------search 

    for (int i = 1; i <= n; i++)
    {
        T3.search(i, &myInfo);
        t3cnt += myInfo;
        myInfo = 0.0;
        h11.search(i, &myInfo);
        h11cnt += myInfo;
        myInfo = 0.0;
        h101.search(i, &myInfo);
        h101cnt += myInfo;
        myInfo = 0.0;
        h1009.search(i, &myInfo);
        h1009cnt += myInfo;
        myInfo = 0.0;
    }

    cout << "T3의 평균 비교 회수 :" << t3cnt / (double)n << endl;
    cout << "Hash Table크기가 11인 경우 평균 비교 회수 :" << h11cnt / (double)n << endl;
    cout << "Hash Table크기가 101인 경우 평균 비교 회수 :" << h101cnt / (double)n << endl;
    cout << "Hash Table크기가 1009인 경우 평균 비교 회수 :" << h1009cnt / (double)n << endl;

    //----------------------------------free arrays

    for (int i = 0; i < n; i++)
        delete[] temp[i];

    delete[] a;
    delete[] temp;
}
