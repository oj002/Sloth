void buf_test(void)
{
    int *b = NULL;
    assert(buf_len(b) == 0);
    const int n = 12345;
    
    for (int i = 0; i < n; ++i)
        buf_push(b, i);

    assert(buf_len(b) == n);

    for (int i = 0; i < n; ++i)
        assert(b[i] == i);

    buf_free(b);
}
void intern_test(void)
{
    char a[] = "test";
    assert(strcmp(a, str_intern(a)) == 0);
    assert(str_intern(a) == str_intern(a));
    assert(str_intern(str_intern(a)) == str_intern(a));
    char b[] = "test";
    assert(a != b);
    assert(str_intern(a) == str_intern(b));
    char c[] = "test!";
    assert(str_intern(a) != str_intern(c));
    char d[] = "tes";
    assert(str_intern(a) != str_intern(d));
}
void common_test(void)
{
    buf_test();
    intern_test();
    puts("common_test done!");
} 

void keyword_test(void)
{
    init_keywords();
    assert(is_keyword_name(first_keyword));
    assert(is_keyword_name(last_keyword));
    for (const char **it = keywords; it != buf_end(keywords); ++it)
        assert(is_keyword_name(*it));
    assert(!is_keyword_name("i am not a keyword"));
}
#define assert_token(x) assert(match_token(TOKEN_##x))
#define assert_token_name(x) \
    assert(token.name == str_intern(x) && match_token(TOKEN_NAME))
#define assert_token_int(x) \
    assert(token.int_val == x && match_token(TOKEN_INT))
#define assert_token_float(x) \
    assert(token.float_val == x && match_token(TOKEN_FLOAT))
#define assert_token_str(x) \
    assert(strcmp(token.str_val, (x)) == 0 && match_token(TOKEN_STR))
#define assert_token_eof() assert(is_token_eof())

void lex_test(void)
{
    keyword_test();
    assert(str_intern("func") == func_keyword);
    
    init_stream("Integer literal test", "0 2147483647 0x7fffffff 042 0b1111");
    assert_token_int(0);
    assert_token_int(2147483647);
    assert_token_int(0x7fffffff);
    assert_token_int(042);
    assert_token_int(0b1111);
    assert_token_eof();

    init_stream("Floating literal test", "3.14 .123 42. 3e10 4.e-2");
    assert_token_float(3.14);
    assert_token_float(.123);
    assert_token_float(42.);
    assert_token_float(3e10);
    assert_token_float(4.e-2);
    assert_token_eof();
    
    init_stream("Char literal test", "'a' '\\n'");
    assert_token_int('a');
    assert_token_int('\n');
    assert_token_eof();
    
    init_stream("String literal test", "\"foo\" \"test \\nlol\"");
    assert_token_str("foo");
    assert_token_str("test \nlol");
    assert_token_eof();

    init_stream("Operator test", ": := + += ++ < <= << <<=");
    assert_token(COLON);
    assert_token(COLON_ASSIGN);
    assert_token(ADD);
    assert_token(ADD_ASSIGN);
    assert_token(INC);
    assert_token(LT);
    assert_token(LTEQ);
    assert_token(LSHIFT);
    assert_token(LSHIFT_ASSIGN);
    assert_token_eof();

    init_stream("Misc test", "WE*(are)_ALMOST42,0xd011e+112;heRE");
    assert_token_name("WE");
    assert_token(MUL);
    assert_token(LPAREN);
    assert_token_name("are");
    assert_token(RPAREN);
    assert_token_name("_ALMOST42");
    assert_token(COMMA);
    assert_token_int(0xd011e);
    assert_token(ADD);
    assert_token_int(112);
    assert_token(SEMICOLON);
    assert_token_name("heRE");

    puts("lex_test done!");
}
