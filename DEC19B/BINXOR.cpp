/*
#   December Challenge 2019 Division 2
#  problem 5-- Binary XOR
# solution by -- RITIK DAGAR
#                 SRM IST NCR CAMPUS
#                 contact -- 9958152151
        */
        
#include <stdio.h>

#define MOD 1000000007

long factorials[100001];

void init()
{
	long temp = 1;
	factorials[0] = 1;
	for (int i = 1; i < 100001; i++)
	{
		temp = (temp * (long long)i) % MOD;
		factorials[i] = temp;
	}
}

long power(long base, long pow)
{
	long x = 1;
	long y = base;
	while (pow)
	{
		if (pow % 2)
		{
			x = (x * y) % MOD;
		}
		y = (y * y) % MOD;
		pow /= 2;
	}
	return x % MOD;
}

long mod_inverse(long base)
{
	return power(base, MOD - 2);
}

long ncr(long n, long r)
{
	return (factorials[n] *
			mod_inverse((factorials[r] * factorials[n - r]) % MOD)) % MOD;
}

int main()
{
	init();

	int tests;
	int n;
	char cur_char;
	int i, j;
	long n1, n2;
	long min, max;
	long long ans;
	scanf("%d", &tests);
	while (tests--)
	{
		scanf("%d", &n);

		// read new line
		scanf("%c", &cur_char);

		n1 = n2 = 0;

		for (i = 0; i < n; i++)
		{
			scanf("%c", &cur_char);
			if (cur_char == '1')
			{
				n1++;
			}
		}

		scanf("%c", &cur_char);

		for (i = 0; i < n; i++)
		{
			scanf("%c", &cur_char);
			if (cur_char == '1')
			{
				n2++;
			}
		}

		if (n2 > n1)
		{
			max = n1; 
			n1 = n2;
			n2 = max;
		}

		min = n1 - n2;

		if ((n1 + n2) > n)
		{
			max = (2 * n) - (n1 + n2);
		}
		else
		{
			max = n1 + n2;
		}

		ans = 0;

		for (i = min; i <= max; i += 2)
		{
			ans = (ans + ncr(n, i)) % MOD;
		}

		printf("%lld\n", ans);
	}

	return 0;
}
