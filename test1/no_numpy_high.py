import os 

# 定义高精度计算器，使用高精度加法与乘法防止越界
class HighPreCalculator :
    def sum(self, nums) :
      sum = 0.0
      for n in nums :
        sum += n
      return sum
    
    def mutiply(self, nums) :
      result = 0.0
      for n in nums :
        result *= n
      return result

calculate_core = HighPreCalculator()

input_str = input("请输入需要处理的数据，用空格分隔：")
nums = list(map(float, input_str.split()))
mode = input("输入处理数据模式（add/multply）")
while(mode not in {"add", "multply"}) :
  mode = input ("输入错误,重新输入模式")

if mode == "add" :
  print(f"求和结果：{calculate_core.sum(nums)}")
else :
  print(f"求积结果：{calculate_core.mutiply(nums)}")
