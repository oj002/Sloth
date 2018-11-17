#define MAX(a, b) ((a) >= (b) ? (a) : (b))
#define MIN(a, b) ((a) <= (b) ? (a) : (b))

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
	char ptr[];
} BufRaw;

#define BUF_BLOCK_SIZE 1024

#define buf_raw(b) ((BufRaw*)((char*)(b) - offsetof(BufRaw, ptr)))

#define buf_cap(b) ((b) ? buf_raw(b)->cap : 0)
#define buf_len(b) ((b) ? buf_raw(b)->len : 0)
#define buf_end(b) ((b) + buf_len(b))

#define buf_push(b, v) (((b) \
            ? ((buf_len(b) >= buf_cap(b)) \
                ? ((b) = buf__grow(b, BUF_BLOCK_SIZE, sizeof(*b))) : 0) \
            : ((b) = buf__new(BUF_BLOCK_SIZE, sizeof(*b)))), \
        (b)[buf_len(b)] = v, ++(buf_raw(b)->len))
        
#define buf_free(b) ((b) ? (free(buf_raw(b)), b = NULL) : 0)
#define buf_clear(b) ((b) ? buf_raw(b)->len = 0 : 0)
// TODO: buf_printf

void *buf__new(size_t count, size_t elem_size)
{
    BufRaw *new = xmalloc(offsetof(BufRaw, ptr) + count * elem_size);
    new->len = 0;
    new->cap = count;
    return new->ptr;
}
void *buf__grow(const void *buf, size_t count, size_t elem_size)
{
    const size_t cap = buf_cap(buf) + count;
    BufRaw *new = xrealloc(buf_raw(buf), offsetof(BufRaw, ptr) + cap * elem_size);
    new->cap = cap;
    return new->ptr;
}



void common_test(void)
{
    size_t *b = NULL;
    for (size_t i = 0; i < 10001; ++i)
        buf_push(b, i);

    size_t sum = 0;
    for (size_t *it = b; it != buf_end(b); ++it)
        sum += *it;
    
    assert(sum == 50005000);
    assert(buf_cap(b) == BUF_BLOCK_SIZE * 10);

    buf_free(b);
}
