#include <python3.10/Python.h>
#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

class PyCalculator {
  private:
    PyObject* pModule = nullptr;
    PyObject* pClass = nullptr;
    // PyObject* pInstance = nullptr;
    PyObject* pFunc_add = nullptr;
    PyObject* pFunc_multiply = nullptr;

    float callStaticMethod(PyObject* pFunc, int a, int b, int c) {
      if (!pFunc) {
        throw std::runtime_error("Python function is null");
      }

      PyGILState_STATE gstate = PyGILState_Ensure();
      
      PyObject* pArgs = PyTuple_New(3);
      PyTuple_SetItem(pArgs, 0, PyLong_FromLong(a));
      PyTuple_SetItem(pArgs, 1, PyLong_FromLong(b));
      PyTuple_SetItem(pArgs, 2, PyLong_FromLong(c));

      PyObject* pResult = PyObject_CallObject(pFunc, pArgs);
      Py_DECREF(pArgs);

      if (!pResult) {
        std::cerr << "[错误] 调用 Python 方法失败" << std::endl;
        PyErr_Print();  // 打印 Python 错误堆栈
        // Py_Finalize();
        PyGILState_Release(gstate);
        throw std::runtime_error("Calling Python method failed");
        // exit(EXIT_FAILURE);
      }

      float result = PyFloat_AsDouble(pResult);
      Py_DECREF(pResult);

      PyGILState_Release(gstate);
      return result;
    }

  public:
    PyCalculator() {
      Py_Initialize();
      PyEval_InitThreads();
      if(!Py_IsInitialized()){
		    throw std::runtime_error("Python 初始化失败");
	    }

      PyRun_SimpleString("import sys");
      PyRun_SimpleString("sys.path.append('/home/cym/intership_test/test1/')");
      PyGILState_STATE gstate = PyGILState_Ensure(); // 加锁

      // PyRun_SimpleString("import numpy_high");
      pModule = PyImport_ImportModule("numpy_high");
      if (!pModule) {
        std::cerr << "[错误] 无法导入 Python 模块：numpy_high" << std::endl;
        PyErr_Print();  // 打印 Python 错误堆栈，方便调试
        PyGILState_Release(gstate);
        throw std::runtime_error("Importing Python module failed");
        
        // exit(EXIT_FAILURE);
      }

      pClass = PyObject_GetAttrString(pModule, "SimpleNumpyCalculator");
      if (!pClass) {
        std::cerr << "[错误] 无法获取 Python 类：SimpleNumpyCalculator" << std::endl;
        PyErr_Print();  // 打印 Python 错误堆栈，方便调试
        PyGILState_Release(gstate);
        throw std::runtime_error("Getting Python class failed");
        // exit(EXIT_FAILURE);
      }

      pFunc_add = PyObject_GetAttrString(pClass, "add");
      if (!pFunc_add || !PyCallable_Check(pFunc_add)) {
        std::cerr << "[错误] 无法获取 Python 方法：add" << std::endl;
        PyErr_Print();  // 打印 Python 错误堆栈，方便调试
        PyGILState_Release(gstate);
        throw std::runtime_error("Getting Python method failed");
      }

      pFunc_multiply = PyObject_GetAttrString(pClass, "multiply");
      if (!pFunc_multiply || !PyCallable_Check(pFunc_multiply)) {
        std::cerr << "[错误] 无法获取 Python 方法：multiply" << std::endl;
        PyErr_Print();  // 打印 Python 错误堆栈，方便调试
        PyGILState_Release(gstate);
        throw std::runtime_error("Getting Python method failed");
      }

      PyGILState_Release(gstate);

      // PyEval_SaveThread();
    }

    ~PyCalculator() {
      PyGILState_STATE gstate = PyGILState_Ensure();

      if (pFunc_add) Py_DECREF(pFunc_add);
      if (pFunc_multiply) Py_DECREF(pFunc_multiply);
      if (pClass) Py_DECREF(pClass);
      if (pModule) Py_DECREF(pModule);

      PyGILState_Release(gstate);
    }

    float add(int a, int b, int c) {
      return callStaticMethod(pFunc_add, a, b, c);
    };

    float multiply(int a, int b, int c) {
      return callStaticMethod(pFunc_multiply, a, b, c);
    };
};

