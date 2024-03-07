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

        SumCalculationImpl* myServant = new SumCalculationImpl;
        PortableServer::ObjectId_var myServantId = poa->activate_object(myServant);
        CORBA::Object_var myServantRef = poa->id_to_reference(myServantId);

        CORBA::String_var ior = orb->object_to_string(myServantRef);

        std::ofstream myfile("ior.txt");
        myfile << ior;
        myfile.close();

        poa_manager->activate();
        orb->run();
    } 
    catch (const CORBA::Exception& ex) 
    {
        std::cerr << "Caught CORBA::Exception." << std::endl;
        return 1;
    }
    return 0;
}