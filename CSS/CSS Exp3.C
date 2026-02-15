#include <stdio.h>
int main()
{
	char ch, a, b, key[25], matrix[5][5], plaintext[100], processed[100], digraph[100], ciphertext[100], temp[25];
	int i, j, k, d=0, found, count=0, len=0, r1, r2, c1, c2, idx=0;
	printf("Enter the Key : ");
	scanf(" %[^\n]", key);
	
	//CreatingTheKeyMatrix
	
	for(i=0;key[i]!='\0';i++)
	{
		ch=key[i];
		if(ch >= 'a' && ch<= 'z')
			ch = ch-32;
		if(ch == 'J')
			ch = 'I';
		if(ch < 'A' || ch > 'Z')
			continue;
		found = 0;
		
		for(j=0;j<count;j++)
		{
			if(temp[j] == ch)
			{
				found = 1;
				break;
			}
		}
		if(found == 0)
		{
			temp[count] = ch;
			count++;
		}
	}
	
	for(i=0;i<26;i++)
	{
		ch = 'A' + i;
		if(ch == 'J')
			continue;
		found = 0;
		for(j=0;j<count;j++)
		{
			if(temp[j] == ch)
			{
				found = 1;
				break;
			}
		}
		if(found == 0)
		{
			temp[count] = ch;
			count++;
		}
	}
	
	k=0;
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			matrix[i][j] = temp[k];
			k++;
		}
	}
	printf("Key Matrix:-\n");
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
			printf("%c ",matrix[i][j]);
		printf("\n");
	}
	
	printf("Enter the Plaintext : ");
	scanf(" %[^\n]", plaintext);
	for(i=0;plaintext[i]!='\0';i++)
	{
		ch = plaintext[i];
		if(ch >= 'a' && ch <= 'z')
			ch = ch-32;
		if(ch == 'J')
			ch = 'I';
		if(ch < 'A' || ch > 'Z')
			continue;
		processed[len] = ch;
		len++;
	}
	
	for(i=0;i<len;i++)
	{
		digraph[d] = processed[i];
		d++;
		if(processed[i] == processed[i+1])
			digraph[d++] = 'X';
		else if(processed[i+1] != '\0')
		{
			i++;
			digraph[d] = processed[i];
			d++;
		}
	}
	if(d%2!=0)
	{
		digraph[d] = 'X';
		d++;
	}
	digraph[d] = '\0';
	
	printf("\nDigraphs:-\n");
	for(i=0;i<d;i=i+2)
		printf("%c%c ", digraph[i], digraph[i+1]);
	
	printf("\nEncryptions:-\n");
	for(i=0;digraph[i]!='\0';i=i+2)
	{
		a=digraph[i];
		b=digraph[i+1];
		for(j=0;j<5;j++)
		{
			for(k=0;k<5;k++)
			{
				if(matrix[j][k] == a)
				{
					r1=j;
					c1=k;
				}
				if(matrix[j][k] == b)
				{
					r2=j;
					c2=k;
				}
			}
		}
		if(r1==r2)
		{
			printf("Same Row    : %c%c -> ",a,b);
			ciphertext[idx]=matrix[r1][(c1+1)%5];
			ciphertext[idx+1]=matrix[r2][(c2+1)%5];
		}
		else if(c1==c2)
		{
			printf("Same Column : %c%c -> ",a,b);
			ciphertext[idx]=matrix[(r1+1)%5][c1];
			ciphertext[idx+1]=matrix[(r2+1)%5][c2];
		}
		else
		{
			printf("Rectangle   : %c%c -> ",a,b);
			ciphertext[idx]=matrix[r1][c2];
			ciphertext[idx+1]=matrix[r2][c1];
		}
		printf("%c%c\n",ciphertext[idx],ciphertext[idx+1]);
		idx=idx+2;
	}
	ciphertext[idx]='\0';
	printf("\nCiphertext : %s\n", ciphertext);
	return 0;
}

