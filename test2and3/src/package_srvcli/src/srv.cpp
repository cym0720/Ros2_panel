#include "rclcpp/rclcpp.hpp"

#include <memory>
#include <exception>

#include "../include/calculator.hpp"
#include "tutorial_interfaces/srv/prod.hpp"
#include "tutorial_interfaces/srv/sum.hpp"

class calculator_server : public rclcpp::Node {
public:
  calculator_server()
  : Node("calculator_server")
  {
    calculator_ = std::make_unique<PyCalculator>();
    RCLCPP_INFO(this->get_logger(), "Calculator init ok: 1 + 2 + 3 = %f",
                calculator_->add(1, 2, 3));

    prod_service_ = this->create_service<tutorial_interfaces::srv::Prod>(
      "prod",
      [this](
        const std::shared_ptr<tutorial_interfaces::srv::Prod::Request> request,
        std::shared_ptr<tutorial_interfaces::srv::Prod::Response> response) {
        try {
          RCLCPP_INFO(this->get_logger(), "Received prod request: %f * %f * %f",
                      request->a, request->b, request->c);
          response->prod = calculator_->multiply(request->a, request->b, request->c);
          RCLCPP_INFO(this->get_logger(), "Send prod response: %f", response->prod);
        } catch (const std::exception &e) {
          RCLCPP_ERROR(this->get_logger(), "Prod service failed: %s", e.what());
          response->prod = 0.0;
        }
      });

    RCLCPP_INFO(this->get_logger(), "prod service created");

    sum_service_ = this->create_service<tutorial_interfaces::srv::Sum>(
      "sum",
      [this](
        const std::shared_ptr<tutorial_interfaces::srv::Sum::Request> request,
        std::shared_ptr<tutorial_interfaces::srv::Sum::Response> response) {
        try {
          RCLCPP_INFO(this->get_logger(), "Received sum request: %f + %f + %f",
                      request->a, request->b, request->c);
          response->sum = calculator_->add(request->a, request->b, request->c);
          RCLCPP_INFO(this->get_logger(), "Send sum response: %f", response->sum);
        } catch (const std::exception &e) {
          RCLCPP_ERROR(this->get_logger(), "Sum service failed: %s", e.what());
          response->sum = 0.0;
        }
      });

    RCLCPP_INFO(this->get_logger(), "sum service created");
    RCLCPP_INFO(this->get_logger(), "Calculator server is ready!");
  }

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
  return 0;
}