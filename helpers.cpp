#include "helpers.h"
#include <iostream>

int generateRandomNumber(int min, int max)
{
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);

    return dist(rng);
}

vector<int> generateCoefficients(int k, int secret)
{
    /* coefficients of the k-1 degree polynom */
    vector<int> coefficients(k);

    /* f(0) must be equal with the secret */
    coefficients[0] = secret;

    for (int i = 1; i < k; i++)
        /* coefficients should be smaller than PRIME */
        coefficients[i] = generateRandomNumber(MIN_SECRET, MAX_SECRET);

    return coefficients;
}

vector<SecretPair> calculateSecretPairs(int n, vector<int> coefficients)
{
    vector<SecretPair> shareSecretPoints(n);

    int k = coefficients.size();

    /* Calculate P(x) for the n numbers */
    for (int number = 1; number <= n; number++) {
        long long accumulator = coefficients[0];

        for (int exp = 1; exp < k; exp++) {

            /* Calculate x^exp */
            long long current = 1;
            for (int i = 1; i <= exp; i++) 
                current = (current * number) % PRIME;

            current = (current * coefficients[exp]) % PRIME;

            accumulator = (accumulator + current) % PRIME;
        }

        /* Store the (x,y) pair */
        shareSecretPoints[number-1] = SecretPair(number, accumulator);
    }

    return shareSecretPoints;
}

/* ax + by = gcd(a, b) */
void gcdExtended(long long a, long long b, long long *x, long long *y)
{
    if (b == 0)
    {
        *x = 1;
        *y = 0;
    } else {
        long long n = a / b;
        long long c = a % b;

        long long x1, y1;
        gcdExtended(b, c, &x1, &y1);

        *x = y1;
        *y = x1 - y1 * n;
    }
}

long long reconstructSecret(vector<SecretPair> secretPairs)
{
    long long secret = 0;

    /* Formula 
     * Sum[0-k](Prod((x-xj)/(xi-xj)) * yi) */

    int k = secretPairs.size();

    for (int i = 0; i < k; i++) {
        
        /* Prod of (x-xj) */
        int upper = 1;

        /* Prod of (xi-xj) */
        int lower = 1;

        /* Calculate the current Prod((x-xj)/(xi-xj)) */
        for (int j = 0; j < k; j++) {
            if (i == j)
                continue;

            int xi = secretPairs[i].getX();
            int xj = secretPairs[j].getX();

            upper = (upper * xj * -1) % PRIME;
            lower = (lower * (xi -xj)) % PRIME;
        }

        long long yi = secretPairs[i].getY();
        
        /* Calculate the inverse from gcd for lower */
        long long x, y;
        long long prime = PRIME;

        int ok = 0;
        if (lower < 0) {
            ok = 1;
            lower *= -1;
        }

        gcdExtended(prime, lower, &x, &y);

        if (ok == 1)
            y *= -1;

        lower = (y + PRIME) % PRIME;

        /* Proceed with upper/lower * yi */
        long long current = (upper * lower) % PRIME;
        current = (current * yi) % PRIME;
        
        secret = (PRIME + secret + current) % PRIME;
    }

    return secret;
}
