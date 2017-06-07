#include <stdio.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	FILE *tmpfp;
	tmpfp = tmpfile();
	if (tmpfp)
	{
		printf("Tmeporaryfilecreated\n");
	}
	else
	{
		printf("Unabletocreatetemporaryfile\n");
		exit(1);
	}
	return 0;
}