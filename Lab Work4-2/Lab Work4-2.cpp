#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>

using namespace std;

void merge(int ary1[], int ary2[], int start, int end, long long int* Comcnt, long long int* Movcnt)
{
    int mid = (start + end) / 2;
    int i = start, j = mid + 1, k = start;
    while (i <= mid && j <= end) {
        if (ary1[i] <= ary1[j])
        {
            (*Comcnt)++;
            ary2[k++] = ary1[i++];
            (*Movcnt)++;
        }
        else
        {
            (*Comcnt)++;
            ary2[k++] = ary1[j++];
            (*Movcnt)++;
        }
    }

    while (i <= mid)
    {
        ary2[k++] = ary1[i++];
        (*Movcnt)++;
    }

    while (j <= end)
    {
        ary2[k++] = ary1[j++];
        (*Movcnt)++;
    }

    for (int i = start; i <= end; i++) {
        ary1[i] = ary2[i];
    }
}

void merge_sort(int ary1[], int ary2[], int start, int end, long long int* Comcnt, long long int* Movcnt)
{
    if (start < end) {
        int mid = (start + end) / 2;
        merge_sort(ary1, ary2, start, mid, Comcnt, Movcnt);
        merge_sort(ary1, ary2, mid + 1, end, Comcnt, Movcnt);
        merge(ary1,ary2,start, end, Comcnt, Movcnt);
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
    //----------------------------------init ary1ays
    srand((unsigned)time(NULL));

    int* a, * b, *c, ** temp, n, ntemp; // for dynamic allocation
    long long int CompareCntA = 0, CompareCntB = 0, MoveCntA = 0, MoveCntB = 0; // for counting

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

    c = new int[n];

    //----------------------------------sorting

    merge_sort(a, c, 0, n - 1, &CompareCntA, &MoveCntA);
    merge_sort(b, c, 0, n - 1, &CompareCntB, &MoveCntB);

    //----------------------------------outputs
    cout << "SortedData_A : ";
    showAry(a);
    cout << "SortedData_B : ";
    showAry(b);
    cout << "Compare_Cnt_A : " << CompareCntA << " DataMove_Cnt_A : " << MoveCntA << "\n";
    cout << "Compare_Cnt_B : " << CompareCntB << " DataMove_Cnt_B : " << MoveCntB << "\n";
    //----------------------------------free ary1ays

    for (int i = 0; i < n; i++)
        delete[] temp[i];

    delete[] a;
    delete[] b;
    delete[] temp;
}
