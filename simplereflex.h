#ifndef SIMPLEREFLEX_H
#define SIMPLEREFLEX_H
#include <type_traits>
#include <tuple>

namespace SimpleReflex{
struct init
{
    template <typename T>
    operator T(); // never defined
};

template <unsigned I>
struct tag : tag<I - 1> {};

template <>
struct tag<0> {};

template <typename T>
constexpr auto size_(tag<30>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 30u; }
template <typename T>
constexpr auto size_(tag<29>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 29u; }
template <typename T>
constexpr auto size_(tag<28>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 28u; }
template <typename T>
constexpr auto size_(tag<27>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 27u; }
template <typename T>
constexpr auto size_(tag<26>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 26u; }
template <typename T>
constexpr auto size_(tag<25>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 25u; }
template <typename T>
constexpr auto size_(tag<24>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 24u; }
template <typename T>
constexpr auto size_(tag<23>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 23u; }
template <typename T>
constexpr auto size_(tag<22>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 22u; }
template <typename T>
constexpr auto size_(tag<21>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 21u; }
template <typename T>
constexpr auto size_(tag<20>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 20u; }
template <typename T>
constexpr auto size_(tag<19>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 19u; }
template <typename T>
constexpr auto size_(tag<18>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 18u; }
template <typename T>
constexpr auto size_(tag<17>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 17u; }
template <typename T>
constexpr auto size_(tag<16>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 16u; }
template <typename T>
constexpr auto size_(tag<15>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 15u; }
template <typename T>
constexpr auto size_(tag<14>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 14u; }
template <typename T>
constexpr auto size_(tag<13>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 13u; }
template <typename T>
constexpr auto size_(tag<12>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 12u; }
template <typename T>
constexpr auto size_(tag<11>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 11u; }
template <typename T>
constexpr auto size_(tag<10>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 10u; }
template <typename T>
constexpr auto size_(tag<9>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 9u; }
template <typename T>
constexpr auto size_(tag<8>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 8u; }
template <typename T>
constexpr auto size_(tag<7>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 7u; }
template <typename T>
constexpr auto size_(tag<6>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 6u; }
template <typename T>
constexpr auto size_(tag<5>)
-> decltype(T{init{}, init{}, init{}, init{}, init{}}, 0u)
{ return 5u; }

template <typename T>
constexpr auto size_(tag<4>)
-> decltype(T{init{}, init{}, init{}, init{}}, 0u)
{ return 4u; }

template <typename T>
constexpr auto size_(tag<3>)
-> decltype(T{init{}, init{}, init{}}, 0u)
{ return 3u; }

template <typename T>
constexpr auto size_(tag<2>)
-> decltype(T{init{}, init{}}, 0u)
{ return 2u; }

template <typename T>
constexpr auto size_(tag<1>)
-> decltype(T{init{}}, 0u)
{ return 1u; }

template <typename T>
constexpr auto size_(tag<0>)
-> decltype(T{}, 0u)
{ return 0u; }

template <typename T>
constexpr std::size_t size_s()
{
#if __cplusplus >= 201703L
    static_assert(std::is_aggregate_v<T>, "your struct is not aggregate ({}), correct it or use boost.PFR instead");
#endif
    return size_<T>(tag<25>{}); // highest supported number
}


template <typename T>
auto as_tuple(T const& v)
{
#if __cplusplus >= 201703L
   static_assert(std::is_aggregate_v<T>);
#endif
  if constexpr (size_s<T>() == 30u){
      const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29, m30] = v;
      return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29, m30);
  }
  else if constexpr (size_s<T>() == 29u){
      const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29] = v;
      return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29);
  }
  else if constexpr (size_s<T>() == 28u){
      const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28] = v;
      return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28);
  }
  else if constexpr (size_s<T>() == 27u){
      const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27] = v;
      return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27);
  }
  else if constexpr (size_s<T>() == 26u){
      const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26] = v;
      return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26);
  }
  else if constexpr (size_s<T>() == 25u){
      const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25] = v;
      return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25);
  }
  else if constexpr (size_s<T>() == 24u){
      const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24] = v;
      return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24);
  }
  else if constexpr (size_s<T>() == 23u){
        const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23] = v;
        return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23);
  }
  else if constexpr (size_s<T>() == 22u){
        const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22] = v;
        return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22);
  }
  else if constexpr (size_s<T>() == 21u){
        const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21] = v;
        return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21);
  }
  else if constexpr (size_s<T>() == 20u){
        const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20] = v;
        return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20);
  }
  else if constexpr (size_s<T>() == 19u){
        const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19] = v;
        return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19);
  }
  else if constexpr (size_s<T>() == 18u){
         const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18] = v;
        return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18);
  }
  else if constexpr (size_s<T>() == 17u){
      const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17] = v;
      return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17);
  }
  else if constexpr (size_s<T>() == 16u){
      const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16] = v;
      return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16);
  }
  else if constexpr (size_s<T>() == 15u){
      const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15] = v;
      return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15);
  }
   else if constexpr (size_s<T>() == 14u){
       const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29, m30] = v;
       return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29, m30);
   }
   else if constexpr (size_s<T>() == 13u){
       const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29] = v;
       return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29);
   }
   else if constexpr (size_s<T>() == 12u){
       const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28] = v;
       return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28);
   }
   else if constexpr (size_s<T>() == 11u){
       const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27] = v;
       return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27);
   }
   else if constexpr (size_s<T>() == 10u){
       const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26] = v;
       return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26);
   }
   else if constexpr (size_s<T>() == 9u){
       const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25] = v;
       return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25);
   }
   else if constexpr (size_s<T>() == 8u){
       const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24] = v;
       return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24);
   }
   else if constexpr (size_s<T>() == 7u){
         const auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23] = v;
         return std::tie(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23);
   }
   else if constexpr (size_s<T>() == 6u){
         const auto& [m0, m1, m2, m3, m4, m5] = v;
         return std::tie(m0, m1, m2, m3, m4, m5);
   }
   else if constexpr (size_s<T>() == 5u){
         const auto& [m0, m1, m2, m3, m4] = v;
         return std::tie(m0, m1, m2, m3, m4);
   }
   else if constexpr (size_s<T>() == 4u){
         const auto& [m0, m1, m2, m3] = v;
         return std::tie(m0, m1, m2, m3);
   }
   else if constexpr (size_s<T>() == 3u){
         const auto& [m0, m1, m2] = v;
         return std::tie(m0, m1, m2);
   }
   else if constexpr (size_s<T>() == 2u){
          const auto& [m0, m1] = v;
         return std::tie(m0, m1);
   }
   else if constexpr (size_s<T>() == 1u){
       const auto& [m0] = v;
       return std::tie(m0);
   }

}



