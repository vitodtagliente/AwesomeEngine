/// Copyright (c) Vito Domenico Tagliente

#include <climits>
#include <cstdint>
#include <type_traits>

#include "typename.h"

template <typename T = std::uintmax_t>
constexpr std::enable_if_t<std::is_integral<T>::value, T> TypeFactoryId(const char* const string) noexcept
{
    constexpr auto N = sizeof(T);
    T n{};
    std::size_t i{};
    while (string[i] && i < N)
        n = (n << CHAR_BIT) | string[i++];
    return (n << (N - i) * CHAR_BIT);
}

template <long unsigned int id>
struct TypeFactoryImp
{
    static void* instantiate()
    {
        return nullptr;
    }
};

#define REGISTER_TYPE(T) template <> struct TypeFactoryImp<TypeFactoryId(TypeName<T>::get())> { static void* instantiate() { return new Foo; } };

struct TypeFactory
{
    static void* instantiate(char* const name)
    {
        // return TypeFactoryImp<TypeFactoryId(name)>::instantiate();
        return nullptr;
    }
};