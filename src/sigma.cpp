#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>

#include "field.hpp"
#include "latticeupdate.hpp"
#include "sum.hpp"
#include "print_field.hpp"
#include "sigma.hpp"

int sigma(Field phi, double lambda, double v, int updatemax, double delta, bool hotstart, std::stringstream& filename, std::string start, bool printfield, double resolution, time_t mainbegin, time_t mainend)
{
    using namespace std;

    if(hotstart)
		phi.hot_start();
	else
		phi.cold_start();

	cout << "\tλ = " << lambda << ", v = " << v 
			<< ", Δ = " << delta << "." << endl;

	time_t metrostart, metrofinish; 
	time(&metrostart);

	int accept = 0;
	for (int update = 1; update <= updatemax; ++update)
	{
		accept += latticeupdate(phi, lambda, v, delta);
	
		time(&metrofinish);

		//cout << "\rMetropolis progress (" << updatemax << " iterations): "
		//     << 100 * update / updatemax << "%" << flush;

		int i =  70 * update / updatemax;
		string progress = "[" + string(i, '-') + string(70 - i, ' ') + "] ";
		cout << "\r" << progress << 100 * update / updatemax << "%, " 
				<< difftime(metrofinish, metrostart) << "s" << flush;
	}

	//cout << "Metropolis accepted " << accept << " / " 
	//     << phi.x1 * phi.x2 * phi.x3 * phi.x4 * phi.N * updatemax 
	//     << " configurations (" 
	//     << (double(accept)) * 100 / (phi.x1 * phi.x2 * phi.x3 * phi.x4 * phi.N * updatemax) 
	//     << "\%)." << endl;

	double normalsigma = sigmasum(phi);
	double mass2 = 4 * lambda * v * v;

	ofstream output;
	output.open (filename.str().c_str(), std::ios_base::app);
	output << lambda << "\t" << v << "\t" 
			<< normalsigma << "\t" << mass2 << endl;
	output.close();

	cout << "\n\tm² = " << mass2 << ", " << flush;
	cout << "σ = " << normalsigma << "." << endl;

	if(printfield)
		print_field(phi);

	time(&mainend);
	int totalops = (2 / resolution + 1) * (1 / resolution + 1);
	int t = difftime(metrofinish, metrostart) * totalops - difftime(mainend, mainbegin);

    return t;
}

