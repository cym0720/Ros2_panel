#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/srv/prod.hpp"
#include "tutorial_interfaces/srv/sum.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

class node_cli : public rclcpp::Node {
  public:
    node_cli()
    : Node("node_cli")
    {
      start_time_ = std::chrono::steady_clock::now();
      sum_client_ = this->create_client<tutorial_interfaces::srv::Sum>("sum_two_numbers");
      prod_client_ = this->create_client<tutorial_interfaces::srv::Prod>("product_three_numbers");
      while (!prod_client_->wait_for_service(1s)) {
        if (!rclcpp::ok()) {
          RCLCPP_ERROR(this->get_logger(), "Interrupted while waiting for the service. Exiting.");
          return;
        }
        RCLCPP_INFO(this->get_logger(), "service not available, waiting again...");
      }
    }

    void send_srv() {
      auto now_time = (std::chrono::steady_clock::now() - start_time_).count();
      if (now_time % 2 == 0) {
        auto request = std::make_shared<tutorial_interfaces::srv::Sum::Request>();
        request->a = now_time;
        request->b = now_time + 1;
        request->c = now_time + 2;
        auto future = sum_client_->async_send_request(request);
        future.wait();
        if (future.get()->sum == request->a + request->b + request->c) {
          RCLCPP_INFO(this->get_logger(), "Sum service call successful,a: %ld, b: %ld, c: %ld, result: %ld");
        } else {
          RCLCPP_ERROR(this->get_logger(), "Sum service call failed");
        }
      } else {
        auto request = std::make_shared<tutorial_interfaces::srv::Prod::Request>();
        request->a = now_time;
        request->b = now_time + 1;
        request->c = now_time + 2;
        auto future = prod_client_->async_send_request(request);
        future.wait();
        if (future.get()->product == request->a * request->b * request->c) {
          RCLCPP_INFO(this->get_logger(), "Product service call successful, a: %ld, b: %ld, c: %ld, result: %ld");
        } else {
          RCLCPP_ERROR(this->get_logger(), "Product service call failed");
        }
      }
      
      
    }
  private:
    rclcpp::Client<tutorial_interfaces::srv::Prod>::SharedPtr prod_client_;
    rclcpp::Client<tutorial_interfaces::srv::Sum>::SharedPtr sum_client_;
    std::chrono::steady_clock::time_point start_time_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<node_cli>();
  rclcpp::shutdown();
  return 0;
}