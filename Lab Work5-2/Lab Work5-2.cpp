#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>
using namespace std;

void CountSort(int* a, int* b, int* N, int n, int k, long long int* com, long long int* mov) {
    int i, j;
    for (i = 0; i < k; i++)
    {
        N[i] = 0;
        b[i] = 0;
    }

    for (i = 0; i < n; i++)
    {
        N[a[i]] = N[a[i]] + 1;
    }

    for (i = 2; i < k; i++)
    {
        N[i] = N[i] + N[i - 1];
    }

    for (j = n-1; j >= 0; j--) 
    {
        b[N[a[j]]] = a[j];
        (*mov)++;
        N[a[j]] = N[a[j]] - 1;
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

    int* a, * b, * c, ** temp, n, ntemp; // for dynamic allocation
    long long int CompareCntA = 0, CompareCntB = 0, CompareCntC = 0, MoveCntA = 0, MoveCntB = 0, MoveCntC = 0; // for counting
    int* atem, * btem, * ctem, * stem;

    cin >> n;
    a = new int[n];
    temp = new int* [n];

    initRandAry(temp, n);

    b = new int[n];
    c = new int[n];

    ntemp = n;

    for (int i = 0; i < n; i++)
    {
        a[i] = ntemp--;
    }

    for (int i = 0; i < n; i++)
    {
        b[i] = temp[i][1];
    }

    for (int i = 0; i < n; i++)
    {
        c[i] = (1 + rand() % n);
    }

    stem = new int[n + 1];
    atem = new int[n + 1];
    btem = new int[n + 1];
    ctem = new int[n + 1];
    

    //----------------------------------sorting

    CountSort(a, atem, stem, n, n+1, &CompareCntA, &MoveCntA);
    CountSort(b, btem, stem, n, n+1, &CompareCntB, &MoveCntB);
    CountSort(c, ctem, stem, n, n+1, &CompareCntC, &MoveCntC);

    //----------------------------------outputs
    cout << "SortedData_A : ";
    showAry(atem);
    cout << "SortedData_B : ";
    showAry(btem);
    cout << "SortedData_C : ";
    showAry(ctem);
    cout << "Compare_Cnt_A : " << CompareCntA << " DataMove_Cnt_A : " << MoveCntA << "\n";
    cout << "Compare_Cnt_B : " << CompareCntB << " DataMove_Cnt_B : " << MoveCntB << "\n";
    cout << "Compare_Cnt_C : " << CompareCntC << " DataMove_Cnt_C : " << MoveCntC << "\n";
    //----------------------------------free arrays

    for (int i = 0; i < n; i++)
        delete[] temp[i];

    delete[] a;
    delete[] b;
    delete[] c;
    delete[] atem;
    delete[] btem;
    delete[] ctem;
    delete[] stem;
    delete[] temp;
}
