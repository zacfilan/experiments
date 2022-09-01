#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <string>
/**
 * @brief A cpp wrapper class around the python interpreter
 *
 */
class PythonInterpreter
{
public:
    static PythonInterpreter *getInstance();
    static void doit(const char *a, const char *b);

private:
    PythonInterpreter(); // Constructor? (the {} brackets) are needed here.
    static void bindModule(std::string moduleName);
    static void bindFunction(std::string name);
    static PyObject *pModule, *pFunc;

public:
    PythonInterpreter(PythonInterpreter const &) = delete;
    void operator=(PythonInterpreter const &) = delete;
};
