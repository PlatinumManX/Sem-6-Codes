#include <stdio.h>
int main()
{
	char text[100], cypher[100], final[100];
	int i, key, temp;
	printf("Enter Key : ");
	scanf("%d",&key);
	printf("Enter the plain text:-\n");
	scanf(" %[^\n]", text);
	for(i=0;text[i]!='\0';i++)
	{
		if(text[i]>='a' && text[i]<='z')
		{
			temp=text[i]-'a'+key;
			temp=temp%26;
			cypher[i]=temp+'a';
		}
		else if(text[i]>='A' && text[i]<='Z')
		{
			temp=text[i]-'A'+key;
			temp=temp%26;
			cypher[i]=temp+'A';
		}
		else
			cypher[i]=text[i];
	}
	cypher[i]=text[i];
	printf("Cypher Text is: ");
	for(i=0;cypher[i]!='\0';i++)
		printf("%c", cypher[i]);
	for(i=0;cypher[i]!='\0';i++)
	{
		if(cypher[i]>='a' && cypher[i]<='z')
		{
			temp=cypher[i]-'a'-key;
			temp=(temp+26)%26;
			final[i]=temp+'a';
		}
		else if(cypher[i]>='A' && cypher[i]<='Z')
		{
			temp=cypher[i]-'A'-key;
			temp=(temp+26)%26;
			final[i]=temp+'A';
		}
		else
			final[i]=cypher[i];
	}
	final[i]=cypher[i];
	printf("\nDecrpyted Text is: ");
	for(i=0;final[i]!='\0';i++)
		printf("%c", final[i]);
	return 0;
}
