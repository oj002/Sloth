const char *enum_keyword;
const char *struct_keyword;
const char *union_keyword;
const char *const_keyword;	// one time assignment just like c const
const char *val_keyword;	// like constexpr or define but with a type
const char *proc_keyword;	// normal function
const char *func_keyword;	// pure function 

const char *for_keyword;
const char *while_keyword;
const char *do_keyword;
const char *break_keyword;
const char *continue_keyword;
const char *return_keyword;
const char *if_keyword;
const char *else_keyword;
const char *switch_keyword;
const char *case_keyword;
const char *default_keyword;
const char *jmp_keyword;

const char *sizeof_keyword;
const char *alignof_keyword;
const char *typeof_keyword;
const char *offsetof_keyword;

const char *import_keyword;

#define NUM_KEYWORDS 26
const char *first_keyword;
const char *last_keyword;
const char **keywords;

const char *assert_name;
const char *static_assert_name;
const char *assert_name;

#define KEYWORD(name) name##_keyword = str_intern(#name); buf_push(keywords, name##_keyword)

void init_keywords(void)
{
    static bool inited = false;
    if (inited) return;
#if defined(DEBUG)
    char *arena_end = intern_arena.end;
#endif
    KEYWORD(enum);
    KEYWORD(struct);
    KEYWORD(union);
    KEYWORD(const);
    KEYWORD(val);
    KEYWORD(proc);
    KEYWORD(func);
    KEYWORD(for);
    KEYWORD(while);
    KEYWORD(do);
    KEYWORD(break);
    KEYWORD(continue);
    KEYWORD(return);
    KEYWORD(if);
    KEYWORD(else);
    KEYWORD(switch);
    KEYWORD(case);
    KEYWORD(default);
    KEYWORD(jmp);
    KEYWORD(sizeof);
    KEYWORD(alignof);
    KEYWORD(typeof);
    KEYWORD(offsetof);
    KEYWORD(import);

    DASSERT(intern_arena.end == arena_end);

    first_keyword = enum_keyword;
    last_keyword = import_keyword;

    assert_name = str_intern("assert");
    static_assert_name = str_intern("static_assert");

    inited = true;
}
#undef KEYWORD

#define is_keyword_name(str) (first_keyword <= str && str <= last_keyword)

typedef enum TokenKind
{
    TOKEN_EOF,
    TOKEN_COLON,
    TOKEN_LPARAN, TOKEN_LBRACE, TOKEN_LBRACKET,
    TOKEN_RPARAN, TOKEN_RBRACE, TOKEN_RBRACKET,
    TOKEN_COMMA,
    TOKEN_DOT,
    TOKEN_DOT_DOT,
    TOKEN_DOT_DOT_DOT, 
    TOKEN_AT,
    TOKEN_POUND,
    TOKEN_QUESTION,
    TOKEN_SEMICOLON,
    TOKEN_KEYWORD, TOKEN_NAME,
    TOKEN_INT, TOKEN_FLOAT, TOKEN_STR,
    TOKEN_NEG, TOKEN_NOT,
    // Multiplicative precedence
    TOKEN_FIRST_MUL,
    TOKEN_MUL = TOKEN_FIRST_MUL,
    TOKEN_DIV, TOKEN_MOD,
    TOKEN_AND,
    TOKEN_LSHIFT, TOKEN_RSHIFT,
    TOKEN_LAST_MUL = TOKEN_RSHIFT,
    // Additive precidence
    TOKEN_FIRST_ADD,
    TOKEN_ADD = TOKEN_FIRST_ADD,
    TOKEN_SUB,
    TOKEN_XOR, TOKEN_OR,
    TOKEN_LAST_ADD = TOKEN_OR,
    // Comparative precidence
    TOKEN_FIRST_CMP,
    TOKEN_EQ = TOKEN_FIRST_CMP,
    TOKEN_NOTEQ,
    TOKEN_LT, TOKEN_GT, TOKEN_LTEQ, TOKEN_GTEQ,
    TOKEN_LAST_CMP = TOKEN_GTEQ,
    TOKEN_AND_AND, TOKEN_OR_OR,
    // Assignment operators
    TOKEN_FIRST_ASSIGN,
    TOKEN_ASSIGN = TOKEN_FIRST_ASSIGN,
    TOKEN_ADD_ASSIGN,
    TOKEN_SUB_ASSIGN,
    TOKEN_OR_ASSIGN,
    TOKEN_AND_ASSIGN,
    TOKEN_XOR_ASSIGN,
    TOKEN_LSHIFT_ASSIGN,
    TOKEN_RSHIFT_ASSIGN,
    TOKEN_MUL_ASSIGN,
    TOKEN_DIV_ASSIGN,
    TOKEN_MOD_ASSIGN,
    TOKEN_LAST_ASSIGN = TOKEN_MOD_ASSIGN,
    TOKEN_INC, TOKEN_DEC,
    TOKEN_COLON_ASSIGN,
    NUM_TOKEN_KINDS,
} TokenKind;

