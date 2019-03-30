int flipEndianess(int num) {
	char bytes[sizeof(int)];
	for (int i = 0; i < sizeof(int); i++) {
		char *cp = ((char *) &num ) + i;
		bytes[sizeof(int) - i - 1] = *cp;
	}
	int *ip = (int *) bytes;
	return *ip;
}
