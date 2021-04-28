#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>
using namespace std;

typedef struct node* node_pointer;

typedef struct node {
    int value;
    node_pointer next;
};

node_pointer TABLE[10], x, temp, z;
 
void radixSort(int* ary, int num, long long int* com, long long int* mov) {
    int i, j, cnt, radix, radix_mod = 10, cipher = 0;
    i = num;
    while (i > 0)
    {
        i = i / 10;
        cipher++;
    } // init cipher

    for (i = 0; i < cipher; i++)
    {
        for (j = 0; j < num; j++)
        {
            cnt = 0;
            radix = (ary[j] % radix_mod) / (radix_mod / 10);
            (*mov)++;
            temp = new node;
            temp->value = ary[j];
            temp->next = z;

            if (TABLE[radix] == z)
            {
                TABLE[radix] = temp;
                (*mov)++;
            }
            else
            {
                x = TABLE[radix];
                (*mov)++;
                while (x->next != z)
                {
                    x = x->next;
                }
                x->next = temp;
                (*mov)++;
            }
            (*mov)++;
        }

        for (j = 0; j < 10; j++)
        {
            if (TABLE[j] != z)
            {
                x = TABLE[j];
                (*mov)++;
                while (x != z)
                {
                    ary[cnt++] = x->value;
                    (*mov)++;
                    temp = x; // 메모리에서 노드를 삭제하기 위해 임시 저장
                    x = x->next;
                    delete temp; // 배열에 이미 넣은 노드를 메모리에서 삭제
                }
            }
            TABLE[j] = z;
            (*mov)++;
        }
        radix_mod *= 10;
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

    int* a, * b, * c, ** temp, n, ntemp; // for dynamic allocation
    long long int CompareCntA = 0, CompareCntB = 0, CompareCntC = 0, MoveCntA = 0, MoveCntB = 0, MoveCntC = 0; // for counting

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



    //----------------------------------sorting

    radixSort(a, n, &CompareCntA, &MoveCntA);
    radixSort(b, n, &CompareCntB, &MoveCntB);
    radixSort(c, n, &CompareCntC, &MoveCntC);

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
