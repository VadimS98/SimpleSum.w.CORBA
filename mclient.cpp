#include "SimpleIDL.hh"  // Подключите сгенерированный заголовочный файл для интерфейса
#include <omniORB4/CORBA.h>
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
    /*if (argc != 2) {
        std::cerr << "Usage: client <object IOR>" << std::endl;
        return 1;
    }*/
    try {
        std::string ior, tmp;
        std::ifstream MyReadFile("ior.txt");
        while (getline (MyReadFile, tmp)) {
            ior += tmp;
        }

        // Инициализация ORB
        CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

        // Преобразование строки IOR в объектную ссылку
        CORBA::Object_var obj = orb->string_to_object(ior.c_str());

        // Сужение ссылки к типу MyInterface
        MyInterface_var SimpleIDL = MyInterface::_narrow(obj);

        if (CORBA::is_nil(SimpleIDL)) {
            std::cerr << "Can't narrow reference to type MyInterface (invalid IOR?)" << std::endl;
            return 1;
        }

        // Вызов метода Summa

        LongArray arrayWithNumbers;
        arrayWithNumbers.length(5);
        arrayWithNumbers[0] = 10;
        arrayWithNumbers[1] = 0;
        arrayWithNumbers[2] = 3;
        arrayWithNumbers[3] = 20;
        arrayWithNumbers[4] = 100;

        CORBA::Long result = SimpleIDL->Summa(arrayWithNumbers);
        std::cout << "The sum is: " << result << std::endl;

        // Разрушение ORB
        orb->destroy();
    } catch (const CORBA::Exception& ex) {
        std::cerr << "Caught CORBA::Exception." << std::endl;
        return 1;
    }
    return 0;
}