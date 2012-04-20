
#include <iostream>
#include <memory>
#include <typeinfo>
#include <utility>

#include <boost/make_shared.hpp>
#include <boost/python.hpp>

namespace bp = boost::python;

class Base
{
public:
    virtual ~Base() {}

    void SomeBaseFunc()
    {
        std::cout << "SomeBaseFunc" << std::endl;
    }
};

class Derived : public Base
{
public:
    virtual ~Derived() {}

    void SomeDerivedFunc()
    {
        std::cout << "SomeDerivedFunc" << std::endl;
    }
};

class Derived2 : public Derived
{
public:
    virtual ~Derived2() {}

    void SomeDerived2Func()
    {
        std::cout << "SomeDerived2Func" << std::endl;
    }
};

class BaseCallback : public Base, public bp::wrapper<Base>
{

};

boost::shared_ptr<Derived> CreateDerived()
{
    return boost::make_shared<Derived>();
}

boost::shared_ptr<Derived> CreateDerived2()
{
    return boost::make_shared<Derived2>();
}

BOOST_PYTHON_MODULE(testlib)
{
    bp::class_<Base, boost::shared_ptr<Base>, boost::noncopyable>("Base", "Describes Base")
        .def("SomeBaseFunc", &Base::SomeBaseFunc, "Describes SomeBaseFunc");

    bp::class_<Derived, bp::bases<Base>, boost::shared_ptr<Derived>, boost::noncopyable>("Derived", "Describes Derived")
        .def("SomeDerivedFunc", &Derived::SomeDerivedFunc, "Describes SomeDerivedFunc");

    bp::class_<Derived2, bp::bases<Derived>, boost::shared_ptr<Derived2>, boost::noncopyable>("Derived2", "Describes Derived2")
        .def("SomeBaseFunc", &Base::SomeBaseFunc, "Describes SomeBaseFunc")
        .def("SomeDerivedFunc", &Derived::SomeDerivedFunc, "Describes SomeDerivedFunc")
        .def("SomeDerived2Func", &Derived2::SomeDerived2Func, "Describes SomeDerived2Func");

    bp::def("CreateDerived", CreateDerived, "Describes CreateDerived");
    bp::def("CreateDerived2", CreateDerived2, "Describes CreateDerived2");
}
