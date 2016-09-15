#include <iostream>
#include "help.h"

void help(char* name)
{
    using namespace std;

    cout << "\e[1;34m⚛ SIGMA\e[0m is a Markov chain Monte Carlo Metropolis simulator for the O(4) linear \n  sigma model on a 4-dimensional spacetime lattice.\n" << endl;
    cout << "Usage: " << name << " [options]\n" << endl;

    cout << "If no options are given, sane defaults will be chosen.\n" << endl;

    cout << "Options:" << endl;
    cout << "\t-t, --temp \e[4mhot\e[0m|\e[4mcold\e[0m \tInitialise the field with a \e[4mhot\e[0m or \e[4mcold\e[0m start;" << endl;
    cout << "\t-c, --correlate\t\tRun the 2-point function;" << endl;
    cout << "\t-r, --resolution \e[4mx\e[0m\tIncrement λ and v by \e[4mx\e[0m ∈ (0, 1];" << endl;
    cout << "\t-i, --iterations \e[4mx\e[0m\tSet the number of Metropolis iterations to \e[4mx\e[0m > 0;" << endl;
    cout << "\t-s, --size \e[4mx\e[0m [\e[4my\e[0m \e[4mz\e[0m \e[4mt\e[0m]\tSet the size of the spacetime lattice;" << endl;
    cout << "\t-d, --delta \e[4mx\e[0m\t\tSet Δ = \e[4mx\e[0m ≥ 0;" << endl;
    cout << "\t-g, --gauss\t\tTest the random number generator;" << endl;
    cout << "\t-l, --lagrangian\tPrint the Lagrangian density;" << endl;
    cout << "\t-h, --help\t\tPrint this message and exit.\n" << endl;
}

