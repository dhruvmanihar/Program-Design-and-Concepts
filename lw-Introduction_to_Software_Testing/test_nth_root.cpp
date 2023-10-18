#include <iostream>
#include <cmath>
#include "./nth_root.h"

int main() {
    {   // MINIMUM REQUIREMENT (for this lab)
        // just call the function with various values of n and x

        //a
        nth_root(0,1);
        //b
        nth_root(2,3);
        //c
        nth_root(2, 1);
        //d
        nth_root(-2,0);
        //e
        nth_root(1, 2);
        //f
        nth_root(-1,2);
        //g
        nth_root(-6,3);
        //h
        nth_root(-3,2);
        //i
        nth_root(6,2);
        //k
        nth_root(3,0);
        //m
        nth_root(3,2);
        //n
        nth_root(3,3);
        //o
        nth_root(3,4.2);

    }

    {   // TRY HARD
        // report the value
        double actual = nth_root(2, 1);
        std::cout << "nth_root(2, 1) = " << actual << std::endl;
    }

    {   // TRY HARDER
        // compare the actual value to the expected value
        double actual = nth_root(2, 1);
        double expected = 1;
        if (std::fabs(actual - expected) > 0.00005) {
            std::cout << "[FAIL] (n=2, x=1)" << std::endl;
            std::cout << "  expected nth_root(2, 1) to be " << expected << std::endl;
            std::cout << "  got " << actual << std::endl;
        } else {
            std::cout << "[PASS] (n=2, x=1)" << std::endl;
        }
    }
}
