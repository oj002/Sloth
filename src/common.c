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


/**
 * @name Stechy Buffs
 * @brief Use a normal pointer as a dynamic array which allocates its memory 
 * in chuncks, for greater eviciency.
 * It write the length and capacity infront of the ptr.
 * @{ */

typedef struct BufRaw {
	size_t len;
	size_t cap;
	char ptr[];
} BufRaw;

#define buf_raw(b) ((BufRaw*)((char*)(b) - offsetof(BufRaw, ptr)))

#define buf_cap(b) ((b) ? buf_raw(b)->cap : 0)
#define buf_len(b) ((b) ? buf_raw(b)->len : 0)
#define buf_end(b) ((b) + buf_len(b))

#define buf_push(b, v) (((b) \
            ? ((buf_len(b) >= buf_cap(b)) \
                ? ((b) = buf__grow(b, buf_cap(b), sizeof(*b))) : 0) \
            : ((b) = buf__new(1024, sizeof(*b)))), \
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

/**  @} */


/**
 * @name Arena allocator
 * @brief Allocates memory in big blocks and distributes it to 'the user'.
 * All of the memory is freeed at once.
 * @{ */

typedef struct Arena {
    char *ptr;
    char *end;
    char **blocks; // is used as a streachy buf
} Arena;

#define ARENA_BLOCK_SIZE (1024 * 1024)
void arena_grow(Arena *a, size_t min_bytes)
{
    const size_t size = MAX(min_bytes, min_bytes);
    a->ptr = xmalloc(size);
    a->end = a->ptr + size;
    buf_push(a->blocks, a->ptr);
}
void *arena_alloc(Arena *a, size_t nbytes)
{
    if (nbytes > (size_t)(a->end - a->ptr))
        arena_grow(a, nbytes);
    
    void *ret = a->ptr;
    a->ptr += nbytes;
    return ret;
}
void arena_free(Arena *a)
{
    for (char **it = a->blocks; it != buf_end(a->blocks); ++it)
        free(*it);     

    buf_free(a->blocks);
}

/**  @} */

/**
 * @name String Interns
 * @brief A structure which contains a bunch of strings,
 * that are stored in a way so there are no duplicates and
 * you can simply compare the interned strings by there address.
 * @{ */

typedef struct Intern {
    size_t len;
    struct Intern *next;
    char str[];
} Intern;

Arena intern_arena;


/**
 * @Synopsis Allocates a new block of memory in the string intern arena.
 * This can be used to allow greater and less than comparision between
 * interned strings ensuring that they are gruped together sequentionaly.
 */
#define str_intern_grow(nbytes) arena_grow(intern_arena, nbytes)

const char *str_intern_range(const char *start, const char *end)
{
    static Intern *prev = NULL;
    const size_t len = end - start;
    for (Intern *it = prev; it; it = it->next)
        if (it->len == len && strncmp(it->str, start, len) == 0)
            return it->str;
    Intern *new = arena_alloc(&intern_arena, offsetof(Intern, str) + len + 1);
    new->len = len;
    new->next = prev;
    memcpy(new->str, start, len);
    new->str[new->len] = '\0';
    
    prev = new;
    return new->str;
}
const char *str_intern(const char *str) {
    return str_intern_range(str, str + strlen(str));
}

/**  @} */



