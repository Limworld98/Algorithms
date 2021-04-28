#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>
using namespace std;

void heapify(int *ary, int n, int i, long long int* com, long long int* mov)
{
    int cur = 2 * i;

    if (cur < n && ary[cur] < ary[cur + 1]) 
        cur++;

    if (ary[i] < ary[cur])
    {
        swap(ary[i], ary[cur]);
        if (cur <= n / 2) 
            heapify(ary,n,cur,com,mov);
    }
}

void heapsort(int *ary, int i, long long int* com, long long int* mov)
{
    swap(ary[1], ary[i]);
    (*mov)++;
    int root = 1;
    int cur = 2;

    while (cur / 2 < i)
    {
        cur = 2 * root;
        if (cur < i - 1 && ary[cur] < ary[cur + 1])
        {        
            cur++;
        }
        (*com)++;
        if (cur < i && ary[root] < ary[cur])
        {
            swap(ary[root], ary[cur]);
            (*mov)++;
        }
        (*com)++;
        root = cur;
    }
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
    for (int i = 1; i <= 20; i++)
        cout << t[i] << " ";
    cout << "\n";
}

int main()
{
    //----------------------------------init arrays
    srand((unsigned)time(NULL));

    int* a, * b, *c, ** temp, n, ntemp; // for dynamic allocation
    long long int CompareCntA = 0, CompareCntB = 0, CompareCntC = 0, MoveCntA = 0, MoveCntB = 0, MoveCntC = 0; // for counting

    cin >> n;
    a = new int[n+1];
    temp = new int* [n];
    initRandAry(temp, n);

    b = new int[n+1];
    c = new int[n+1];

    ntemp = n;
    for (int i = 1; i <= n; i++)
    {
        a[i] = ntemp--;
    }

    for (int i = 0; i < n; i++)
    {
        b[i+1] = temp[i][1];
    }

    for (int i = 1; i <= n; i++)
    {
        c[i] = (1 + rand() % n);
    }



    //----------------------------------sorting
    
    for (int i = n / 2; i > 0; i--)
        heapify(a,n,i,&CompareCntA,&MoveCntA);
    for (int i = n; i > 0; i--)
        heapsort(a,i, &CompareCntA, &MoveCntA);

    for (int i = n / 2; i > 0; i--)
        heapify(b, n, i, &CompareCntB, &MoveCntB);
    for (int i = n; i > 0; i--)
        heapsort(b, i, &CompareCntB, &MoveCntB);

    for (int i = n / 2; i > 0; i--)
        heapify(c, n, i, &CompareCntC, &MoveCntC);
    for (int i = n; i > 0; i--)
        heapsort(c, i, &CompareCntC, &MoveCntC);

   

    //----------------------------------outputs
    cout << "SortedData_A : ";
    showAry(a);
    cout << "SortedData_B : ";
    showAry(b);
    cout << "SortedData_C : ";
    showAry(c);
    cout << "Compare_Cnt_A : " << CompareCntA << " DataMove_Cnt_A : " << MoveCntA << "\n";
    cout << "Compare_Cnt_B : " << CompareCntB << " DataMove_Cnt_B : " << MoveCntB << "\n";
    cout << "Compare_Cnt_C : " << CompareCntC << " DataMove_Cnt_C : " << MoveCntC << "\n";
    //----------------------------------free arrays

    for (int i = 0; i < n; i++)
        delete[] temp[i];

    delete[] a;
    delete[] b;
    delete[] temp;
}
