/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <typeinfo>

template <typename T>
struct Typename
{
    static constexpr const char* get()
    {
        return typeid(T).name();
    }

    static constexpr bool exists = false;
};

#define TYPENAME(T) template <> struct Typename<T> { static constexpr const char* get() { return #T; } static constexpr bool exists = true; };
#define TYPENAME_ALIAS(T, N) template <> struct Typename<T> { static constexpr const char* get() { return N; } static constexpr bool exists = true; };

TYPENAME(int)
TYPENAME(double)
TYPENAME(float)
TYPENAME(bool)
TYPENAME(void)
TYPENAME(char)
TYPENAME_ALIAS(char*, "string")

constexpr const char* typename_int = Typename<int>::get();
constexpr const char* typename_double = Typename<double>::get();
constexpr const char* typename_float = Typename<float>::get();
constexpr const char* typename_bool = Typename<bool>::get();
constexpr const char* typename_void = Typename<void>::get();
constexpr const char* typename_char = Typename<char>::get();
constexpr const char* typename_string = Typename<char*>::get();