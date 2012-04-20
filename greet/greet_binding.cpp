
#include <boost/python/def.hpp>
#include <boost/python/module.hpp>

#include "greet.h"

namespace bp = boost::python;

BOOST_PYTHON_MODULE(greet)
{
    bp::def("say_greeting", greet::say_greeting);
    bp::def("shout_greeting", greet::shout_greeting);
}
