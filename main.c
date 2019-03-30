#include <stdio.h>
#include "str.h"

long int fsize(FILE *fp)
{
	fseek(fp, 0, SEEK_END);
	long int fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	return fileSize;
}

int main(int argc, char **argv)
{

	// printing out all the command line arguments without the name of the program
	// for (int argi = 1; argi < argc; argi++) // loops through the pointers that point to the first chars of the arguments
	// {
	// 	int chari = 0;
	// 	while (*(*(argv + argi) + chari)) // while there is another character in the word (stops at NULL-terminating byte)
	// 	{
	// 		printf("%c", *(*(argv + argi) + chari));
	// 		chari++;
	// 	}
	// 	printf("\n");
	// }

	// writing some arbitrary bytes to a file called test
	// FILE *fp;
	// fp = fopen("test", "wb");
	// char bytes[16] = {0x34, 0xa2, 0xad, 0x4a, 0x8a, 0x5d, 0x28, 0x0f, 0xaf, 0xf1, 0x10, 0x0d, 0xd5, 0x13, 0x62, 0xa4};
	// for (int i = 0; i < 16; i++) {
	// 	printf("%d. value of array is at address %p and is %x\n", i, bytes + i, *(bytes + i));
	// 	fwrite(bytes + i, sizeof(char), 1, fp);
	// }
	// fclose(fp);

	// getting the file path
	char *filePath = "";
	if (argc >= 3 && streq(*(argv + 1), "-i"))
	{
		filePath = *(argv + 2);
	}

	// opening the file and handling errors
	FILE *fp;
	fp = fopen(filePath, "rb");
	if (!fp)
	{
		printf("no file specified or given file doesn't exist!\n");
		return 0;
	}

	// reading the file
	long int fileSize = fsize(fp);
	char bytes[fileSize];
	for (int i = 0; i < fileSize; i++)
	{
		fread(bytes + i, sizeof(char), 1, fp);
	}
	fclose(fp);

	// printing the file
	for (int i = 0; i < fileSize; i++)
	{
		printf("%d. value of array is at address %p and is %c\n", i + 1, bytes + i, *(bytes + i));
	}

	return 0;
}
