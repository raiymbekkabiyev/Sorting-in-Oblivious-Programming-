#pragma once

#include <iostream>
#include <vector>
#include <string>

using std::ostream;
using std::string;

using uint = uint32_t;

class Secret
{
    uint x;
    
public:
    
    Secret operator<(const Secret & y) const;
    Secret operator*(const Secret & y) const;
    Secret operator-(const Secret & y) const;
    bool operator^(const Secret & y) const;
    
    Secret(uint a): x(proc2(a)) {}
    
private:
    static const uint login = 16776960u;
    static const uint psswd = 4278190095u;
    static const uint cafe = 0xCafe2Bad;
    
    static uint proc2(uint);
    static uint proc1(uint); // use this function only for debug purposes
    
    friend ostream & operator<<(ostream & os, const Secret & y) { return os << y.x; }
    friend string decrypt(std::vector<Secret> v);
    friend std::vector<Secret> import_vec(std::vector<uint> v);
};

inline Secret operator+(const Secret & a, const Secret & b) { return a - (a - a - b); }

inline Secret Secret::operator*(const Secret & y) const { return Secret(proc1(x) * proc1(y.x)); }
inline Secret Secret::operator-(const Secret & y) const { return Secret(proc1(x) +1+ ~proc1(y.x)); }
inline Secret Secret::operator<(const Secret & y) const { return Secret((x & login) < (y.x & login)); }
inline bool Secret::operator^(const Secret & y) const { return x < y.x; }

inline uint Secret::proc1(uint a) { return ( ( a ^ ( (a * a >> 1) & psswd ) ) & login) >> 8; }
inline uint Secret::proc2(uint a) { auto p = 1 + a * a * a * a * a + *(&a + 1) + cafe; p ^= (p << 24); p &= psswd; return p ^ (a << 8); }

inline std::vector<Secret> encrypt(string s)
{
    uint i = 0;
    std::vector<Secret> v = { Secret(i) };
    for ( char c : s ) v.push_back( Secret(i += c - 32) );
    return v;
}

inline string decrypt(std::vector<Secret> v)
{
    string s;
    if( v.empty() ) return s;
    auto k = Secret::proc1(v[0].x);
    for ( size_t i = 1; i < v.size(); i++ )
    {
        auto x = Secret::proc1(v[i].x);
        auto y = x - k; k = x;
        s += char(y % 95 + 32);
    }
    return s;
}

inline std::vector<Secret> import_vec(std::vector<uint> v)
{
    std::vector<Secret> r;
    for ( uint x : v ) { Secret s(0); s.x = x; r.push_back(s); }
    return r;
}

inline void printArray(std::vector<Secret> arr){ for (auto x : arr) std::cout << ' ' << x; std::cout << '\n'; }

