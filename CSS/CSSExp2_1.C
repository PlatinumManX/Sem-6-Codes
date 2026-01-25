#include <stdio.h>
int main()
{
	int n1, n2, r, r1, r2, s, s1, s2, t, t1, t2, q, temp, sum1, sum2;
	printf("Enter 2 Numbers:-\n");
	scanf("%d %d",&r1, &r2);
	n1=r1;
	n2=r2;
	if(r1<=r2)
	{
		temp=r1;
		r1=r2;
		r2=temp;
	}
	s1=1;
	s2=0;
	t1=0;
	t2=1;
	printf("q\tr1\tr2\tr\ts1\ts2\ts\tt1\tt2\tt\n");
	while(r2!=0)
	{
		q=r1/r2;
		r=r1%r2;
		s=s1-q*s2;
		t=t1-q*t2;
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",q,r1,r2,r,s1,s2,s,t1,t2,t);
		r1=r2;
		r2=r;
		s1=s2;
		s2=s;
		t1=t2;
		t2=t;
	}
	sum1=s1*n1;
	sum2=t1*n2;
	printf("\nGCD : %d\ns : %d\nt : %d\n",r1,s1,t1);
	printf("s*a + t*b = gcd(a, b)\n%d*%d + %d*%d = %d",s1,n1,t1,n2,r1);
	printf("\n%d + %d = %d",sum1,sum2,r1);
	return 0;
}
