/// Copyright (c) Vito Domenico Tagliente

#include <string>

template <typename T>
struct TypeName
{
    static const char* get()
    {
        return typeid(T).name();
    }
};

#define TYPENAME(T) template <> struct TypeName<T> { static const char* get() { return #T; } };
#define TYPENAME_ALIAS(T, N) template <> struct TypeName<T> { static const char* get() { return N; } };

TYPENAME(int)
TYPENAME(double)
TYPENAME(float)
TYPENAME(bool)
TYPENAME(void)
TYPENAME(char)
TYPENAME(std::string)