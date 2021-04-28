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
		D[i][0] = D[i - 1][0] + del;	//ù ���� �ʱ�ȭ
	for (int j = 1; j < m + 1; j++)
		D[0][j] = D[0][j - 1] + ins;	// ù ���� �ʱ�ȭ

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
	//stack�� �̵������ ����, temp�� map�� �̵��Ұ� ��θ� ǥ��
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

	while (i < n || j < m) //�����Ÿ� ���̺��� ���� �����Ҷ����� �˻�
	{
		if(j == m) // �� �������� ��� delete �� �˻�
		{
			if (D[i + 1][j] == (D[i][j] + 1) && temp[i+1][j] != false) // check delete
			{
				stack1.push(2);
				i++;
			}			
			else //�� �������� delete (���̻� �̵�) �Ҽ� ���°��
			{
				temp[i][j] = false;
				t = stack1.top();
				stack1.pop();

				switch (t) //�ֱ� �̵���
				{
				case 1: //insert �ϰ��
					j--;
					break;
				case 2: // delete �ϰ��
					i--;
					break;
				case 3: // change �ϰ��
					i--;
					j--;
					break;
				case 4: // change �ϰ��
					i--;
					j--;
					break;
				}
			}
		}

		else if (i == n) // �� �Ʒ����ϰ�� insert�� �˻�
		{
			if (D[i][j + 1] == (D[i][j] + 1) && temp[i][j+1] != false) // check insert
			{
				stack1.push(1);
				j++;
			}	
			else //�� �Ʒ����� insert (���̻� �̵�) �Ҽ� ���°��
			{
				temp[i][j] = false;
				t = stack1.top();
				stack1.pop();

				switch (t) //�ֱ� �̵���
				{
				case 1: //insert �ϰ��
					j--;
					break;
				case 2: // delete �ϰ��
					i--;
					break;
				case 3: // change �ϰ��
					i--;
					j--;
					break;
				case 4: // change �ϰ��
					i--;
					j--;
					break;
				}
			}
		}

		else if(i != n && j != m)// �Ѵ� �ƴҰ�� ����/����/���� �˻�
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
			else // �̵��� �Ұ����Ҷ�
			{
				temp[i][j] = false;
				t = stack1.top(); //stack���� top�� �����ѵ� pop�Ѵ� pop�� ���Ұ�..
				stack1.pop(); 
				switch (t)
				{
				case 1: //insert �ϰ��
					j--;
					break;
				case 2: // delete �ϰ��
					i--;
					break;
				case 3: // change(no cost) �ϰ��
					i--;
					j--;
					break;
				case 4: // change �ϰ��
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
	cout << "�����Ÿ� ���̺�" << endl;

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
	cout << "�ʱ� ���ڿ��� �Է��Ͻÿ� : ";
	cin >> a;
	cout << "��ǥ ���ڿ��� �Է��Ͻÿ� : ";
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

	cout << "�ּҺ�� ��� : ";
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

