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
void lex_test(void)
{
    keyword_test();
    assert(str_intern("func") == func_keyword);
    puts("lex_test done!");
}
