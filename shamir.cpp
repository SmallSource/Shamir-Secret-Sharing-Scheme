#include <iostream>
#include "helpers.h"

using namespace std;

void help();
void split();
void restore();

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cerr << "Usage: ./shamir --help\n";
        return -1;
    }

    string option = argv[1];

    if (option.compare("--split") == 0) {
        split();
    }
    else if (option.compare("--restore") == 0) {
        restore();
    }
    else {
        help();
    }

    return 0;
}

void help()
{
    cout << "You have two options for the program:\n";
    cout << "1. ./shamir --split.\n";
    cout << "2. ./shamir --restore.\n";
    cout << "Use either one of them to get guided.\n";
}

void split()
{
    cout << "Alright. What's your secret?\n";
    cout << "Please select a number between " << MIN_SECRET << " and " << MAX_SECRET << ":\n";
    cout << "Secret = ";

    /* Read the secret */
    int secret;
    cin >> secret;

    cout << "\nPlease select how many splits you want(n) and what's ";
    cout << "the minimum required to restore the secret(k).\n";

    /* Read n and k */
    int n, k;
    cout << "n = ";
    cin >> n;

    cout << "k = ";
    cin >> k;

    /* Check for n >= k */
    if (n < k) {
        cout << "The number of splits should be bigger than the minimum required to restore.\n";
        return;
    }

    cout << "\nThe polynom generated is: ";
    cout << "P(x) = (";
    
    /* Generate the polynom that will be used */
    vector<int> coefficients = generateCoefficients(k, secret);
    for (int i = 0; i < k; i++)
        if (i == k - 1)
            cout << coefficients[i] << " * x^" << k - 1 << ") % ";
        else
            cout << coefficients[i] << " * x^" << i << " + ";
    cout << PRIME << "\n";
    
    cout << "\nThe generated pairs (x, f(x)) are:\n";

    /* Generate the points that will be sent to the n users */
    vector<SecretPair> shareSecretPoints = calculateSecretPairs(n, coefficients);
    for (int i = 0; i < n; i++)
        cout << "(" << shareSecretPoints[i].getX() << "," << 
            shareSecretPoints[i].getY() << ")\n";
}

void restore()
{
    cout << "Please insert the minimum number required to restore(k): \n";
    cout << "k = ";

    /* Get the minimum required to restore */
    int k;
    cin >> k;

    cout << "Please insert k pairs (x, f(x)) in the format:\n";
    cout << "x1 f(x1)\nx2 f(x2)\n...\nxk f(xk).\n";

    /* Get the (x, f(x)) pairs */
    vector<SecretPair> secrets;
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
    
        secrets.push_back(SecretPair(x, y));
    }

    /* Restore the secret from the k pairs */
    cout << "Your secret was = " << reconstructSecret(secrets) << "\n";
}