template <typename T, typename F>
void for_each_member(T & v, F f)
{
#if __cplusplus >= 201703L
static_assert(std::is_aggregate_v<T>);
#endif
if constexpr (size_s<T>() == 30u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7); f(m8); f(m9);  f(m10); f(m11); f(m12); f(m13); f(m14); f(m15); f(m16); f(m17);
    f(m18); f(m19); f(m20); f(m21); f(m22); f(m23);  f(m24);  f(m25); f(m26); f(m27); f(m28); f(m29);
}
if constexpr (size_s<T>() == 29u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7); f(m8); f(m9);  f(m10); f(m11); f(m12); f(m13); f(m14); f(m15); f(m16); f(m17);
    f(m18); f(m19); f(m20); f(m21); f(m22); f(m23);  f(m24);  f(m25); f(m26); f(m27); f(m28);
}
if constexpr (size_s<T>() == 28u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7); f(m8); f(m9);  f(m10); f(m11); f(m12); f(m13); f(m14); f(m15); f(m16); f(m17);
    f(m18); f(m19); f(m20); f(m21); f(m22); f(m23);  f(m24);  f(m25); f(m26); f(m27);
}
if constexpr (size_s<T>() == 27u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7); f(m8); f(m9);  f(m10); f(m11); f(m12); f(m13); f(m14); f(m15); f(m16); f(m17);
    f(m18); f(m19); f(m20); f(m21); f(m22); f(m23);  f(m24);  f(m25); f(m26);
}
if constexpr (size_s<T>() == 26u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24, m25] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7); f(m8); f(m9);  f(m10); f(m11); f(m12); f(m13); f(m14); f(m15); f(m16); f(m17);
    f(m18); f(m19); f(m20); f(m21); f(m22); f(m23);  f(m24);  f(m25);
}
if constexpr (size_s<T>() == 25u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23, m24] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7); f(m8); f(m9);  f(m10); f(m11); f(m12); f(m13); f(m14); f(m15); f(m16); f(m17);
    f(m18); f(m19); f(m20); f(m21); f(m22); f(m23);  f(m24);
}
if constexpr (size_s<T>() == 24u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22, m23] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7); f(m8); f(m9);  f(m10); f(m11); f(m12); f(m13); f(m14); f(m15); f(m16); f(m17);
    f(m18); f(m19); f(m20); f(m21); f(m22); f(m23);
}
if constexpr (size_s<T>() == 23u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21, m22] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7); f(m8); f(m9);  f(m10); f(m11); f(m12); f(m13); f(m14); f(m15); f(m16); f(m17);
    f(m18); f(m19); f(m20); f(m21); f(m22);
}
if constexpr (size_s<T>() == 22u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20, m21] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7); f(m8); f(m9);  f(m10); f(m11); f(m12); f(m13); f(m14); f(m15); f(m16); f(m17);
    f(m18); f(m19); f(m20); f(m21);
    }
