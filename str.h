int strln(char *str) {
	int ofst = 0;
	while (*(str + ofst)) {
		ofst++;
	}
	return ofst;
}

int streq(char *str1, char *str2) {
	int ofst = 0;
	while (*(str1 + ofst) && *(str2 + ofst)) {
		if (*(str1 + ofst) != *(str2 + ofst)) {
			return 0;
		}
		ofst++;
	}
	if (*(str1 + ofst) || *(str2 + ofst)) {
		return 0;
	}
	return 1;
}
