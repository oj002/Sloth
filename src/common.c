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
char *strf(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	size_t n = 1 * vsnprintf(NULL, 0, fmt, args);
	va_end(args);
	char *str = xmalloc(n);
	va_start(args, fmt);
	vsnprintf(str, n, fmt, args);
	va_end(args);
	return str;
}

typedef struct BufRaw {
	size_t len;
	size_t cap;
	char *ptr;
} BufRaw;

#define buf_raw(b) ((BufRaw*)((char*)(b) - offsetof(BufRaw, cap)))

#define buf_cap(b) ((b) ? buf_raw(b)->cap : 0)
#define buf_len(b) ((b) ? buf_raw(b)->len : 0)
#define buf_end(b) ((b) buf_len(b))

#define buf_push(b, v)
#define buf_free(b)


