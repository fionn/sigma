// This is a program to study spontaneous symmetry breaking in 
// the O(4) sigma model. It's kind of like a generalisation of 
// the Higgs field and can be thought of as a low-energy
// approximation of the pion field in quantum chromodynamics,
// where isospin symmetry is the O(3) subgroup and the pions
// are the pseudo-Goldstone bosons.

/* TODO:
* set lambda, v for correlator
*/

#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <getopt.h>

#include "field.h"
#include "histogram.h"
#include "latticeupdate.h"
#include "sum.h"
#include "correlator.h"
#include "correlate.h"
#include "print_field.h"
#include "help.h"
#include "sigma.h"

int main(int argc, char *argv[])
{
    using namespace std;

    int SIZE = 8;
    int max1 = SIZE;
    int max2 = SIZE;
    int max3 = SIZE;
    int max4 = SIZE;
    const int maxN = 4;

    int updatemax = 5000;
    double resolution = 0.05; 
    double delta = 0.05;

    srand48((unsigned)time(NULL));

    bool hotstart = false;
    bool runcorrelator = false;
    bool printfield = false;
    
    while(true)
    {
        static struct option long_options[] =
        {
            {"help",        no_argument,       0, 'h'},
            {"temp",        required_argument, 0, 't'},
            {"temperature", required_argument, 0, 't'},
            {"correlate",   no_argument,       0, 'c'},
            {"gauss",       no_argument,       0, 'g'},
            {"resolution",  required_argument, 0, 'r'},
            {"delta",       required_argument, 0, 'd'},
            {"iterations",  required_argument, 0, 'i'},
            {"size",        required_argument, 0, 's'},
            {"beta",        required_argument, 0, 'b'},
            {"printfield",  no_argument,       0, 'p'},
            {"lagrangian",  no_argument,       0, 'l'},
            {0, 0, 0, 0}
        };

        int option_index = 0;
        int c = getopt_long(argc, argv, "ht:cgr:d:i:s:b:lp", 
                                 long_options, &option_index);

        if(c == -1)
            break;

        int index_start;
        switch(c)
        {
            case 'h':
                help(argv[0]);
                return 0;

            case 't':
                if(string(optarg) == "hot")
                    hotstart = true;
                else if(string(optarg) == "cold")
                    hotstart = false;
                else
                {
                    cerr << "Usage: " << argv[0] << " --temperature " 
                         << "\e[4mhot\e[0m|\e[4mcold\e[0m" << endl;
                    return -1;
                }
                break;

            case 'c':
                runcorrelator = true;
                break;

            case 'g':
                histogram();
                return 0;

            case 'r':
                resolution = atof(optarg);
                if(resolution <= 0 || resolution > 1)
                {
                    cerr << resolution << " is not in (0, 1]." << endl;
                    return -1;
                }
                break;

            case 'd':
                delta = atof(optarg);
                if(delta < 0)
                {
                    cerr << "Δ = " << delta << " ∉ [0, +∞)." << endl;
                    return -1;
                }
                break;

            case 'i':
                updatemax = atof(optarg);
                if(updatemax <= 0)
                {
                    cerr << "Iterations must be nonnegative." << endl;
                    return -1;
                }
                break;

            case 's':
                SIZE = atof(optarg);
                optind--;
                index_start = optind;
                int size[4];
                for(; optind < argc && *argv[optind] != '-'; optind++)
                {
                    cout << argv[optind] << endl;
                    size[optind - index_start] = atof(argv[optind]);
                    if(size[optind - index_start] <= 0)
                    {
                        cerr << "All spacetime dimensions must be positive.\n";
                        return -1;
                    }
                    cout << size[optind - index_start] << endl;
                }
                if(optind - index_start == 4) 
                {
                    max1 = size[0];
                    max2 = size[1];
                    max3 = size[2];
                    max4 = size[3];
                }
                else if(optind - index_start == 1)
                {
                    max1 = SIZE;
                    max2 = SIZE;
                    max3 = SIZE;
                    max4 = SIZE;
                }
                else
                {
                    cerr << "Spacetime has 4 dimensions." << endl;
                    cerr << "All spacetime dimensions must be positive." << endl;
                    cerr << "Usage: sigma --size "
                         << "\e[4mx\e[0m [\e[4my\e[0m \e[4mz\e[0m \e[4mt\e[0m]\n"
                         << "If only one dimension is specified, the lattice will "
                         << "be set as isotropic." << endl;
                    return -1;
                }
                break;

            case 'b':
                cerr << "Set the value of inverse temperature β = 1 / (k_B T)." << endl;
                cerr << "This option is not implemented. Defaulting to β = 1." << endl; 
                //return -1;
                break;

            case 'p':
                printfield = true;
                break;

            case 'l':
                cout << "Our Lagrangian is\n\t"
                     << "𝓛 = ∂ᵞϕⁱ∂ᵧϕⁱ+ ½μ²ϕⁱϕⁱ- ¼λ(ϕⁱϕⁱ)²." << endl;
                return 0;

            case '?':
                cerr << "Try " << argv[0] << " --help." << endl;
                return -1;
        }
    }

    Field phi(max1, max2, max3, max4, maxN);

    string iso, start;
    if(phi.x1 == phi.x2 && phi.x2 == phi.x3 && phi.x3 == phi.x4)
        iso = "Isotropic";
    else
        iso = "Anisotropic";
    if(hotstart)
        start = "hot";
    else
        start = "cold";

    stringstream filename;
    filename << start << ".update(" << updatemax << ").delta(" 
             << delta << ").lattice(" << phi.x1 << phi.x2 << phi.x3 << phi.x4 
             << ")" << ".dat";

    cout << iso << " lattice Λ(" 
         << phi.x1 << "," << phi.x2 << "," << phi.x3 << "," << phi.x4 
         << ") with " << phi.x1 * phi.x2 * phi.x3 * phi.x4 << " sites." << endl;
    cout << "Δ = " << delta << "." << endl;
    cout << "Field ϕ started " << start << "." << endl;
    cout << "Saving to " << filename.str().c_str() << ".\n" << endl;

    time_t mainbegin, mainend;  
    time(&mainbegin);

    if(runcorrelator)
    {
        for(int j = 0; j < 40; j++)
        {
            const double lambda = -0.4; // have a flag
            const double v = 0.6;       // for these

            cout << "\nRUN " << j + 1 << " / 40" << endl;

            sigma(phi, lambda, v, updatemax, delta, hotstart, filename, 
                  start, printfield, resolution, mainbegin, mainend);
            correlate(phi, lambda, v, start, updatemax, delta);
        }

        return 0;
    }
        
    for(double lambda = -1.0; lambda <= 1.0; lambda += resolution)
        for(double v = 0.0; v <= 1.0; v += resolution)
        {
            int t = sigma(phi, lambda, v, updatemax, delta, hotstart, filename, 
                          start, printfield, resolution, mainbegin, mainend);
            cout << "Estimated " << t / 60 << " minutes remaining.\n" << endl;
        } 

    cout << "\t\e[96m👻 \e[0m all done.\n" << endl;

    return 0;   
}

