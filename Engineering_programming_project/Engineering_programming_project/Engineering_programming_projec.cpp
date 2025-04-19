#include <stdio.h>
#include <string.h>
#define N 10000

int max(int, int);
void del_space(char[]);
void arr_to_str(int[], int);
void solve_str(char[], int[], int*);
void sum_arr(int[], int[], int[], int*, int, int);
void sub_arr(int[], int[], int[], int*, int, int);
void mul_arr(int[], int[], int[], int*, int, int);
void div_arr(int[], int[], int[], int*, int, int);

int main()
{
	char a[N], b[N];
	fgets(a, N, stdin);
	fflush(stdin);
	fgets(b, N, stdin);
	del_space(a);
	del_space(b);
	int numa[N] = { 0 }, numb[N] = { 0 }, sum[N] = { 0 }, sub[N] = { 0 }, mul[N] = { 0 }, div[N] = { 0 };
	int amax = 0, bmax = 0, summax = 0, submax = 0, mulmax = 0, divmax = 0;
	solve_str(a, numa, &amax);
	solve_str(b, numb, &bmax);
	sum_arr(sum, numa, numb, &summax, amax, bmax);
	sub_arr(sub, numa, numb, &submax, amax, bmax);
	mul_arr(mul, numa, numb, &mulmax, amax, bmax);
	div_arr(div, numa, numb, &divmax, amax, bmax);
	arr_to_str(sum, summax);
	printf("\n");
	arr_to_str(sub, submax);
	printf("\n");
	arr_to_str(mul, mulmax);
	printf("\n");
	arr_to_str(div, divmax);
	printf("\n");
	arr_to_str(numa, amax);
	printf("\n");
	return 0;
}

void del_space(char str[])
{
	int cnt = 0, check = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == ' ')
		{
			check = 1;
		}
		if (check)
		{
			while (str[i + cnt] == ' ')
			{
				cnt++;
			}
			str[i] = str[i + cnt];
		}
	}
}


void arr_to_str(int num[], int max)
{
	int check = 0, cnt = 0;
	for (int i = max; i >= 0; i--)
	{
		if (num[i])
		{
			cnt++;
			if (num[i] > 0 && check) printf("+");
			if (i == 1)
			{
				if (num[i] == 1) printf("x");
				else if (num[i] == -1) printf("-x");
				else printf("%dx", num[i]);
				check = 1;
				continue;
			}
			if (i == 0)
			{
				printf("%d", num[i]);
				return;
			}
			if (num[i] == 1) printf("x^%d", i);
			else if (num[i] == -1) printf("-x^%d", i);
			else printf("%dx^%d", num[i], i);
			check = 1;
		}
	}
	if (cnt == 0) printf("0");
}

int max_int(int num1, int num2)
{
	if (num1 > num2) return num1;
	return num2;
}

void solve_str(char str[], int num[], int* max)
{
	int sig = 1, tmp = 1, check = 0, sum = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		while (str[i] >= '0' && str[i] <= '9')
		{
			sum = sum * 10 + (int)str[i] - 48;
			i++;
		}
		if (sum)
		{
			if (str[i] == 'x')
			{
				tmp = sum;
				check++;
			}
			else
			{
				if (check % 2 == 1)
				{
					num[sum] = num[sum] + tmp * sig;
					check++;
					(*max) = max_int((*max), sum);
				}
				else
				{
					num[0] = num[0] + sum * sig;
				}
			}
			sum = 0;
		}
		if (str[i] == 'x')
		{
			if (!(str[i - 1] >= '0' && str[i - 1] <= '9'))
			{
				tmp = 1;
				check++;
			}
			if (str[i + 1] != '^')
			{
				num[1] = num[1] + (tmp * sig);
				(*max) = max_int((*max), 1);
				check++;
			}
		}
		if (str[i] == '+' || str[i] == '-') sig = 44 - (int)str[i];
	}
}

void sum_arr(int sum[], int num1[], int num2[], int* summax, int max1, int max2)
{
	for (int i = 0; i <= max_int(max1, max2); i++)
	{
		sum[i] = num1[i] + num2[i];
		if (sum[i]) (*summax) = max_int((*summax), i);
	}
}

void sub_arr(int sub[], int num1[], int num2[], int* submax, int max1, int max2)
{
	for (int i = 0; i <= max_int(max1, max2); i++)
	{
		sub[i] = num1[i] - num2[i];
		if (sub[i]) (*submax) = max_int((*submax), i);
	}
}

void mul_arr(int mul[], int num1[], int num2[], int* mulmax, int max1, int max2)
{
	(*mulmax) = max1 + max2;
	for (int i = 0; i <= max1; i++)
	{
		for (int j = 0; j <= max2; j++)
		{
			mul[i + j] = mul[i + j] + num1[i] * num2[j];
		}
	}
}

void mul_int(int new_num[], int num[], int n, int mul, int* max, int maxn)
{
	(*max) = mul + maxn;
	for (int i = 0; i <= (maxn); i++)
	{
		new_num[i + mul] = num[i] * n;
	}
}

void sub_int(int num1[], int num2[], int* max1)
{
	int max = (*max1);
	(*max1) = 0;
	for (int i = 0; i <= max; i++)
	{
		num1[i] = num1[i] - num2[i];
		if (num1[i]) (*max1) = max_int((*max1), i);
	}
}

void div_arr(int div[], int num1[], int num2[], int* divmax, int max1, int max2)
{
	while (max1 >= max2 && num1[max1] / num2[max2] != 0)
	{
		int k = num1[max1] / num2[max2];
		int mul = max1 - max2;
		div[mul] = div[mul] + k;
		(*divmax) = max_int((*divmax), mul);
		int new_max = 0;
		int new_num[N] = { 0 };
		mul_int(new_num, num2, k, mul, &new_max, max2);
		sub_int(num1, new_num, &max1);
	}
}