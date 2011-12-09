#include <stdio.h>

// c++ style comment
static int i=1;

/* stream comment */
void solution(int n,char from,char to,char temp)
{
	if(n>0)
	{
		solution(n-1,from,temp,to);
		printf("step %d -> Move the disk %d form %c to %c.\n",i++,n,from,to);
		solution(n-1,temp,to,from);
	}
}

int main(int argc, const char* argv[])
{
	int n;
	printf("Tower of honai problem.\n");
	printf("Enter the no. disks:");
	if (argc == 1)
		scanf("%d",&n);
	else
		n = atoi(argv[1]);
	printf("The solution.\n");
	solution(n,'L','R','C');
	return 0;
}
