
#include <boost/python.hpp>
#include <boost/thread.hpp>

#include "python_helpers.hpp"

BOOST_PYTHON_MODULE(TEST1)
{
    bp::class_<PythonDelayedCallback, boost::noncopyable>("DelayedCallback", bp::init<bp::object, float>())
        .def_readwrite("callback", &PythonDelayedCallback::callback, "callback to set that will finish the event")
        .def_readwrite("delay", &PythonDelayedCallback::delay, "delay that determines when the event will finish")
        ;
}