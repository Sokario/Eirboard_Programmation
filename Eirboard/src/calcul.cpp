/*****************************************************/
/*                Calcul Architecture                */
/*                   STM32F429ZI                     */
/*                                                   */
/*****************************************************/

#include "include/calcul.hpp"

// Convert a binary string to a binary int
u32 s2bin(const char *s)
{
    u32 i = 0;
    while (*s)
    {
        i <<= 1;
    	i += *s++ - '0';
    }
    return i;
}

u32 bitsCount(u32 n)
{
    u32 c = 0;
    while(n != 0){
        u32 a = n & -n;
        n = n ^ a;
        c++;
    }
    return c;
}

u32 bitsParity (u32 data)
{
    return bitsCount (data) & 1;
}