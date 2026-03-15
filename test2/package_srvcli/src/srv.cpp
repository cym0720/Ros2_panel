#include "rclcpp/rclcpp.hpp"

#include <memory>

#include "../include/calculator.hpp"
#include "tutorial_interfaces/srv/prod.hpp"
#include "tutorial_interfaces/srv/sum.hpp"

class caculator_server : public rclcpp::Node{
  public:
    caculator_server()
    : Node("caculator_server")
    {
      std::unique_ptr<PyCalculator> calculator = std::make_unique<PyCalculator>();
      auto add_Three_func = [&calculator](int a, int b, int c) {
        return calculator->add(a, b, c);
      };

      auto multiply_Three_func = [&calculator](int a, int b, int c) {
        return calculator->multiply(a, b, c);
      };

      rclcpp::Service<tutorial_interfaces::srv::Prod>::SharedPtr prod_service =
        this->create_service<tutorial_interfaces::srv::Prod>("prod", &multiply_Three_func);

      rclcpp::Service<tutorial_interfaces::srv::Sum>::SharedPtr sum_service =
        this->create_service<tutorial_interfaces::srv::Sum>("sum", &add_Three_func);
    }
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<caculator_server>();
  rclcpp::spin(node);
  rclcpp::shutdown();
}