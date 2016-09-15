#include <iostream>
#include <sstream>
#include <fstream>

#include "field.h"
#include "correlator.h"
#include "correlate.h"

void correlate(Field phi, double lambda, double v, 
               std::string start, int updatemax, double delta)
{
    using namespace std;

    stringstream filename;
    filename << "correlation." << start << ".update(" << updatemax 
                << ").lambda(" << lambda << ").v(" << v 
                << ").delta(" << delta << ").lattice(" 
                << phi.x1 << phi.x2 << phi.x3 << phi.x4 << ")" << ".dat";

    ofstream output;
    output.open(filename.str().c_str());

    for(int d = 0; d <= phi.x4; d++)
        output << d << "\t" 
                << correlator(phi, d) / correlator(phi, 0) << endl;

    output.close();

    cout << "Saving " << filename.str().c_str() << "." << endl;
}
