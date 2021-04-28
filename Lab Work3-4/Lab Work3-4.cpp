#include <iostream>

using namespace std;

void insertion(int a[], int n,long long int* weight)
{
    int i, j; int v;
    for (i = 1; i < n; i++)
    {
        v = a[i];

        j = i;
        if (a[j - 1] > v) {
            *weight += a[j - 1];
        while (a[j - 1] > v)
        {
            a[j] = a[j - 1];
            *weight += a[j];
            
            j--;
        }
        }
        a[j] = v;
        *weight += a[j];
    }
}


int Bubble(int sorted, int* a, int n, long long int* weight)
{
    int temp;
    if (*(a - 1) > *a) {
        temp = *a;
        *weight += *a;
        *a = *(a - 1);
        *weight += *(a - 1);
        *(a - 1) = temp;
        *weight += *a;
        sorted = false;

    }
    return sorted;
}

void bubbleSort(int a[], int n, long long int* weight)
{
    int i, Sorted;
    Sorted = false;
    while (!Sorted) {
        Sorted = true;
        for (i = 1; i < n; i++)
            Sorted = Bubble(Sorted, &a[i], n, weight);
    }
}

void shellSort(int a[], int n, long long int* weight)
{
    int i, j, h, v;
    h = 1;
    do
    {
        h = 3 * h + 1;
    } while (h < n);

    do {
        h = h / 3;
        for (i = h; i <= n; i++)
        {
            v = a[i];
            j = i;
            while (a[j - h] > v)
            {
                a[j] = a[j - h];
                *weight += a[j];
                *weight += a[j - 1];
                j -= h;
                if (j <= h - 1)
                    break;
            }
            a[j] = v;
            *weight += a[j];
        }

    } while (h > 1);
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

    int* a, * b, * c, n, ntemp; // for dynamic allocation

    long long int Insweight = 0,Bubweight = 0, Shlweight = 0; // for counting

    cin >> n;
    a = new int[n];
    b = new int[n];
    c = new int[n];


    ntemp = n;
    for (int i = 0; i < n; i++)
    {
        a[i] = ntemp--;
    }

    ntemp = n;
    for (int i = 0; i < n; i++)
    {
        b[i] = ntemp--;
    }

    ntemp = n;
    for (int i = 0; i < n; i++)
    {
        c[i] = ntemp--;
    }


    //----------------------------------sorting


    insertion(a, n, &Insweight);
    bubbleSort(b, n, &Bubweight);
    shellSort(c, n-1, &Shlweight);
    //bubbleSort(b, n, &CompareCntB, &MoveCntB);

    //----------------------------------outputs
    
    cout << "Insertion Sort : " << Insweight << endl;
    cout << "Bubble Sort : " << Bubweight << endl;
    cout << "Shell Sort : " << Shlweight << endl;

    //----------------------------------free arrays

    delete[] a;
    delete[] b;
    delete[] c;
}
