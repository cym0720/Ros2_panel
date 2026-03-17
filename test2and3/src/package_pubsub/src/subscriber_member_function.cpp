// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("minimal_subscriber"), zero_time_(0)
  {
    subscription_ = this->create_subscription<std_msgs::msg::String>(
      "counter_info", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const std_msgs::msg::String & msg)
  {
    std::string msg_str = msg.data;
    if (is_first_time_)
    {
      is_first_time_ = false;
      RCLCPP_INFO(this->get_logger(), "接收到消息：%s", msg_str.c_str());
    }
    else if (msg_str == "0")
    {
      zero_time_++;
      RCLCPP_INFO(this->get_logger(), "嘿！我已经被清空%s次了！", std::to_string(zero_time_).c_str());
    }
    else {
      RCLCPP_INFO(this->get_logger(), "接收到消息：%s", msg_str.c_str());
    }
  }
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
  size_t zero_time_;
  bool is_first_time_ = true;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
