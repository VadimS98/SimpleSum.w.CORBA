#include "SimpleIDL.hh"

class SumCalculationImpl : public POA_MyInterface
{
public:
    SumCalculationImpl() {}
    virtual ~SumCalculationImpl() {}

    virtual CORBA::Long Summa(const LongArray& numbers) override {
        CORBA::Long sum = 0;
        for (CORBA::ULong i = 0; i < numbers.length(); ++i) {
            sum += numbers[i];
        }
        return sum;
    }
};