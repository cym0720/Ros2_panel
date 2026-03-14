import os
import numpy as np

class NumPyCalculator :
  __mode = ""
  __result = 0
  __nums_str = []
  __max_decimal_len = 0
  __sum_decimal_total = 0
  
  #python原生支持大整数，NB
  __nums_int = np.array([], dtype=object)    # 存储每个数字的整数部分（向量）
  __nums_decimal = np.array([], dtype=object)# 存储每个数字的小数部分（向量）
  
  def __init__(self) :
    self.__reset()

  def __reset(self) :
    self.__mode = ""
    self.__result = 0
    self.__nums_str = []
    self.__max_decimal_len = 0
    self.__sum_decimal_total = 0

    __nums_int = np.array([], dtype=object)    
    __nums_decimal = np.array([], dtype=object)
    
  def __get_carry(self) :
    """
    得到小数到整数的进位
    """
    return self.__sum_decimal_total  // 10**self.__max_decimal_len

input_str = input("请输入需要处理的数据，用空格分隔：")
nums = list(map(float, input_str.split()))
mode = input("输入处理数据模式（add/multply）")
while(mode not in {"add", "multply"}) :
  mode = input ("输入错误,重新输入模式")

