import os 

class Calculator :
    def sum(self, nums) :
      sum = 0.0
      for n in nums :
        sum += n
      return sum
    
    def multiply(self, nums) :
      result = 1.0
      for n in nums :
        result *= n
      return result

calculate_core = Calculator()

input_str = input("请输入需要处理的数据，用空格分隔：")
nums = list(map(float, input_str.split()))
mode = input("输入处理数据模式（add/multply）")
while(mode not in {"add", "multply"}) :
  mode = input ("输入错误,重新输入模式")

if mode == "add" :
  print(f"求和结果：{calculate_core.sum(nums)}")
else :
  print(f"求积结果：{calculate_core.multiply(nums)}")
