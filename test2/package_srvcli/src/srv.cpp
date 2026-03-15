#include "rclcpp/rclcpp.hpp"

#include <memory>

#include "../include/calculator.hpp"
#include "tutorial_interfaces/srv/prod.hpp"
#include "tutorial_interfaces/srv/sum.hpp"

class calculator_server : public rclcpp::Node{
  public:
    calculator_server()
    : Node("calculator_server")
    {
      calculator_ = std::make_unique<PyCalculator>();
      RCLCPP_INFO(this->get_logger(), "Calculator server is ready! 1 + 2 +3 = %f", calculator_->add(1, 2, 3));
      prod_service_ = this->create_service<tutorial_interfaces::srv::Prod>(
        "prod", 
        [this](const std::shared_ptr<tutorial_interfaces::srv::Prod::Request> request,
        std::shared_ptr<tutorial_interfaces::srv::Prod::Response> response) {
          RCLCPP_INFO(this->get_logger(), "Received request, %f * %f * %f", request->a, request->b, request->c);
          response->prod = calculator_->multiply(request->a, request->b, request->c);
        });
      sum_service_ = this->create_service<tutorial_interfaces::srv::Sum>(
        "sum", 
        [this](const std::shared_ptr<tutorial_interfaces::srv::Sum::Request> request,
        std::shared_ptr<tutorial_interfaces::srv::Sum::Response> response) {
          RCLCPP_INFO(this->get_logger(), "Received request, %f + %f + %f", request->a, request->b, request->c);
          response->sum = calculator_->add(request->a, request->b, request->c);
        });
      RCLCPP_INFO(this->get_logger(), "Calculator server is ready!");
    };

    private:
      std::unique_ptr<PyCalculator> calculator_;
      rclcpp::Service<tutorial_interfaces::srv::Prod>::SharedPtr prod_service_;
      rclcpp::Service<tutorial_interfaces::srv::Sum>::SharedPtr sum_service_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<calculator_server>();
  rclcpp::spin(node);
  rclcpp::shutdown();
}