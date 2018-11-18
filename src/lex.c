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

const char *first_keyword;
const char *last_keyword;
const char **keywords;

#define KEYWORD(name) name##_keyword = str_intern(#name); buf_push(keywords, name##_keyword)

void init_keywords(void)
{
    static bool inited = false;
    if (inited) return;
    str_intern_grow(25 * sizeof(char*));
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
    first_keyword = enum_keyword;
    last_keyword = import_keyword;

    inited = true;
}
#undef KEYWORD

#define is_keyword_name(str) (first_keyword <= str && str <= last_keyword)

typedef enum TokenKind
{
    EOF,
    LPARAN, LBRACE, LBRACKET,
    RPARAN, RBRACE, RBRACKET,
    COLON, COMMA, DOT,
    AT, POUND,
    DOT_DOT,
    DOT_DOT_DOT,
    EOF,
    EOF,
    EOF,
    EOF,
    EOF,
    EOF,
    EOF,
    EOF,
    EOF,
    EOF,
    EOF,
} TokenKind;

void next_token(void)
{
    /*switch()
    {
    case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
    case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
    case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
    case 'v': case 'w': case 'x': case 'y': case 'z':
    case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
    case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
    case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
    case 'V': case 'W': case 'X': case 'Y': case 'Z': 
    }*/
}
