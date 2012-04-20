
#ifndef PYTHON_HELPERS_HPP_
#define PYTHON_HELPERS_HPP_

#include <iostream>
#include <boost/python.hpp>
#include <boost/thread.hpp>

namespace bp = boost::python;

struct aquire_py_GIL {
	PyGILState_STATE state;
	aquire_py_GIL() {
		state = PyGILState_Ensure();
	}

	~aquire_py_GIL() {
		PyGILState_Release(state);
	}
};

struct release_py_GIL {
	PyThreadState *state;
	release_py_GIL() {
		state = PyEval_SaveThread();
	}
	~release_py_GIL() {
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

#endif  // PYTHON_HELPERS_HPP_
