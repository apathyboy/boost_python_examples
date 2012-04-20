
#include <boost/python.hpp>
#include <boost/thread.hpp>

#include "python_helpers.hpp"

static int delay = 100;

void hello(int id) {
	release_py_GIL unlocker;
    logger safe_cout;
	std::stringstream ss;
	ss << ">>> py: sleep: " << id << "\n";
	safe_cout << ss.str();
	boost::this_thread::sleep(boost::posix_time::millisec(rand()*delay/RAND_MAX));
}

BOOST_PYTHON_MODULE(TEST1)
{
	bp::def("hello_cpp", hello);
}