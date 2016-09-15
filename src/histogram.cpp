#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>
#include "pandora.h"
#include "histogram.h"

using namespace std;

void histogram()        // This checks pandora() by creating a histogram.
{
    double x, centre = 0, range = 5;
    int i, count[10000];
    double imax = 1E7;
    
    time_t hist0, hist1;    
    time(&hist0);
    
    cout << "\nChecking the random number generator for " << imax << " points in " << flush;
    
    for(i = 0; i < 10000; i++)
        count[i] = 0;

    for(i = 0; i < imax; i++)
    {
        x = (pandora() + centre);

        if(x > -range && x < range)
            count[(int)((x + 5.) * 1000.)]++;
        else
            i--;
    }
    
    stringstream filename;
    filename << "histogram" << imax << ".dat";
    ofstream output;
    output.open(filename.str().c_str());

    for(i = 0; i < 10000; i++)
        output << (double) i / 1000 - 5 << "\t" << count[i] << "\t" << x << endl;
    
    output.close();
    
    time(&hist1);
    
    cout << difftime(hist1, hist0) << "s.\nOutput at \"" << filename.str().c_str() << "\".\n" << endl;
}

