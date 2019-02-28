#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include <filehelper.h>

int main()
{
    std::string filePath = "/home/iwanicki/sw/mk240Readout/data/signalToNoise_qualtitative";
    std::vector<std::string> dirSkipList = {"dump"};
    std::vector<std::string> files = filehelper::getAllFilesInDir(filePath, dirSkipList);

    std::cout << "Files used: " << files.size() << std::endl;

    for(unsigned int n=0; n<files.size(); ++n)
    {
        std::ifstream infile(files.at(n));
        std::string line;
        while (std::getline(infile, line))
        {
            std::string date, time;
            std::string st1, st2, st3, st4;
            std::istringstream iss(line);
            if (!(iss >> date >> time >> st1 >> st2 >> st3 >> st4)) { break; } // error
            //std::cout << date << "\t" << time << "\t" << st1 << "\t" << st2 << "\t" << st3 << "\t" << st4 << std::endl;
            double t1=filehelper::toDouble(st1), t2=filehelper::toDouble(st2), t3=filehelper::toDouble(st3), t4=filehelper::toDouble(st4);

        }
    }

    return 0;
}
