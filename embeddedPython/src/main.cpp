#include <PythonInterpreter.h>

int main(int argc, char *argv[])
{
    auto pythonInterpreter = PythonInterpreter::getInstance();
    if (pythonInterpreter != NULL)
    {
        pythonInterpreter->doit("tic", "tok"); // fix these, who owns the memory?
    }

    return 0;
}