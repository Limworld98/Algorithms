#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

void randomSet(int x, int ary[]);
void buildUnion(int x, int y, int ary1[], int ary2[], int ary3[]);
void buildInterSec(int x, int y, int ary1[], int ary2[], int ary3[]);
void showSet(int x, int ary[]);

int main()
{
    int a, b;

    do
    {
        cin >> a >> b;
    } while ((a > 40) || (b > 40));

    int* set1 = new int[a];
    int* set2 = new int[b];
    int* set3 = new int[a + b];
    int* set4 = new int[a + b];

    randomSet(a, set1);
    randomSet(b, set2);

    cout << "집합A - ";
    showSet(a, set1);
    cout << "집합B - ";
    showSet(b, set2);

    buildUnion(a, b, set1, set2, set3);
    cout << "합집합 - ";
    showSet(a + b, set3);

    cout << "교집합 - ";
    buildInterSec(a, b, set1, set2, set4);
    showSet(a + b, set4);
}

void randomSet(int x, int ary[]) // make random set without overlap
{
    random_device rd;
    mt19937 myrand(rd());
    uniform_int_distribution<int> mydis(1, 40);

    int count;
    for (int i = 0; i < x; i++)
    {
        while (1)
        {
            ary[i] = mydis(myrand);
            count = 0;

            for (int j = 0; j < i; j++)
            {
                if (ary[j] == ary[i])
                {
                    count = 1;
                    break;
                }
            }

            if (!count)
                break;
        }
    }

    sort(ary, ary + x);
}

void buildUnion(int x, int y, int ary1[], int ary2[], int ary3[])
{
    int count;

    for (int i = 0; i < x; i++)
    {
        ary3[i] = ary1[i];
    }

    for (int i = 0; i < y; i++)
    {
        count = 0;

        for (int j = 0; j < x; j++)
        {
            if (ary2[i] == ary1[j])
            {
                count = 1;
            }
        }

        if (!count)
        {
            ary3[x + i] = ary2[i];
        }
    }

    sort(ary3, ary3 + (x + y));

}

void buildInterSec(int x, int y, int ary1[], int ary2[], int ary3[])
{
    int count;
    if (x > y)
    {
        for (int i = 0; i < x; i++)
        {
            count = 0;

            for (int j = 0; j < y; j++)
            {
                if (ary1[i] == ary2[j])
                {
                    count = 1;
                }
            }

            if (count)
            {
                ary3[i] = ary1[i];
            }
        }
    }
    else
    {
        for (int i = 0; i < y; i++)
        {
            count = 0;

            for (int j = 0; j < x; j++)
            {
                if (ary2[i] == ary1[j])
                {
                    count = 1;
                }
            }
            if (count)
            {
                ary3[i] = ary2[i];
            }
        }
    }  

    sort(ary3, ary3 + (x + y));
}

void showSet(int x , int ary[]) 
{
    
    for (int i = 0; i < x; i++)
    {
        if(ary[i] > 0)
        cout << ary[i] << " ";
    }

    cout << endl;
}
