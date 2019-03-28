#include <stdio.h>

long int getFileSize(FILE *fp)
{
	fseek(fp, 0, SEEK_END);
	long int fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	return fileSize;
}

int evaluateStringEquality(int str1len, char *str1, int str2len, char *str2) // returns 0 when != and 1 when ==
{
	if (str1len != str2len)
	{
		return 0;
	}
	for (int i = 0; i < str1len && i < str2len; i++)
	{
		if (*(str1 + i) != *(str2 + i))
		{
			return 0;
		}
	}
	return 1;
}

int evaluateStringEquality(char *str1, char *str2)
{
	int i = 0;
	while (*(str1 + i) && *(str2 + i)) // so far still evaluates to equal when e.g. "hello world\0" =? "hello wo\0"
	{
		if (*(str1 + i) != *(str2 + i))
		{
			return 0;
		}
		i++;
	}
}

int main(int argc, char **argv)
{

	for (int argi = 1; argi < argc; argi++) // loops through the pointers that point to the first chars of the arguments
	{
		int chari = 0;
		while (*(*(argv + argi) + chari)) // while there is another character in the word (stops at NULL-terminating byte)
		{
			printf("%c", *(*(argv + argi) + chari));
			chari++;
		}
		printf("\n");
	}

	// FILE *fp;
	// fp = fopen("test", "wb");
	// char bytes[16] = {0x34, 0xa2, 0xad, 0x4a, 0x8a, 0x5d, 0x28, 0x0f, 0xaf, 0xf1, 0x10, 0x0d, 0xd5, 0x13, 0x62, 0xa4};
	// for (int i = 0; i < 16; i++) {
	// 	printf("%d. value of array is at address %p and is %x\n", i, bytes + i, *(bytes + i));
	// 	fwrite(bytes + i, sizeof(char), 1, fp);
	// }
	// fclose(fp);

	FILE *fp;
	fp = fopen("test", "rb");
	long int fileSize = getFileSize(fp);
	char bytes[fileSize];
	for (int i = 0; i < fileSize; i++)
	{
		fread(bytes + i, sizeof(char), 1, fp);
	}
	fclose(fp);

	for (int i = 0; i < fileSize; i++)
	{
		printf("%d. value of array is at address %p and is %c\n", i + 1, bytes + i, *(bytes + i));
	}

	return 0;
}
