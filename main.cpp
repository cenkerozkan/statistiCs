#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include <algorithm>
//#include <bits/stdc++.h> (Non - standard)

// Prototypes.
double calc_mean(std::vector<double> _vec);
double calc_median(std::vector<double> _vec);
double calc_dev_var(std::vector<double> _vec, double _mean, double* _variance, double* _deviation);
double calc_quartiles(std::vector<double> _vec, double* _quart1, double* _quart2, double _quart3);

int main(void) {
	std::cout << "\n\nHi, welcome to the statistiCs program!\nThis program has been written purely for educational\npurposes and does not offer any professional results.\nTherefore, it is not recommended for business use.\n\nIn short, statistiCs does the following calculations:\n\t1) Mean\n\t2) Median\n\t3) Standart deviation\n\t4) Standart variance\n\t5) Quartile 1 and Quartile 3\n\t6) IQR\n\nAnd sorts the dataset.\nNOTE: It only works with finite discrete datasets!\nYou need to input a txt file name located in the same directory as the program.\n\n";
	std::string sFlag;	// Loop flag.

	while (true) {
		std::cout << "\nTo continue, type 'c'.\nTo quit, type 'q'\n:";
		std::cin >> sFlag;

		// Quit.
		if (sFlag == "q" || sFlag == "Q") {
			break;
		}

		// Continue.
		else if (sFlag == "c" || sFlag == "C") {
			std::string filename;
			std::cout << "Enter the file name:\n";
			std::cin >> filename;


			std::ifstream fin(filename);
			// File not found.
			if (!fin.is_open()){
				std::cerr << "File not found.\n";
			}
			// File exists.
			else{
				// Using vector instead of an array.
				std::vector<double> vec;
				while (!fin.eof()) {
					// It is a temporary solution.
					// Unefficient. Fix later.
					double temp;
					fin >> temp;
					vec.push_back(temp);
				}
				sort(vec.begin(), vec.end());	// Using STL sort, instead of bubble sort.
				for(int i=0; i<vec.size(); i++){
					//DEBUG.
					std::cout << vec[i] << std::endl;
				}
				double mean = calc_mean(vec);
				std::cout << mean << std::endl;
			}
			fin.close();
		}
	}
}


// Functions.
double calc_mean(std::vector<double> _vec) {
	double temp = 0;
	for (int i = 0; i < _vec.size(); i++) {
		temp += _vec[i];
	}
	return temp / _vec.size();
}
//double calc_median(std::vector<double> _vec);
//double calc_dev_var(std::vector<double> _vec, double _mean, double &_variance, double &_deviation);
//double calc_quartiles(std::vector<double> _vec, double &_quart1, double &_quart2, double &_quart3);
