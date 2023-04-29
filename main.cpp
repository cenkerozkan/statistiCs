/*
* Author: Cenker Özkan
* Date: 25.04.2023
* statistiCs (Mingw64 gcc11.2.0)
* v003
*
* Capabilities:
*	1 - Reads data from txt file.
*	2 - Sorts data set.
*	3 - Calculates mean. (Population)
*	4 - Calculates median.
*	5 - Calculates standard deviation. (Population)
*	6 - Calculates Quartile 1,3 and inner quartile range. (IQR)
*	7 - Prints the sorted data set and results into a new file.
*	8 - Automatic size allocation.
*	9 - "Save as" and "Save" options.
*/

//#pragma warning(disable:4996)	// To disable thread warn caused by localtime function.
//#include <iostream>
//#include <fstream>
//#include <chrono>	// time.h alternative.
//#include <vector>
//#include <algorithm>
#include <bits/stdc++.h> //(Non - standard)

// Prototypes.
double calc_mean(std::vector<double> _vec);
double calc_median(std::vector<double> _vec);
double calc_var(std::vector<double> _vec, double _mean);
void calc_quartiles(std::vector<double> _vec, double &_quart1, double &_quart3);
bool is_exist(std::string _filename);
void write_log(std::vector<double> _vec, double _mean, double _median, double _variance, double _quart1, double _quart3);
std::string time_curr();

int size=0;
int main(void) {
    std::cout << "Hi, welcome to the statistiCs program!\nThis program has been written purely for educational\npurposes and does not offer any professional results.\nTherefore, it is not recommended for business use.\n\nIn short, statistiCs does the following calculations:\n\t1) Mean\n\t2) Median\n\t3) Standart deviation\n\t4) Standart variance\n\t5) Quartile 1 and Quartile 3\n\t6) IQR\n\nAnd sorts the dataset.\nNOTE: It only works with finite discrete datasets!\nYou need to input a txt file name located in the same directory as the program.\n\n";
    // I know it is very inefficient to use a string
    // just for a single character check, but I'll
    // leave it that way for now.
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
                    size++;
                }
                sort(vec.begin(), vec.end());	// Using STL sort, instead of bubble sort.
                /*for (int i = 0; i<vec.size(); i++) {
                    //DEBUG.
                    std::cout << vec[i] << std::endl;
                }*/
                // Results.
                double mean = calc_mean(vec), median = calc_median(vec), variance = calc_var(vec, mean), q1 = 0, q3 = 0;
                calc_quartiles(vec, q1, q3);
                std::cout << "\n\nResults\n********\nMean: " << mean << "\nMedian: " << median << "\nStandard dev: " << sqrt(variance) << "\nVariance: " << variance << "\nQuartile1: " << vec[q1] << "\nIQR: " << vec[q3] - vec[q1] << "\nQuartile3: " << vec[q3] << "\n";
                write_log(vec, mean, median, variance, q1, q3);
            }
            fin.close();
        }
            // Invalid argument.
        else { std::cerr << "Invalid argument!\n"; }
    }
}


// Functions.
// Calculate mean.
double calc_mean(std::vector<double> _vec) {
    double temp = 0;
    for (int i = 0; i < size; i++) {
        temp += _vec[i];
    }
    return temp / _vec.size();
}

// Calculate median.
double calc_median(std::vector<double> _vec) {
    int temp = size;
    switch (temp) {
        // Even.
        case 0:
            return ((_vec[(temp - 1) / 2]) + (_vec[((temp - 1) / 2) + 1])) / 2;

            // Odd.
        default:
            return (_vec[(temp - 1) / 2]);
    }
    return 0;
}

// Calculate variance.
double calc_var(std::vector<double> _vec, double _mean) {
    double temp = 0;
    for (int i = 0; i < _vec.size(); i++) {
        temp += ((_vec[i] - _mean) * (_vec[i] - _mean) / size);
    }
    return temp;
}

// Calculate quartiles.
void calc_quartiles(std::vector<double> _vec, double& _quart1, double& _quart3) {
    _quart1 = 0.25 * (size + 1);
    _quart3 = 0.75 * (size + 1);
    // I will not include the interpolation process in this version for now.
    return;
}

// Check if there is a file with the same name.
bool is_exist(std::string _filename) {
    std::fstream fin(_filename);
    if (fin.is_open()) {return 1; fin.close();}
    fin.close();
    return 0;
}

// Explain later.
std::string time_curr() {
    std::chrono::system_clock::time_point p = std::chrono::system_clock::now();
    time_t t = std::chrono::system_clock::to_time_t(p);
    char str[26];
    ctime_s(str, sizeof str, &t);
    return str;
}


// New log function.
void write_log(std::vector<double> _vec, double _mean, double _median, double _variance, double _quart1, double _quart3) {
    int flag = 0;
    std::string var_time = time_curr();
    while (true) {
        std::cout << "\n\nSave(1)\nSave as(2)\n:";
        std::cin >> flag;
        std::ofstream fout;

        // Save.
        if (flag == 1) {
            time_t t = time(0);
            struct tm* now = localtime(&t);

            char buffer[80];
            strftime(buffer, 80, "%Y-%m-%d %I-%M-%S.txt", now);
            fout.open(buffer);
        }
            // Save as.
        else if (flag == 2) {
            std::string filename;
            std::cout << "Enter file name\n:";
            std::cin >> filename;

            // File check.
            if (is_exist(filename)) {
                std::cerr << "There is another file with the same name.\n";
            }
            else {
                // Create file.
                fout.open(filename);
            }
        }
        else { std::cerr << "Invalid argument.\n"; }
        fout << "Date & Time: " << var_time << "\n\nSize of the data set: " << _vec.size() << "\nMean: " << _mean << "\nMedian: " << _median << "\nStandard Dev: " << sqrt(_variance) << "\nVariance: " << _variance << "\nQuartile1: " << _vec[_quart1] << "\nIQR: " << _vec[_quart3] - _vec[_quart1] << "\nQuartile3: " << _vec[_quart3] << "\n\n\n";

        // Print sorted data.
        int j = 1;
        for (int i = 0; i < size; i++) {
            fout << _vec[i] << ",\t";
            j++;
            if (j%5 == 1) {
                fout << "\n";
            }
        }
        fout.close();
        break;
    }
}
