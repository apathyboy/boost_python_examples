
#include <cstdlib>
#include <iostream>
#include <string>

#include <boost/python.hpp>

int main(int argc, const char* argv[])
{
    // Step 1: Initialize Python and enable thread support
    //
    // @note: It's important to ensure this is completed in the main thread of the application.
	Py_Initialize();
	PyEval_InitThreads();
	
    // Step 2: Release the GIL from the main thread so that other threads can use it
    //PyEval_ReleaseThread(PyGILState_GetThisThreadState());
    
    // Step 3: Turn over to application processing
    for (;;) {
        std::string cmd;
        std::cin >> cmd;
        
        if (cmd.compare("exit") == 0 || cmd.compare("q") == 0) {
            // Stop the application and join the thread until it's finished.
            std::cout << "Exit command received: " << std::endl;        	
            break;

        } else if(cmd.compare("console") == 0) {
#ifdef WIN32
            std::system("cls");
#else
            std::system("clear");
#endif
            std::cout << "swgpy console 1.0.0" << std::endl;
            PyRun_InteractiveLoop(stdin, "<stdin>");
        } else {
            std::cout << "Invalid command received: " << cmd << "\n";
            std::cout << "Type exit or quit to quit" << std::endl;
        }
    }

    // Step 4: Lock the GIL before calling finalize
    //PyGILState_Ensure();
    Py_Finalize();

	return 0;
}
