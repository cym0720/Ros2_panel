import numpy as np

class SimpleNumpyCalculator:
  __nums_str = ''
  __nums_list = []
  __np_nums = np.array([])
  __result = 0
  
  def reset(self) -> None:
    self.__nums_str = ''
    self.__nums_list = []
    self.__np_nums = np.array([])
    self.__result = 0
  
  def __split_numStr(self) -> None:
    '''
    将带空格的字符串变为numpy数组
    '''
    self.__nums_str = self.__nums_str.strip()
    self.__nums_list = self.__nums_str.split()
    self.__np_nums = np.array(self.__nums_list, dtype=np.float64)

  def __add(self) :
    self.__result = np.sum(self.__np_nums)
    return self.__result
    
  def __multiply(self) :
    self.__result = np.prod(self.__np_nums)
    return self.__result
  
  @staticmethod
  def add ( a, b, c) :
    nums = np.array([a, b, c], dtype=np.float64)
    return float(np.sum(nums))
  
  @staticmethod
  def multiply (a,  b,  c) :
    nums = np.array([a, b, c], dtype=np.float64)
    return float(np.prod(nums))
  
  def run(self) -> None:
    self.reset()
    
    self.__nums_str = input('输入数字(空格分隔): ')
    self.__split_numStr()
    mode = input('输入模式(add/multiply) ')
    while(mode not in ['add','multiply']):
      mode = input('输入错误！重新输入(add/multiply) ')
 
    if mode == 'add':
      print(self.__add())
    elif mode =='multiply':
      print(self.__multiply())

if __name__ == '__main__':
  calc = SimpleNumpyCalculator()
  calc.run()