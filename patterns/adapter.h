#ifndef PATTERNS_ADAPTER_H
#define PATTERNS_ADAPTER_H
#include "mainwindow.h"
#include "qtextstream"
class MainWindow;

namespace Patterns{
namespace Adapter{

class IClientServices
{
public:
    virtual void Operation1(void) = 0;
};


/**
 * @brief The Client class Wants/can only execute the operation from the IClientServices interface
 */
class Client
{
public:
    Client(IClientServices* adaptable_object)
    {
        _adaptable_object = adaptable_object;
    }
    ~Client()
    {
    }

    void IAlwaysCallThisMethodButWantItToBeAdaptedExternally(void)
    {
        ::MainWindow::qout<<"This Must Do different Things According To adaptable object supplied"<<endl;
        _adaptable_object->Operation1();
    }
private:
    IClientServices* _adaptable_object;
};

/**
 * @brief The ThingToAdaptTo class
 * is a class that can't be changed it has a method signature that can't be used by our client
 * straightforwardly (like from a compiled API or sensitiv code)
 *
 */
class ThingToAdaptTo
{
public:
    void NeededOperation(qint32 different_signature)
    {
        ::MainWindow::qout << "NeededOperation() : Success ! we adapted our client's inteface to the ThingToAdaptTo object though the Adapter object"<<endl;
        ::MainWindow::qout << "NeededOperation() : this code can't be changed and we need to call it from the client"<<endl;
    }
};

class ConcreteAdapter : public IClientServices
{
public:
    ConcreteAdapter(ThingToAdaptTo* thing_to_adapt)
    {
        _adaptee = thing_to_adapt;
        _stub_integer = 0; //can be set externally if needed
    }
    void Operation1 (void)
    {
        ::MainWindow::qout << "Operation1() : ConcreteAdapter's call will redirect the call to adapte it "<<endl;
        _adaptee->NeededOperation(_stub_integer);
    }
    void Operation2 (void)
    {
        ::MainWindow::qout << "Operation2() : ConcreteAdapter's call will redirect the call to adapte it "<<endl;
        _adaptee->NeededOperation(_stub_integer);
    }
private:
    ThingToAdaptTo* _adaptee;
    qint32 _stub_integer;
};



} /* Adapter */
} /* Patterns */

#endif // PATTERNS_ADAPTER_H
