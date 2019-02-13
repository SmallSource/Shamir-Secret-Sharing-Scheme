#include <random>
#include <vector>
#include <string>
#include <cmath>
#include "SecretPair.h"

#define MIN_SECRET  1
#define MAX_SECRET  100000

#define PRIME       104729

using namespace std;

/* Generate a random number in the interval (min, max) */
int generateRandomNumber(int min, int max);

/* Generate random coefficients for the polynom used */
vector<int> generateCoefficients(int k, int secret);

/* Calculate the n (x,y) pairs for a given polynom */
vector<SecretPair> calculateSecretPairs(int n, vector<int> coefficients);

/* find the find the inverse inv for a number num such that inv * num % p=1 */
void gcdExtended(long long a, long long b, long long *x, long long *y);

/* Reconstruct the secret from k (x,y) pairs */
long long reconstructSecret(vector<SecretPair> secretPairs);

