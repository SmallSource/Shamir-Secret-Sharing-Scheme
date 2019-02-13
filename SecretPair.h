/* A pair that will be sent to one of the users (x, f(x)) */

class SecretPair
{
    private:
        /* x and f(x) */
        long long x, y;

    public:
        /* constructors */
        SecretPair();
        SecretPair(long long number, long long eval);

        /* getters */
        long long getX();
        long long getY();
};
