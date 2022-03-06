/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <typeinfo>

template <typename T>
struct TypeName
{
    static constexpr const char* get()
    {
        return typeid(T).name();
    }
};

#define TYPENAME(T) template <> struct TypeName<T> { static constexpr const char* get() { return #T; } };
#define TYPENAME_ALIAS(T, N) template <> struct TypeName<T> { static constexpr const char* get() { return N; } };

TYPENAME(int)
TYPENAME(double)
TYPENAME(float)
TYPENAME(bool)
TYPENAME(void)
TYPENAME(char)
TYPENAME_ALIAS(char*, "string")

constexpr const char* typename_int = TypeName<int>::get();
constexpr const char* typename_double = TypeName<double>::get();
constexpr const char* typename_float = TypeName<float>::get();
constexpr const char* typename_bool = TypeName<bool>::get();
constexpr const char* typename_void = TypeName<void>::get();
constexpr const char* typename_char = TypeName<char>::get();
constexpr const char* typename_string = TypeName<char*>::get();