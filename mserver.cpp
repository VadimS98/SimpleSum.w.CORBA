#include "SumCalculationImpl.h"
#include <omniORB4/CORBA.h>
#include <iostream>
#include <fstream>

int main(int argc, char** argv) {
    try {
        CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
        CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
        PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);
        PortableServer::POAManager_var poa_manager = poa->the_POAManager();

        SumCalculationImpl* myServant = new SumCalculationImpl; // Изменено здесь
        PortableServer::ObjectId_var myServantId = poa->activate_object(myServant);
        CORBA::Object_var myServantRef = poa->id_to_reference(myServantId);

        // Нет необходимости явно вызывать _remove_ref для myServant
        // Так как POA управляет жизненным циклом сервантов

        CORBA::String_var ior = orb->object_to_string(myServantRef);
        std::cout << "IOR: " << ior.in() << std::endl;

        std::ofstream myfile("ior.txt");
        myfile << ior;
        myfile.close();

        poa_manager->activate();
        orb->run();
    } catch (const CORBA::Exception& ex) {
        std::cerr << "Caught CORBA::Exception." << std::endl;
        return 1;
    }
    return 0;
}

/*
int main(int argc, char** argv) {
    try {
        // Инициализация ORB
        CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

        // Получение ссылки на корневой POA
        CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
        PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);
        PortableServer::POAManager_var poa_manager = poa->the_POAManager();

        // Создание серванта
        PortableServer::Servant_var<SumCalculationImpl> myInterfaceImpl = new SumCalculationImpl();

        PortableServer::ObjectId_var myServantId = poa->activate_object(myServant);
        CORBA::Object_var myServantRef = poa->id_to_reference(myServantId);

        // Явное уменьшение счетчика ссылок на сервант, так как POA управляет его жизненным циклом
        myServant->_remove_ref();

        // Получение IOR (Interoperable Object Reference)
        CORBA::String_var ior = orb->object_to_string(myServantRef);

        // Активация POA Manager
        //poa_manager->activate();

        // Получение ссылки на объект
        //CORBA::Object_var myInterface_obj = myInterfaceImpl->_this();

        // Вывод строки объектной ссылки в формате IOR
        //CORBA::String_var ior = orb->object_to_string(myInterface_obj);

        std::ofstream myfile;
        myfile.open ("ior.txt");
        myfile << ior;
        myfile.close();

        std::cout << "IOR: " << ior << std::endl;

        // Запуск ORB
        orb->run();
    } catch (const CORBA::Exception& ex) {
        std::cerr << "Caught CORBA::Exception." << std::endl;
        return 1;
    }
    return 0;
}
*/