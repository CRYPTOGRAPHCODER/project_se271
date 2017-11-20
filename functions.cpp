
bool char_compare(const char*x, const char *y) {
	for (int i = 0; x[i] != 0; i++) {
		if (x[i] != y[i])
			return false;
	}
	return true;
};
