#include "c4/string.hpp"
#include <cwchar>

C4_BEGIN_NAMESPACE(c4)

void s2ws(char const* mbstr, size_t len, wchar_t *output)
{
    std::mbstate_t state = std::mbstate_t();
    std::mbsrtowcs(&output[0], &mbstr, len, &state);
}
void ws2s(wchar_t const* mbstr, size_t len, char *output)
{
    std::mbstate_t state = std::mbstate_t();
    std::wcsrtombs(&output[0], &mbstr, len, &state);
}
/*
string sstest()
{
    csubstring ss1("ssa"), ss2("ssb");
    string r;
    r = ss1 + ss2;
    C4_ASSERT(r == "ssassb");
    return r;
}
static string wtf = sstest();

string sstest2()
{
    char buf1[] = "ssa";
    char buf2[] = "ssb";
    substring ss1(buf1), ss2(buf2);
    string r;
    r = ss1 + ss2;
    C4_ASSERT(r == "ssassb");
    return r;
}
static string wtf2 = sstest2();

string sstest3()
{
    csubstringrs ss1("ssa"), ss2("ssb");
    string r;
    r = ss1 + ss2;
    return r;
}
static string wtf3 = sstest3();

string sstest4()
{
    char buf1[] = "ssa";
    char buf2[] = "ssb";
    substringrs ss1(buf1), ss2(buf2);
    string r;
    r = ss1 + ss2;
    C4_ASSERT(r == "ssassb");
    return r;
}
static string wtf4 = sstest4();

substring sstest5()
{
    csubstring ss1("ssa"), ss2("ssb");
    string r;
    r = ss1 + ss2;
    C4_ASSERT(r == "ssassb");
    return r;
}
static string wtf5 = sstest5();
*/
substring sstest6()
{
    char buf1[] = "ssa";
    char buf2[] = "ssb";
    substring ss1(buf1), ss2(buf2);
    static char resultbuf[9];
    substring r(resultbuf);
    r = ss1 + ss2;
    //C4_ASSERT(r == "ssassb");
    return r;
}
static string wtf6 = sstest6();
/*
substringrs sstest7()
{
    csubstringrs ss1("ssa"), ss2("ssb");
    static char resultbuf[9];
    substringrs r;
    r = ss1 + ss2;
    C4_ASSERT(r == "ssassb");
    return r;
}
static string wtf7 = sstest7();

substringrs sstest8()
{
    char buf1[] = "ssa";
    char buf2[] = "ssb";
    substringrs ss1(buf1), ss2(buf2);
    static char resultbuf[9];
    substringrs r(resultbuf);
    r = ss1 + ss2;
    C4_ASSERT(r == "ssassb");
    return r;
}
static string wtf8 = sstest8();
*/
C4_END_NAMESPACE(c4)

//-----------------------------------------------------------------------------

#ifdef C4_VSNPRINTF
/// Visual Studio does not have vsnprintf
/// @see http://stackoverflow.com/questions/2915672/snprintf-and-visual-studio-2010
int vsnprintf(char* str, size_t size, const char* format, va_list ap)
{
    int count = -1;

    if (size != 0)
    {
        count = _vsnprintf_s(str, size, _TRUNCATE, format, ap);
    }

    if (count == -1)
    {
        count = _vscprintf(format, ap);
    }

    return count;
}
#endif // C4_VSNPRINTF

#ifdef C4_SNPRINTF
/// Visual Studio does not have snprintf
/// @see http://stackoverflow.com/questions/2915672/snprintf-and-visual-studio-2010
int snprintf(char* str, size_t size, const char* format, ...)
{
    int count;
    va_list ap;

    va_start(ap, format);
#if defined(C4_WIN) || defined(C4_XBOX)
    count = _vsnprintf_s(str, size, _TRUNCATE, format, ap);
#else
    count = vsnprintf(str, size, format, ap);
#endif
    va_end(ap);

    return count;
}
#endif // C4_SNPRINTF
