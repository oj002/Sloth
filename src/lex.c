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

}


void next_token(void)
{

}