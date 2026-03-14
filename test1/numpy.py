import os
import numpy as np

class NumPyCalculator :
  __mode = ""
  __result = 0
  __nums_str = []
  __nums_str = []
  __nums_int = []
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
    self.__nums_int = []
    self.__nums_decimal = []
    self.__max_decimal_len = 0
    self.__sum_decimal_total = 0

  def __get_carry(self) :
    """
    得到小数到整数的进位
    """
    __nums_int = np.array([], dtype=object)    
    __nums_decimal = np.array([], dtype=object)
    
  def __get_carry(self) :
    """
    得到小数到整数的进位
    """
    return self.__sum_decimal_total  // 10**self.__max_decimal_len
  
  def __split_numStr(self) :
    """
    将字符串形式中的每个数字分割成整数部分和小数部分
    不一样的是还要转np向量
    """

    self.__nums_int = np.array([], dtype=object)
    self.__nums_decimal = np.array([], dtype=object)
    
    nums = self.__nums_str.split()
    
    for n_str in nums :
      if '.' in n_str :
        int_part, dec_part = n_str.split('.', 1)
        self.__nums_int.append(int(int_part))
        
        dec_part_stripped = dec_part.rstrip('0')
        self.__max_decimal_len = max(self.__max_decimal_len, len(dec_part_stripped))
        if n_str.startswith('-'):
          dec_part_final = '-' + dec_part_stripped
        else:
          dec_part_final = dec_part_stripped
        self.__nums_decimal.append(dec_part_final)
      else :
        int_num = int(n_str)
        self.__nums_int.append(int_num)
        if int_num < 0:
          self.__nums_decimal.append('-')
        else:
          self.__nums_decimal.append('')

    #补齐小数位数
    for i in range(len(self.__nums_decimal)) :
      dec_part = self.__nums_decimal[i]
      if dec_part.startswith('-'):
        # 带负号：去掉负号→补0→加回负号
        num_part = dec_part.lstrip('-')
        num_part = num_part.ljust(self.__max_decimal_len, '0')
        self.__nums_decimal[i] = '-' + num_part
      else :
        self.__nums_decimal[i] = dec_part.ljust(self.__max_decimal_len, '0')
        
    
    

input_str = input("请输入需要处理的数据，用空格分隔：")
nums = list(map(float, input_str.split()))
mode = input("输入处理数据模式（add/multply）")
while(mode not in {"add", "multply"}) :
  mode = input ("输入错误,重新输入模式")

