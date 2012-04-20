
#include <iostream>
#include <boost/python.hpp>
#include <boost/thread.hpp>
#include "python_helpers.hpp"

#ifdef WIN32
#define MAIN wmain
typedef wchar_t unicode_char;
#else
#define MAIN main
typedef char unicode_char;
#endif

namespace bp = boost::python;

static int delay = 100;
static int thread_count = 100;
static int thread_loops = 10;

void call_python(bp::dict &localDict, int id) {
    logger safe_cout;

	try {
		aquire_py_GIL lock;
		try	{
			bp::object scriptFunction = bp::extract<bp::object>(localDict["hello_python"]);
			if(scriptFunction)
				scriptFunction(id);
			else
				safe_cout << "Script did not have a hello function!\n";
		} catch(const bp::error_already_set& /* e */) {
			safe_cout << "Exception in script: ";
			print_py_error();
		}
	} catch(const std::exception &e) {
		safe_cout << "Exception in script: " << e.what() << "\n";
	}
}

void thread_proc(const int id, bp::dict localDict) {
    logger safe_cout;
	for (int i=0;i<thread_loops;i++) {
		boost::posix_time::millisec time_to_sleep(rand()*delay/RAND_MAX);
		std::stringstream ss;
		ss << ">>> proc: " << id << "\n";
		safe_cout << ss.str();
		boost::this_thread::sleep(time_to_sleep);
		call_python(localDict, id);
	}
}  

int MAIN(int argc, const unicode_char* argv[]) {
	Py_Initialize();
	PyEval_InitThreads();
        
    logger safe_cout;
	
    try	{
		bp::object main_module = bp::import("__main__");
		bp::dict globalDict = bp::extract<bp::dict>(main_module.attr("__dict__"));
		bp::dict localDict = globalDict.copy();

		bp::object ignored = bp::exec(
			"from TEST1 import hello_cpp\n"
			"\n"
			"def hello_python(id):\n"
			"	hello_cpp(id)\n"
			"\n"
			, localDict, localDict);

		PyThreadState *state = PyEval_SaveThread();

		boost::thread_group threads;
		for (int i=0;i<thread_count;i++)
			threads.create_thread(boost::bind(&thread_proc, i, localDict));
		safe_cout << ":::main: waiting for threads to join\n";
		threads.join_all();  

	} catch(const std::exception &e) {
		safe_cout << "Exception in script: " << e.what() << "\n";
	} catch(const bp::error_already_set& /* e */) {
		safe_cout << "Exception in script: ";
		print_py_error();
	}
}