if constexpr (size_s<T>() == 21u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19, m20] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7); f(m8); f(m9);  f(m10); f(m11); f(m12); f(m13); f(m14); f(m15); f(m16); f(m17);
    f(m18); f(m19); f(m20);
}

if constexpr (size_s<T>() == 20u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18, m19] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7); f(m8); f(m9);  f(m10); f(m11); f(m12); f(m13); f(m14); f(m15); f(m16); f(m17);
    f(m18); f(m19);
}
if constexpr (size_s<T>() == 19u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17, m18] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7); f(m8); f(m9);  f(m10); f(m11); f(m12); f(m13); f(m14); f(m15); f(m16); f(m17);
    f(m18);
}
if constexpr (size_s<T>() == 18u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16, m17] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7); f(m8); f(m9);  f(m10); f(m11); f(m12); f(m13); f(m14); f(m15); f(m16); f(m17);
}
if constexpr (size_s<T>() == 17u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7); f(m8); f(m9);  f(m10); f(m11); f(m12); f(m13); f(m14); f(m15); f(m16);
}
if constexpr (size_s<T>() == 16u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7); f(m8); f(m9);  f(m10); f(m11); f(m12); f(m13); f(m14); f(m15);
}
if constexpr (size_s<T>() == 15u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7); f(m8); f(m9);  f(m10); f(m11); f(m12); f(m13); f(m14);
}
if constexpr (size_s<T>() == 14u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7); f(m8); f(m9);  f(m10); f(m11); f(m12); f(m13);
}
if constexpr (size_s<T>() == 13u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7); f(m8); f(m9);  f(m10); f(m11); f(m12);
}
if constexpr (size_s<T>() == 12u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7); f(m8); f(m9);  f(m10); f(m11);
}
if constexpr (size_s<T>() == 11u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7); f(m8); f(m9);  f(m10);
}
if constexpr (size_s<T>() == 10u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8, m9] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7); f(m8); f(m9);
}
if constexpr (size_s<T>() == 9u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7, m8] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7); f(m8);
}

if constexpr (size_s<T>() == 8u){
    auto& [m0, m1, m2, m3, m4, m5, m6, m7] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6); f(m7);
}
if constexpr (size_s<T>() == 7u){
    auto& [m0, m1, m2, m3, m4, m5, m6] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5); f(m6);
}
if constexpr (size_s<T>() == 6u){
    auto& [m0, m1, m2, m3, m4, m5] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4); f(m5);
}
if constexpr (size_s<T>() == 5u){
    auto& [m0, m1, m2, m3, m4] = v;
    f(m0); f(m1); f(m2); f(m3); f(m4);
}
if constexpr (size_s<T>() == 4u){
    auto& [m0, m1, m2, m3] = v;
    f(m0); f(m1); f(m2); f(m3);
}
if constexpr (size_s<T>() == 3u){
    auto& [m0, m1, m2] = v;
    f(m0); f(m1); f(m2);
}
else if constexpr (size_s<T>() == 2u){
    auto& [m0, m1] = v;
    f(m0); f(m1);
}
else if constexpr (size_s<T>() == 1u){
    auto& [m0] = v;
    f(m0);
}
}
}

#endif // SIMPLEREFLEX_H
