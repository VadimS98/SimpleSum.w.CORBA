#include "SimpleIDL.hh"
#include <omniORB4/CORBA.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

int main(int argc, char** argv) {
    /*if (argc != 2) {
        std::cerr << "Usage: client <object IOR>" << std::endl;
        return 1;
    }*/
    try {
        std::string ior, tmp;
        std::string iorFilename = "ior.txt";
        std::ifstream MyReadFile(iorFilename);

        if (!MyReadFile.is_open()) 
        {
            std::cerr << "No IOR file " << iorFilename << std::endl;
            return 1;
        }

        while (getline (MyReadFile, tmp)) 
        {
            ior += tmp;
        }

        MyReadFile.close();

        // Инициализация ORB
        CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
        // Преобразование строки IOR в объектную ссылку
        CORBA::Object_var obj = orb->string_to_object(ior.c_str());
        // Сужение ссылки к типу MyInterface
        MyInterface_var SimpleIDL = MyInterface::_narrow(obj);

        if (CORBA::is_nil(SimpleIDL)) 
        {
            std::cerr << "Can't narrow reference to type MyInterface (invalid IOR?)" << std::endl;
            return 1;
        }

        LongArray arrayWithNumbers;

        std::string NumbersFilename = "numbers.txt";
        std::ifstream NumbersFile(NumbersFilename);

        if (!NumbersFile.is_open()) 
        {
            std::cerr << "Cannot open file " << NumbersFilename << std::endl;
            return 1;
        }

        std::vector<long> numbersv;
        tmp = "";

        while (std::getline(NumbersFile, tmp)) 
        {
            std::stringstream ss(tmp);
            std::string number;

            while (std::getline(ss, number, ',')) {
                long num = std::stol(number);
                numbersv.push_back(num);
            }
        }

        arrayWithNumbers.length(numbersv.size());

        for (auto i = 0; i < numbersv.size(); ++i) {
            arrayWithNumbers[i] = numbersv[i];
        }   

        CORBA::Long result = SimpleIDL->Summa(arrayWithNumbers);
        std::cout << "The sum is: " << result << std::endl;

        // Разрушение ORB
        orb->destroy();

    } catch (const CORBA::Exception& ex) 
    {
        std::cerr << "Caught CORBA::Exception." << std::endl;
        return 1;
    }
    return 0;
}