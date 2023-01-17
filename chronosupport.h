#ifndef CHRONOSUPPORT_H
#define CHRONOSUPPORT_H
#include <QDataStream>
#include <chrono>
#ifdef __linux__
inline QDataStream& operator << (QDataStream& ds, intmax_t n){
    int32_t lp = n & 0xffffffff;
    int32_t hp = (n & 0xffffffff00000000) >> 32;
    ds << lp << hp;
    return ds;
}
inline QDataStream& operator >> (QDataStream& ds, intmax_t& n){
    int32_t lp;
    int32_t hp;
    ds  >> lp >> hp;
    n = hp;
    n = (n << 32) + lp;
    return ds;
}
#endif
template <intmax_t Ttype, intmax_t TPeriod>
inline QDataStream& operator << (QDataStream& ds, const std::ratio<Ttype, TPeriod>&dur){
    ds << dur.den << dur.num;
    return ds;
}
template <intmax_t Ttype, intmax_t TPeriod>
inline QDataStream& operator >>(QDataStream& ds,  std::ratio<Ttype, TPeriod>&dur){
    intmax_t den, num;
    ds >> den >> num;
    dur = std::ratio<Ttype, TPeriod>(den, num);
    ds << dur.den << dur.num;
    return ds;
}
template <typename Ttype, typename TPeriod>
inline QDataStream& operator >> (QDataStream& ds, std::chrono::duration<Ttype, TPeriod>&dur){
    Ttype t;
    ds >> t;
    dur = std::chrono::duration<Ttype, TPeriod>(t);
    return ds;
}
template <typename Ttype, typename TPeriod>
inline QDataStream& operator << (QDataStream& ds, const std::chrono::duration<Ttype, TPeriod>&dur){
    ds << dur.count();
    return ds;
}

#endif // CHRONOSUPPORT_H
