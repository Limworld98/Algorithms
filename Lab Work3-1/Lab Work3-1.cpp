#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>

using namespace std;

void insertion(int a[], int n, long long int *Comcnt, long long int *Movcnt)
{
    int i, j; int v;
    for (i = 1; i < n; i++)
    {
        v = a[i]; 
        j = i;

        while (a[j - 1] > v)
        {
            (*Comcnt)++;
            a[j] = a[j - 1];
            (*Movcnt)++;
            j--;
        }(*Comcnt)++;
        a[j] = v;
    }
}

void initRandAry(int **t,int num)
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

    int *a,*b,**temp, n, ntemp; // for dynamic allocation
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
    
    
    //----------------------------------sorting
    insertion(a, n,&CompareCntA,&MoveCntA);
    insertion(b, n,&CompareCntB,&MoveCntB);


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
