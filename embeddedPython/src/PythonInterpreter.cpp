#include <PythonInterpreter.h>

PyObject *PythonInterpreter::pModule = NULL;
PyObject *PythonInterpreter::pFunc = NULL;

PythonInterpreter *
PythonInterpreter::getInstance()
{
    try
    {
        static PythonInterpreter instance; // Guaranteed to be destroyed, and instantiated on first use.
        return &instance;
    }
    catch (std::string msg)
    {
        PyErr_Print();
        fprintf(stderr, msg.c_str());
        // Py_XDECREF(PythonInterpreter::pFunc);
        // Py_XDECREF(PythonInterpreter::pModule);
    }
    return NULL;
}

// this should be the private one!
PythonInterpreter::PythonInterpreter()
{
    Py_Initialize();

    std::wstring ws(Py_GetPath());
    std::string pythonModules = ":/home/zacfilan/repos/embeddedPython/test";
    std::wstring pm(pythonModules.begin(), pythonModules.end());
    ws += pm;
    PySys_SetPath(ws.c_str());

    bindModule("concat");
    bindFunction("concat");
}

/**
 * @brief Bind the omdule name to pModule
 *
 * @param name the module name
 */
void PythonInterpreter::bindModule(std::string name)
{
    PyObject *pName = PyUnicode_DecodeFSDefault(name.c_str());
    /* Error checking of pName left out */

    PythonInterpreter::pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    if (PythonInterpreter::pModule == NULL)
    {
        throw "Failed to load " + name;
    }
}

/**
 * @brief Bind the python function (in the already bound module)
 * to pFunc
 *
 * @param name
 */
void PythonInterpreter::bindFunction(std::string name)
{
    PythonInterpreter::pFunc = PyObject_GetAttrString(PythonInterpreter::pModule, name.c_str());
    /* pFunc is a new reference */

    if (!(PythonInterpreter::pFunc && PyCallable_Check(PythonInterpreter::pFunc)))
    {
        if (PyErr_Occurred())
            throw "Cannot find function " + name;
    }
}

/**
 * @brief Call this bound function
 *
 * @param in
 * @param out
 */
void PythonInterpreter::doit(const char *in1, const char *in2)
{
    PyObject *pArgs = Py_BuildValue("ss", in1, in2);
    if (pArgs == NULL)
    {
        throw new std::string("unable to convert c-arguments to python arguments");
    }
    PyObject *pValue = PyObject_CallObject(PythonInterpreter::pFunc, pArgs);
    Py_DECREF(pArgs);

    if (pValue == NULL)
    {
        PyErr_Print();
        return; // throw std::string("Call failed");
    }
    char *result;
    PyObject *t = PyTuple_New(1);
    PyTuple_SetItem(t, 0, pValue);
    if (!PyArg_ParseTuple(t, "s", &result))
    {
        PyErr_Print();
        fprintf(stderr, "cannot convert return value");
    }
    printf("Result of call: %s\n", result);
    Py_DECREF(pValue);
    Py_DECREF(t);
}
