#include "SecretPair.h"

SecretPair::SecretPair()
{
    x = 0;
    y = 0;
}

SecretPair::SecretPair(long long number, long long eval)
{
    x = number;
    y = eval;
}

long long SecretPair::getX()
{
    return x;
}

long long SecretPair::getY()
{
    return y;
}

