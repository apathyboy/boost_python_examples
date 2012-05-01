
#ifndef PYTHON_HELPERS_HPP_
#define PYTHON_HELPERS_HPP_

#include <iostream>
#include <boost/python.hpp>
#include <boost/thread.hpp>

namespace bp = boost::python;

class GilMutex
{
public:
    void lock()
    {
        state_ = PyGILState_Ensure();
    }

    void unlock()
    {
        PyGILState_Release(state_);
    }

private:
    PyGILState_STATE state_;
};

class ScopedGilLock
{
public:
    ScopedGilLock()
    {
        mutex_.lock();
    }

    ~ScopedGilLock()
    {
        mutex_.unlock();
    }

private:
    GilMutex mutex_;
};

struct ScopedGilRelease
{
    PyThreadState* state;

    ScopedGilRelease()
    {
		state = PyEval_SaveThread();
    }

    ~ScopedGilRelease()
    {
		PyEval_RestoreThread(state);
    }
};

class logger {
	boost::recursive_mutex cout_guard;
public:
	template <typename T>
	logger & operator << (const T & data){
		boost::lock_guard<boost::recursive_mutex> lock(cout_guard);
		std::cout << data;
		return *this;
	}
};

void print_py_error() {
    logger safe_cout;
	try {
		PyErr_Print();
		bp::object sys(bp::handle<>(PyImport_ImportModule("sys")));
		bp::object err = sys.attr("stderr");
		std::string err_text = bp::extract<std::string>(err.attr("getvalue")());
		safe_cout << err_text << "\n";
	} catch (...) {
		safe_cout << "Failed to parse python error\n";
	}
	PyErr_Clear();
}

struct PythonDelayedCallback
{
    bp::object callback;
    float delay;

    PythonDelayedCallback(bp::object callback, float delay)
        : callback(callback)
        , delay(delay)
    {}
};

#endif  // PYTHON_HELPERS_HPP_
