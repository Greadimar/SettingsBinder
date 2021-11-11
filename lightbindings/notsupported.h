#ifndef NOTSUPPORTED_H
#define NOTSUPPORTED_H
#include <type_traits>
namespace {
template <typename T> void NOTSUPPORTED(){
    static_assert (std::is_same<T, void>::value, "This type is not supported" );
}
}

#endif // NOTSUPPORTED_H
