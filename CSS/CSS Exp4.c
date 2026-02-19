#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool isPrime(int);
int Euclidean(int, int);
bool isGCD(int a, int b);
long long modexp(long long base, long long exp, long long mod);
int main()
{
    int p, q, n, e, phi, d, m;
    long long c, m1;
    printf("Enter Two Prime : ");
    scanf("%d %d", &p, &q);
    if(!isPrime(p) || !isPrime(q))
    {
        printf("Invalid Numbers Entered");
        return 0;
    }
    n = p*q;
    printf("Value of n : %d", n);
    phi = (p-1)*(q-1);
    printf("\nPhi(n) : %d", phi);
    printf("\nEnter Value of e co-prime of %d : ", phi);
    scanf("%d", &e);
    if(!isGCD(e, phi))
    {
		printf("Invalid Value of e");
		return 0;
	}
    d = Euclidean(phi, e);
    printf("Value of d : %d", d);
    printf("\nPublic Key : {%d, %d}", e, n);
    printf("\nPrivate Key : {%d, %d}", d, n);
    printf("\nEnter the Number to be Encrypted : ");
    scanf("%d", &m);
    printf("\nFor Encryption:-\nC = M^e mod n\nC = %d^%d mod %d", m, e, n);
    c = modexp(m, e, n);
    printf("\nC = %lld", c);
    printf("\nFor Decryption:-\nM = C^d mod n\nM = %lld^%d mod %d", c, d, n);
    m1 = modexp(c, d, n);
    printf("\nM = %lld", m1);
    return 0;
}

bool isPrime(int a)
{
    int i;
    for(i=a-1;i>1;i--)
    {
        if(a%i == 0)
            return false;
    }
    return true;
}

int Euclidean(int phi, int e)
{
	int r, r1, r2, t, t1, t2, q;
	r1=phi;
	r2=e;
	t1=0;
	t2=1;
	printf("Calculation of d:-\nq\tr1\tr2\tr\tt1\tt2\tt\n");
	while(r2!=0)
	{
		q=r1/r2;
		r=r1%r2;
		t=t1-q*t2;
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",q,r1,r2,r,t1,t2,t);
		r1=r2;
		r2=r;
		t1=t2;
		t2=t;
	}
	return t1;
}

bool isGCD(int a, int b)
{
	int i;
	for(i=2;i<=b;i++)
	{
		if(a%i==0 && b%i==0)
			return false;
	}
	return true;
}

long long modexp(long long base, long long exp, long long mod)
{
	long long result = 1;
	while(exp > 0)
	{
		if(exp % 2 == 1)
			result = (result * base) % mod;
		base = (base * base) % mod;
		exp = exp / 2;
	}
	return result;
}
