
#include <iostream>
#include <mutex>

#include <boost/python.hpp>
#include <boost/thread.hpp>
#include "python_helpers.hpp"

namespace bp = boost::python;

logger safe_cout;

void CallCommandFunc(int i)
{
    // Aquire the GIL lock before any calls to the python api
    ScopedGilLock gil;

    try
    {
        bp::object command1 = bp::import("command1");
        bp::object test_class = command1.attr("TestClass")();
        bp::object result = test_class.attr("TestFunc")();

        if (result != NULL)
        {
            std::string str_val = bp::extract<std::string>(result);
            safe_cout << str_val << " from thread: " << i << "\n";
        }
    }
    catch(const bp::error_already_set& /*e*/)
    {
        print_py_error();
    }
    catch(const std::exception& e)
    {
        safe_cout << e.what();
    }
    catch(...)
    {
        safe_cout << "Unknown exception thrown";
    }
}

int main(int argc, const char* argv[])
{
    // Step 1: Initialize Python and enable thread support
    //
    // @note: It's important to ensure this is completed in the main thread of the application.
	Py_Initialize();
	PyEval_InitThreads();
	
    // Step 2: Release the GIL from the main thread so that other threads can use it
    PyEval_ReleaseThread(PyGILState_GetThisThreadState());
    
    // Step 3: Turn over to application processing
    boost::thread_group threads;
    for (int i = 0; i < 100; ++i)
    {
        threads.create_thread(std::bind(CallCommandFunc, i));
    }

    threads.join_all();
    
    // Step 4: Lock the GIL before calling finalize
    PyGILState_Ensure();
    Py_Finalize();

	return 0;
}
