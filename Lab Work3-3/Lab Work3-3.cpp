#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>

using namespace std;

int Bubble(int sorted, int* a, int n, int* Comcnt, int* Movcnt)
{
    int temp;
    if (*(a - 1) > *a) {
        temp = *(a - 1);
        *(a - 1) = *a;
        *a = temp;
        sorted = false;
        (*Movcnt)++;
    }
    (*Comcnt)++;
    return sorted;
}

void bubbleSort(int a[], int n, int* Comcnt, int* Movcnt)
{
    int i, Sorted;
    Sorted = false;
    while (!Sorted) {
        Sorted = true;
        for (i = 1; i < n; i++)
            Sorted = Bubble(Sorted, &a[i], n, Comcnt, Movcnt);
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
    for (int i = 0; i < 20; i++)
        cout << t[i] << " ";
    cout << "\n";
}

int main()
{
    //----------------------------------init arrays
    srand((unsigned)time(NULL));

    int* a, * b, ** temp, n, ntemp; // for dynamic allocation
    int CompareCntA = 0, CompareCntB = 0, MoveCntA = 0, MoveCntB = 0; // for counting

    cin >> n;
    a = new int[n];
    temp = new int* [n];
    initRandAry(temp, n);

    b = new int[n];

    ntemp = n;
    for (int i = 0; i < n; i++)
    {
        a[i] = ntemp--;
    }

    for (int i = 0; i < n; i++)
    {
        b[i] = temp[i][1];
    }


    //----------------------------------sorting

    bubbleSort(a, n, &CompareCntA, &MoveCntA);
    bubbleSort(b, n, &CompareCntB, &MoveCntB);

    //----------------------------------outputs
    cout << "SortedData_A : ";
    showAry(a);
    cout << "SortedData_B : ";
    showAry(b);
    cout << "Compare_Cnt_A : " << CompareCntA << " DataMove_Cnt_A : " << MoveCntA << "\n";
    cout << "Compare_Cnt_B : " << CompareCntB << " DataMove_Cnt_B : " << MoveCntB << "\n";
    //----------------------------------free arrays


    for (int i = 0; i < n; i++)
        delete[] temp[i];

    delete[] a;
    delete[] b;
    delete[] temp;
}
