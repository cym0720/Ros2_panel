#include <python3.10/Python.h>
#include <iostream>
#include <string>
#include <memory>

class PyCalculator {
  private:
    PyObject* pModule = nullptr;
    PyObject* pClass = nullptr;
    PyObject* pInstance = nullptr;
    PyObject* pFunc_add = nullptr;
    PyObject* pFunc_multiply = nullptr;

    float callStaticMethod(PyObject* pFunc, int a, int b, int c) {
      if (!pFunc) return 0;

      PyObject* pArgs = PyTuple_New(3);
      PyTuple_SetItem(pArgs, 0, PyLong_FromLong(a));
      PyTuple_SetItem(pArgs, 1, PyLong_FromLong(b));
      PyTuple_SetItem(pArgs, 2, PyLong_FromLong(c));

      PyObject* pResult = PyObject_CallObject(pFunc, pArgs);
      if (!pResult) {
        std::cerr << "[错误] 调用 Python 方法失败" << std::endl;
        PyErr_Print();  // 打印 Python 错误堆栈
        Py_Finalize();
        exit(EXIT_FAILURE);
      }

      float result = PyFloat_AsDouble(pResult);
      Py_DECREF(pResult);
      return result;
    }

  public:
    PyCalculator() {
      Py_Initialize();
      if(!Py_IsInitialized()){
		    std::cout << "python init fail" << std::endl;
        exit(1);
	    }

      PyRun_SimpleString("import sys");
      PyRun_SimpleString("sys.path.append('/home/cym/intership_test/test1/')");
      PyRun_SimpleString("import numpy_high");
      pModule = PyImport_ImportModule("numpy_high");
      if (!pModule) {
        std::cerr << "[错误] 无法导入 Python 模块：numpy" << std::endl;
        PyErr_Print();  // 打印 Python 错误堆栈，方便调试
        Py_Finalize();
        exit(EXIT_FAILURE);
      }

      pClass = PyObject_GetAttrString(pModule, "SimpleNumpyCalculator");
      if (!pClass) {
        std::cerr << "[错误] 无法获取 Python 类：SimpleNumpyCalculator" << std::endl;
        PyErr_Print();  // 打印 Python 错误堆栈，方便调试
        Py_Finalize();
        exit(EXIT_FAILURE);
      }

      pFunc_add = PyObject_GetAttrString(pClass, "add");
      if (!pFunc_add) {
        std::cerr << "[错误] 无法获取 Python 方法：add" << std::endl;
        PyErr_Print();  // 打印 Python 错误堆栈，方便调试
        Py_Finalize();
        exit(EXIT_FAILURE);
      }

      pFunc_multiply = PyObject_GetAttrString(pClass, "multiply");
      if (!pFunc_multiply) {
        std::cerr << "[错误] 无法获取 Python 方法：multiply" << std::endl;
        PyErr_Print();  // 打印 Python 错误堆栈，方便调试
        Py_Finalize();
        exit(EXIT_FAILURE);
      }
    }
    
    ~PyCalculator() {
      Py_DECREF(pModule);
      Py_DECREF(pClass);
      Py_DECREF(pInstance);
      Py_DECREF(pFunc_add);
      Py_DECREF(pFunc_multiply);
      Py_Finalize();
    }

    float add(int a, int b, int c) {
      return callStaticMethod(pFunc_add, a, b, c);
    };

    float multiply(int a, int b, int c) {
      return callStaticMethod(pFunc_multiply, a, b, c);
    };
};

