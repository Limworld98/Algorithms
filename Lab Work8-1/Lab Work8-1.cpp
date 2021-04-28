#include <iostream>
#include <algorithm>
#include <string>

#define INSERT 1
#define DELETE 1
#define CHANGE 2

using namespace std;

void EditDist(int **D,int n, string X, int m, string Y, int ins, int del, int chg) 
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

void showDist(int** D, int n, int m)
{
	cout <<"편집거리 테이블" << endl;

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
	cout << "최소편집비용 : " << mat[alen][blen]<<endl;
	return 0;
}