typedef enum TokenMod {
    MOD_NONE,
    MOD_HEX,
    MOD_BIN,
    MOD_OCT,
    MOD_CHAR,
    MOD_MULTILINE,
} TokenMod;

const char* token_kind_name(TokenKind kind)
{
    switch (kind)
    {
    case TOKEN_EOF: return "EOF";
    case TOKEN_COLON: return ":";
    case TOKEN_LPARAN: return "(";
    case TOKEN_LBRACE: return "{";
    case TOKEN_LBRACKET: return "[";
    case TOKEN_RPARAN: return ")";
    case TOKEN_RBRACE: return "}";
    case TOKEN_RBRACKET: return "]";
    case TOKEN_COMMA: return ",";
    case TOKEN_DOT: return ".";
    case TOKEN_DOT_DOT: return "..";
    case TOKEN_DOT_DOT_DOT: return "...";
    case TOKEN_AT: return "@";
    case TOKEN_POUND: return "#";
    case TOKEN_QUESTION: return "?";
    case TOKEN_SEMICOLON: return ";";
    case TOKEN_KEYWORD: return "keyword";
    case TOKEN_NAME: return "name";
    case TOKEN_INT: return "int";
    case TOKEN_FLOAT: return "float";
    case TOKEN_STR: return "string";
    case TOKEN_NEG: return "~";
    case TOKEN_NOT: return "!";
    case TOKEN_MUL: return "*";
    case TOKEN_DIV: return "/";
    case TOKEN_MOD: return "%";
    case TOKEN_AND: return "&";
    case TOKEN_LSHIFT: return "<<";
    case TOKEN_RSHIFT: return ">>";
    case TOKEN_ADD: return "+";
    case TOKEN_SUB: return "-";
    case TOKEN_XOR: return "^";
    case TOKEN_OR: return "|";
    case TOKEN_EQ: return "==";
    case TOKEN_NOTEQ: return "!=";
    case TOKEN_LT: return "<";
    case TOKEN_GT: return ">";
    case TOKEN_LTEQ: return "<=";
    case TOKEN_GTEQ: return ">=";
    case TOKEN_AND_AND: return "&&";
    case TOKEN_OR_OR: return "||";
    case TOKEN_ASSIGN: return "=";
    case TOKEN_ADD_ASSIGN: return "*=";
    case TOKEN_SUB_ASSIGN: return "-=";
    case TOKEN_OR_ASSIGN: return "|=";
    case TOKEN_AND_ASSIGN: return "&=";
    case TOKEN_XOR_ASSIGN: return "^=";
    case TOKEN_LSHIFT_ASSIGN: return "<<=";
    case TOKEN_RSHIFT_ASSIGN: return ">>=";
    case TOKEN_MUL_ASSIGN: return "*=";
    case TOKEN_DIV_ASSIGN: return "/=";
    case TOKEN_MOD_ASSIGN: return "%=";
    case TOKEN_INC: return "++";
    case TOKEN_DEC: return "--";
    case TOKEN_COLON_ASSIGN: return ":=";
    default:
        return "<unknown>";
    }
}
TokenKind assign_token_to_binary_token[NUM_TOKEN_KINDS] = {
    [TOKEN_ADD_ASSIGN] = TOKEN_ADD,
    [TOKEN_SUB_ASSIGN] = TOKEN_SUB,
    [TOKEN_OR_ASSIGN] = TOKEN_OR,
    [TOKEN_AND_ASSIGN] = TOKEN_ADD,
    [TOKEN_XOR_ASSIGN] = TOKEN_XOR,
    [TOKEN_LSHIFT_ASSIGN] = TOKEN_LSHIFT,
    [TOKEN_RSHIFT_ASSIGN] = TOKEN_RSHIFT,
    [TOKEN_MUL_ASSIGN] = TOKEN_MUL,
    [TOKEN_DIV_ASSIGN] = TOKEN_DIV,
    [TOKEN_MOD_ASSIGN] = TOKEN_MOD,
};

