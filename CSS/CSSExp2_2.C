#include <stdio.h>
#include <stdbool.h>

bool isPrime(int n);
bool isGCD1(int a, int b);

int main()
{
	int i, n, fact[100], j=0, RelPrime[100], k=0;
	printf("Enter the number : ");
	scanf("%d",&n);
	if(isPrime(n))
	{
		printf("%d is a Prime Number\n",n);
		printf("Relatively Prime Numbers are : [ ");
		for(i=1;i<n;i++)
			printf("%d ",i);
		printf("]\nphi(%d) = %d",n,n-1);
	}
	else
	{
		printf("%d is not a Prime Number\n",n);
		for(i=1;i<=n;i++)
		{
			if(n%i==0)
			{
				fact[j]=i;
				j++;
			}
		}
		printf("Factors of %d are : [ ",n);
		for(i=0;i<j;i++)
			printf("%d ",fact[i]);
		printf("]\nPrime Factors are : [ ");
		for(i=1;i<j;i++)
		{
			if(isPrime(fact[i]))
				printf("%d ",fact[i]);
		}
		printf("]\nRelatively Primes are : [ ");
		for(i=1;i<n;i++)
		{
			if(isGCD1(n, i))
			{
				RelPrime[k]=i;
				printf("%d ",RelPrime[k]);
				k++;
			}
		}
		printf("]\nphi(%d) = %d",n,k);
	}
	return 0;
}

bool isPrime(int n)
{
	int i;
	for(i=n-1;i>1;i--)
	{
		if(n%i==0)
			return false;
	}
	return true;
}

bool isGCD1(int a, int b)
{
	int i;
	for(i=2;i<=b;i++)
	{
		if(a%i==0 && b%i==0)
			return false;
	}
	return true;
}
