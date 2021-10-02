#include <iostream>
#include <algorithm>

#include "secret.h"

using namespace std;

Secret min(Secret x,Secret y)
{
    Secret cond1 = x<y; //since ! operator was not overloaded, define two conditions separtely
    Secret cond2 = y<x;
    auto min_obj = x*cond1 + y*cond2; //obligious was of writing if else statement
    return min_obj;
}
Secret max(Secret x,Secret y)
{
    Secret cond1 = x<y; //same as min function but for max value
    Secret cond2 = y<x;
    auto t = y*cond1 + x*cond2;
    return t;
}

void swap_if(Secret &x, Secret &y, Secret z)
{
    Secret cond1(1); // using Secret construction to create a secret object that would act like bool val = 1
    auto cond2 = cond1 - z; // same as !z (not z) condition
    //swap x and y if z=1 else remain as is. tmp is used to keep value of x when z=1
    Secret tmp = x;
    x = y*z + x*cond2;
    y = tmp*z + y*cond2;
    
}

void secret_sort(std::vector<Secret> & arr)
{
    //perfoming bubble sort
    int i, j;
    
    for(i=0; i<arr.size(); i++)
    {
        for(j=0; j<arr.size()-1; j++)
        {
            //passing two consequetive objects of secret vector
            swap_if(arr[j], arr[j+1], arr[j+1]<arr[j]); //z is defined from comparison of two consequetive elements. < operator is overloaded to return object of type Secret (same as z). 
        }
    }
}

void shuffle(std::vector<Secret> & arr)
{
    int n = (int)arr.size();
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if ( arr[j + 1] ^ arr[j] )
                std::swap(arr[j], arr[j + 1] );
}

void test()
{
    auto phrase = encrypt("Some phrase");
    cout << decrypt(phrase) << '\n';
    shuffle(phrase);
    cout << decrypt(phrase) << '\n';
    secret_sort(phrase);
    cout << decrypt(phrase) << '\n';
}
/* this function outputs:
 Some phrase
 ***********
 Some phrase
 */


int main()
{
    std::vector<uint> shuffled = { 285518085, 352427273, 687915277, 772094988, 973324812,
        1023617548, 1023617548, 1375820812, 1996510979, 2046984461, 2164405007,
        2181047308, 2248146956, 3322173964, 3506702083, 3657463820, 3657463820,
        3691114251, 3691134731, 3691134731, 3691330311, 3808498700, 3808498700,
        3892499980, 3926193676, 4060310279
    };
    
    
    auto secret = import_vec(shuffled);
    
    secret_sort(secret);
    
    cout << decrypt(secret) << '\n';
    
    
}