typedef struct CodePos {
    const char *name;
    size_t line;
} CodePos;

CodePos pos_builtin = {.name = "<buildin>"};

typedef struct Token
{
    TokenKind kind;
    TokenMod mod;
    CodePos pos;
    const char *start;
    const char *end;
    union {
        uint64_t int_val;
        double float_val;
        const char *str_val;
        const char *name;
    };
} Token;

Token token;
const char *stream;
const char *line_beg;

void warning(CodePos pos, const char *fmt, ...)
{
    if (pos.name == NULL) // TODO: check if needed
        pos = pos_builtin;
    va_list args;
    va_start(args, fmt);
    printf("%s(%zu:%zu): warning: ", pos.name, pos.line);
    vprintf(fmt, args);
    putchar('\n');
    va_end(args);
}
void error(CodePos pos, const char *fmt, ...)
{
    if (pos.name == NULL)
        pos = pos_builtin;
    va_list args;
    va_start(args, fmt);
    printf("%s(%zu:%zu): error: ", pos.name, pos.line);
    vprintf(fmt, args);
    putchar('\n');
    va_end(args);
}

#define fatal_error(...) (error(__VA_ARGS__), exit(EXIT_FAILUR))
#define error_here(...) (error(token.pos, __VA_ARGS__))
#define warning_here(...) (warnin(token.pos, __VA_ARGS__))
#define fatal_error_here(...) (error_here(__VA_ARGS__), exit(EXIT_FAILUR))

void scan_num(void)
{
   
}

char escape_to_char[256] = {
    ['0'] = '\0',
    ['\''] = '\'',
    ['"'] = '"',
    ['n'] = '\n',
    ['r'] = '\r',
    ['t'] = '\t',
    ['v'] = '\v',
    ['b'] = '\b',
    ['a'] = '\a',
};
void scan_hex_escape(void)
{
   
   token.int_val = '0'; 
}
void scan_char(void)
{
    DASSERT(*stream == '\'');
    token.kind = TOKEN_INT;
    token.mod = MOD_CHAR;
    ++stream;
    switch (*stream)
    {
    case '\'':
        error_here("Char literal cannot be empty"); 
        return;
    case '\\':
        ++stream;
        if (*stream == 'x')
            scan_hex_escape();
        else {
            token.int_val = escape_to_char[*stream];
            if (token.int_val == 0 && *stream != '0')
                error_here("Invalid char literal escape '\\%c'", *stream);
            ++stream;
        }
        break;
    default:
        token.int_val = *stream;
        ++stream;
        break;
    }
    if (*stream != '\'')
        error_here("Expected closing char quotes, got '%c'", *stream);
    else ++stream;
}
void scan_str(void)
{
    
}

void next_token(void)
{
repeat:
    token.start = stream;
    switch(*stream)
    {
    case '\n':
        ++token.pos.line;
    case ' ': case '\r': case '\t': case '\v':
        ++stream;
        while (isspace(*stream))
            if (*stream++ == '\n')
                ++token.pos.line, line_beg = stream;
        goto repeat;
    case '\'':
        scan_char();
        break;
    case '"':
        scan_str();
        break;
    case '.':
        break;
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
        scan_num();
        break;
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
    case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
    case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
    case 'v': case 'w': case 'x': case 'y': case 'z':
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
    case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
    case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
    case 'V': case 'W': case 'X': case 'Y': case 'Z': case '_':
    {
        while (isalnum(*stream) || *stream == '_')
            ++stream;
        token.name = str_intern_range(token.start, stream);
        token.kind = is_keyword_name(token.name) ? TOKEN_KEYWORD : TOKEN_NAME;
        break;
    }
    case '/':
    {
        ++stream;
        switch(*stream)
        {
        case '/':
            ++stream;
            while (*stream && *stream != '\n') ++stream;
            goto repeat;
        case '*':
        {
            ++stream;
            size_t level = 1;
            while (*stream && level != 0)
            {
                if (stream[0] == '*' && stream[1] == '/')
                    --level, stream += 2;
                else if (stream[0] == '/' && stream[1] == '*')
                    ++level, stream += 2;
                else if (*stream == '\n')
                    ++token.pos.line, ++stream;
            }
            goto repeat;
        }
        case '=':
            token.kind = TOKEN_DIV_ASSIGN, ++stream;
            break;
        default:
            token.kind = TOKEN_DIV;
        }
        break;
    }
    default:
        error_here("Invalid '%c' token, skipping", *stream);
        ++stream;
        goto repeat; 
    }
    token.end = stream;
}
