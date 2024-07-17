#include <cassert>
#include <unordered_set>
#include "test_common.hpp"
#include "../src/bitarray.hpp"
using tkoz::BitArray;

// for testing one use case, sieve or eratosthenes
std::unordered_set<size_t> primes = {
2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,
101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,
211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,
307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,
401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,
503,509,521,523,541,547,557,563,569,571,577,587,593,599,
601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,
701,709,719,727,733,739,743,751,757,761,769,773,787,797,
809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,
907,911,919,929,937,941,947,953,967,971,977,983,991,997};

int main()
{
    BitArray b1;
    assert(b1.size() == 0);
    size_t N = 280;
    BitArray b2(N,0), b3(N,1);
    for (size_t i = 0; i < N; ++i)
    {
        assert(b2.get(i) == false);
        assert(b3[i] == true);
    }
    N = 1000;
    // prime sieve
    b2 = BitArray(N,1);
    b2.set0(0);
    b2.set0(1);
    for (size_t i = 2; i*i < N; ++i)
    {
        if (!b2.get(i)) continue;
        for (size_t j = i*i; j < N; j += i)
            b2.set0(j);
    }
    for (size_t i = 0; i < N; ++i)
    {
        assert(b2.get(i) == (primes.find(i) != primes.end()));
    }
    // iterator test
    size_t p = 0;
    for (auto b : b2)
    {
        bool pp = primes.find(p++) != primes.end();
        assert(b == pp);
    }
    // copy ctor
    BitArray b4(b2);
    for (size_t i = 0; i < N; ++i)
        assert(b2.get(i) == b4.get(i));
    // set0 test
    b3 = BitArray(N,1);
    for (size_t i = 0; i < N; ++i)
        if (primes.find(i) == primes.end())
            b3.set0(i);
    for (size_t i = 0; i < N; ++i)
        assert(b2.get(i) == b3.get(i));
    // exceptions
    assert_throw(b4.at(-1));
    assert_throw(b4.at(N));
    assert(b4[0] == false);
    assert(999 < N && b4[999] == false);
    // set1 test
    for (size_t i = 0; i < N; ++i)
        if (!b3.get(i))
            b3.set1(i);
    for (size_t i = 0; i < N; ++i)
        assert(b3.get(i));
    return 0;
}
