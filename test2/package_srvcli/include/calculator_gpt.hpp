#pragma once

#include <python3.10/Python.h>
#include <iostream>
#include <string>

class PyCalculator {
private:
    PyObject* pModule = nullptr;
    PyObject* pClass = nullptr;
    PyObject* pInstance = nullptr;
    PyObject* pFunc_add = nullptr;
    PyObject* pFunc_multiply = nullptr;

    float callMethod(PyObject* func, int a, int b, int c)
    {
        if (!func) return 0;

        PyGILState_STATE gstate = PyGILState_Ensure();

        PyObject* args = PyTuple_New(3);
        PyTuple_SetItem(args,0,PyLong_FromLong(a));
        PyTuple_SetItem(args,1,PyLong_FromLong(b));
        PyTuple_SetItem(args,2,PyLong_FromLong(c));

        PyObject* result = PyObject_CallObject(func,args);

        if(!result)
        {
            PyErr_Print();
            PyGILState_Release(gstate);
            throw std::runtime_error("python call failed");
        }

        float value = PyFloat_AsDouble(result);

        Py_DECREF(result);
        Py_DECREF(args);

        PyGILState_Release(gstate);

        return value;
    }

public:

    PyCalculator()
    {
        Py_Initialize();

        if(!Py_IsInitialized())
        {
            throw std::runtime_error("Python init failed");
        }

        PyEval_InitThreads();

        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append('/home/cym/intership_test/test1/')");

        PyGILState_STATE gstate = PyGILState_Ensure();

        pModule = PyImport_ImportModule("numpy_high");

        if(!pModule)
        {
            PyErr_Print();
            throw std::runtime_error("import module failed");
        }

        pClass = PyObject_GetAttrString(pModule,"SimpleNumpyCalculator");

        if(!pClass)
        {
            PyErr_Print();
            throw std::runtime_error("get class failed");
        }

        pInstance = PyObject_CallObject(pClass,nullptr);

        if(!pInstance)
        {
            PyErr_Print();
            throw std::runtime_error("create instance failed");
        }

        pFunc_add = PyObject_GetAttrString(pInstance,"add");
        pFunc_multiply = PyObject_GetAttrString(pInstance,"multiply");

        PyGILState_Release(gstate);

        /* 释放 GIL 给 ROS2 executor */
        PyEval_SaveThread();
    }

    ~PyCalculator()
    {
        PyGILState_STATE gstate = PyGILState_Ensure();

        if(pFunc_add) Py_DECREF(pFunc_add);
        if(pFunc_multiply) Py_DECREF(pFunc_multiply);
        if(pInstance) Py_DECREF(pInstance);
        if(pClass) Py_DECREF(pClass);
        if(pModule) Py_DECREF(pModule);

        PyGILState_Release(gstate);

        Py_Finalize();
    }

    float add(int a,int b,int c)
    {
        return callMethod(pFunc_add,a,b,c);
    }

    float multiply(int a,int b,int c)
    {
        return callMethod(pFunc_multiply,a,b,c);
    }
};