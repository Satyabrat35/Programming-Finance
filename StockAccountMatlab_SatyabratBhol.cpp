#include "mex.h"
#include "engine.h"
#include "Helper_SatyabratBhol.h"
#include "StockAccount_SatyabratBhol.h"

#include <iostream>
#pragma comment(dylib, "libmx.dylib")
#pragma comment(dylib, "libmex.dylib")
#pragma comment(dylib, "libeng.dylib")

using namespace std;


void StockAccount::plotGraphUsingMatlab() {
	Engine *ep;
	ep = engOpen(NULL);
	if (ep == NULL) {
		cout << "Error: engine open failed" << endl;
		exit(1);
	}
	
    // Get the number of records and plot it --
    // Considering only first 500 records
	int num = helpfunc.getNumberOfLines(PORTFOLIO_FILE);
	long time_first;
	double time[500]; 
	double value[500]; 

	ifstream ifs;
	int j = 0;
	ifs.open(PORTFOLIO_FILE);
	if (ifs.fail()) {
		cout << "Error: " << PORTFOLIO_FILE << " cannot open" << endl;
		return;
	} else {
		string line;
		while (getline(ifs, line) && j < 500) { 
			if (j == 0) {
				time_first = atof(helpfunc.getNthWordInString(line, 2).c_str()); // get the time of the first data
			}
            // Time in minutes
			time[j] = (atof(helpfunc.getNthWordInString(line, 2).c_str()) - time_first) / 60.0;
            // Portfolio Value 
			value[j] = atof(helpfunc.getNthWordInString(line, 1).c_str()); 
			j++;
		}
		ifs.close();
	}

	for (int i = 0; i < 500; ++i) {
        if(i < j) continue;
		time[i] = time[i - 1];
		value[i] = value[i - 1];
	}
    
	mxArray *X;
	X = mxCreateDoubleMatrix(1, 100, mxREAL);
	memcpy((void *)mxGetPr(X), (void *)time, sizeof(double) * 100);
	mxArray *Y;
	Y = mxCreateDoubleMatrix(1, 100, mxREAL);
	memcpy((void *)mxGetPr(Y), (void *)value, sizeof(double) * 100);

	engPutVariable(ep, "x", X);
	engPutVariable(ep, "y", Y);
    
	engEvalString(ep, "plot(x, y)");
    // Adding x-axis label
    engEvalString(ep, "xlabel('Time (mins)')");
    // engEvalString(ep, "xlim([0, 100])");

	// Add a pause
	// engEvalString(ep, "pause(30)");
    // Adding y-axis label
    engEvalString(ep, "ylabel('Total Portfolio Value ($)')");
    // engEvalString(ep, "ylim([5000, 15000])");
	// engEvalString(ep, "xlabel('Time'), ylabel('Total Portfolio Value ($)')");
	// engEvalString(ep, "set(gca,'YTickLabel',num2str(get(gca,'YTick').'))");
	// engEvalString(ep, "axis([-inf,inf,0,inf])");
    engEvalString(ep, "title('Portfolio Value Over Time')");
}