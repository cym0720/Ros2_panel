import os 
import string

class HighPreCalculator :
  __mode = ""
  __carry = 0
  __carry_back = 0
  __result  = 0
  __nums_str = []
  __nums_int = []
  __nums_decimal = []
  __max_decimal_len = 0
  __sum_decimal_total = 0 
  
  def __reset (self) :
    self.__mode = ""
    self.__carry = 0
    self.__carry_back = 0
    self.__result  = 0
    self.__nums_str = []
    self.__nums_int = []
    self.__nums_decimal = []
    self.__max_decimal_len = 0
    self.__sum_decimal_total = 0

  def __get_carry(self) :
    """
    得到小数到整数的进位
    """
    return self.__sum_decimal_total  // 10**self.__max_decimal_len

  def __sum_int(self, nums) :
    """
    整数加和
    """
    return sum(nums)
  
  def __multiply_int(self, nums) :
    """
    整数乘积
    """
    result = 1
    for n in nums :
      result *= n                                                                                                 
    return result

  def __split_numStr(self) :
    """
    将字符串形式中的每个数字分割成整数部分和小数部分
    TODO 注意小数部分最后要全部补齐为最高小数位数
    """
    self.__nums_int.clear()
    self.__nums_decimal.clear()
    
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
  
  def __add(self) :
    """
    整数加法
    """
    sum_int = self.__sum_int(self.__nums_int)
    self.__sum_decimal_total = sum([int(d) 
                                    if d.strip('-') else 0 
                                    for d in self.__nums_decimal])

    carry = self.__get_carry()
    sum_int += carry
    sum_decimal = self.__sum_decimal_total % 10**self.__max_decimal_len

    # 处理整数与小数位正负号不同的情况
    if (sum_decimal > 0 and sum_int < 0) or (sum_decimal < 0 and sum_int > 0) :
      sum_int -= 1
      sum_decimal = str(10**self.__max_decimal_len - abs(sum_decimal)).rjust(self.__max_decimal_len, '0')

      self.__result = str(sum_int) + '.' + sum_decimal
    else:
      if self.__max_decimal_len == 0:
        self.__result = sum_int
        return
      sum_decimal_str = str(sum_decimal).rjust(self.__max_decimal_len, '0').rstrip('0')
      if sum_decimal_str:
        self.__result = f"{sum_int}.{sum_decimal_str}"
      else:
        self.__result = sum_int
    
  def __multiply(self):
    """
    整数乘法
    TODO 注意小数部分乘法,没有进位，只有退位了
    """
    full_ints = []
    
    for n_int, n_decimal in zip (self.__nums_int, self.__nums_decimal) :
      #先把小数和整数位拼成正整数
      abs_int_str = str(abs(n_int))
      abs_dec_str = n_decimal.lstrip('-')
      full_str = abs_int_str + abs_dec_str
      full_int = int(full_str)
      
      #恢复负号
      if n_int < 0 or n_decimal.startswith('-'):
        full_int = -full_int
      full_ints.append(full_int)
      
    product_full = self.__multiply_int(full_ints)
    
    total_dec_len = len(self.__nums_decimal) * self.__max_decimal_len
    product_str = str(product_full)
    
    #处理最后的符号和退位
    sign = "-" if product_str.startswith('-') else ""
    product_str = product_str.lstrip('-')
    
    if total_dec_len == 0:
      self.__result = f"{sign}{product_str}"
      return
    
    if len(product_str) <= total_dec_len:
        int_part = "0"
        dec_part = product_str.rjust(total_dec_len, '0')
    else:
        int_part = product_str[:-total_dec_len]
        dec_part = product_str[-total_dec_len:]
    
    dec_part = dec_part.rstrip('0')
    if dec_part:
        self.__result = f"{sign}{int_part}.{dec_part}"
    else:
        self.__result = f"{sign}{int_part}"
    
  def run(self) :
    """
    输入数据
    """
    self.__reset()
    self.__nums_str = input("请输入需要处理的数据，用空格分隔：")
    self.__mode     = input("输入处理数据模式（add/multply）")
    while(self.__mode not in {"add", "multply"}):
      self.__mode = input("输入错误,重新输入模式")
  
    self.__split_numStr()
    if self.__mode == "add" :
      self.__add()
    else :
      self.__multiply()

    if self.__mode == "add":
      print(f"求和结果：{self.__result}")
    else:
      print(f"求积结果：{self.__result}")
    
if __name__ == '__main__':
  calculator = HighPreCalculator()
  while(1) :
    calculator.run()
    

