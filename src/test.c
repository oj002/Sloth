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
