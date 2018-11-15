
void fatal(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, "FATAL: ");
	vfprintf(stderr, fmt, args);
	fputc('\n', stderr);
	va_end(args);
	exit(EXIT_FAILURE);
}

void *xcalloc(size_t num_elems, size_t elem_size)
{
	void *ptr = calloc(num_elems, elem_size);
	if (!ptr) {
		perror("xcalloc failed");
		exit(EXIT_FAILURE);
	}
	return ptr;
}
void *xrealloc(void *ptr, size_t num_bytes)
{
	ptr = realloc(ptr, num_bytes);
	if (!ptr) {
		perror("xrealloc failed");
		exit(EXIT_FAILURE);
	}
	return ptr;
}
void *xmalloc(size_t num_bytes)
{
	void *ptr = malloc(num_bytes);
	if (!ptr) {
		perror("xmalloc failed");
		exit(EXIT_FAILURE);
	}
	return ptr;
}
void *memdup(void *src, size_t size)
{
	void *dest = xmalloc(size);
	memcpy(dest, src, size);
	return dest;
}