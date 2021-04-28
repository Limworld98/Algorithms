#include <iostream>
#include <algorithm>
#include <string>
#include <stack>

#define INSERT 1
#define DELETE 1
#define CHANGE 2

using namespace std;

stack<int> stack1; //1:insert 2:delete 3:change(no cost) 4: change
stack<int> stack2; //1:insert 2:delete 3:change(no cost) 4: change

void EditDist(int** D, int n, string X, int m, string Y, int ins, int del, int chg)
{

	D[0][0] = 0;

	int c;

	for (int i = 1; i < n + 1; i++)
		D[i][0] = D[i - 1][0] + del;	//첫 열의 초기화
	for (int j = 1; j < m + 1; j++)
		D[0][j] = D[0][j - 1] + ins;	// 첫 행의 초기화

	for (int i = 1; i < n + 1; i++)
	{
		for (int j = 1; j < m + 1; j++)
		{
			c = (X[i - 1] == Y[j - 1]) ? 0 : chg;
			D[i][j] = min({ D[i - 1][j] + del, D[i][j - 1] + ins, D[i - 1][j - 1] + c });
		}
	}
}

void Distsearch(int **D,int n, int m)
{
	//stack에 이동방식을 저장, temp로 map에 이동불가 경로를 표기
	int i = 0, j = 0,t;
	bool** temp;
	temp = new bool* [n+1];

	for (int k = 0; k < n+1; k++)
	{
		temp[k] = new bool[m+1];
	}

	for (int k = 0; k < n+1; k++)
	{
		for (int l = 0; l < m+1; l++)
		{
			temp[k][l] = true;
		}
	}

	while (i < n || j < m) //편집거리 테이블의 끝에 도달할때까지 검사
	{
		if(j == m) // 맨 우측열일 경우 delete 만 검사
		{
			if (D[i + 1][j] == (D[i][j] + 1) && temp[i+1][j] != false) // check delete
			{
				stack1.push(2);
				i++;
			}			
			else //맨 우측에서 delete (더이상 이동) 할수 없는경우
			{
				temp[i][j] = false;
				t = stack1.top();
				stack1.pop();

				switch (t) //최근 이동이
				{
				case 1: //insert 일경우
					j--;
					break;
				case 2: // delete 일경우
					i--;
					break;
				case 3: // change 일경우
					i--;
					j--;
					break;
				case 4: // change 일경우
					i--;
					j--;
					break;
				}
			}
		}

		else if (i == n) // 맨 아래행일경우 insert만 검사
		{
			if (D[i][j + 1] == (D[i][j] + 1) && temp[i][j+1] != false) // check insert
			{
				stack1.push(1);
				j++;
			}	
			else //맨 아래에서 insert (더이상 이동) 할수 없는경우
			{
				temp[i][j] = false;
				t = stack1.top();
				stack1.pop();

				switch (t) //최근 이동이
				{
				case 1: //insert 일경우
					j--;
					break;
				case 2: // delete 일경우
					i--;
					break;
				case 3: // change 일경우
					i--;
					j--;
					break;
				case 4: // change 일경우
					i--;
					j--;
					break;
				}
			}
		}

		else if(i != n && j != m)// 둘다 아닐경우 삽입/삭제/변경 검사
		{
			if (D[i + 1][j + 1] == D[i][j] && temp[i + 1][j + 1] != false) // check change(no cost)
			{
				stack1.push(3);
				i++;
				j++;
			}
			else if (D[i + 1][j + 1] == (D[i][j]+2) && temp[i + 1][j + 1] != false) // check change
			{
				stack1.push(4);
				i++;
				j++;
			}
			else if (D[i][j + 1] == (D[i][j] + 1) && temp[i][j+1] != false) // check insert
			{
				stack1.push(1);
				j++;
			}
			else if (D[i + 1][j] == (D[i][j] + 1) && temp[i+1][j] != false) // check delete
			{
				stack1.push(2);
				i++;
			}
			else // 이동이 불가능할때
			{
				temp[i][j] = false;
				t = stack1.top(); //stack에서 top을 리턴한뒤 pop한다 pop한 원소가..
				stack1.pop(); 
				switch (t)
				{
				case 1: //insert 일경우
					j--;
					break;
				case 2: // delete 일경우
					i--;
					break;
				case 3: // change(no cost) 일경우
					i--;
					j--;
					break;
				case 4: // change 일경우
					i--;
					j--;
					break;
				}
			}
		}
	}

}

void showDist(int** D, int n, int m)
{
	cout << "편집거리 테이블" << endl;

	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < m + 1; j++)
		{
			cout << D[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	string a, b;
	int alen, blen;
	cout << "초기 문자열을 입력하시오 : ";
	cin >> a;
	cout << "목표 문자열을 입력하시오 : ";
	cin >> b;
	alen = a.length();
	blen = b.length();

	int** mat;
	mat = new int* [alen + 1];

	for (int i = 0; i < (alen + 1); i++)
	{
		mat[i] = new int[blen + 1];
	}

	EditDist(mat, alen, a, blen, b, INSERT, DELETE, CHANGE);
	showDist(mat, alen, blen);
	Distsearch(mat, alen, blen);

	while (!stack1.empty())
	{
		stack2.push(stack1.top());
		stack1.pop();
	}

	cout << "최소비용 경로 : ";
	while (!stack2.empty())
	{
		switch (stack2.top())
		{
		case 1:
			cout << "I ";
			break;
		case 2:
			cout << "D ";
			break;
		case 3:
			cout << "O ";
			break;
		case 4:
			cout << "C ";
			break;
		}
		stack2.pop();
	}
		return 0;
}

