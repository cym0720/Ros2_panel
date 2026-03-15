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
      sum_client_ = this->create_client<tutorial_interfaces::srv::Sum>("sum");
      prod_client_ = this->create_client<tutorial_interfaces::srv::Prod>("prod");
      timer_ = this->create_wall_timer(
      1500ms,
      std::bind(&node_cli::send_srv, this)
    );
    }

    void send_srv() {
      auto now_time = std::chrono::duration_cast<std::chrono::seconds>
                        (std::chrono::steady_clock::now() - start_time_).count();
      
      // 偶数就调用和，奇数就调用求积
      if (now_time % 2 == 0) {
        auto request = std::make_shared<tutorial_interfaces::srv::Sum::Request>();
        request->a = now_time;
        request->b = now_time + 1;
        request->c = now_time + 2;
        // auto future = sum_client_->async_send_request(request);
        // if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), future, 3s) != 
        //   rclcpp::FutureReturnCode::SUCCESS) {
        //   RCLCPP_ERROR(this->get_logger(), "Sum service call timeout!");
        //   return;
        // }

        if (!sum_client_->wait_for_service(1s)) {
          RCLCPP_WARN(this->get_logger(), "Sum service not available");
          return;
        }
        sum_client_->async_send_request(
          request,
          [this,request](rclcpp::Client<tutorial_interfaces::srv::Sum>::SharedFuture future) {
          auto response = future.get();
          RCLCPP_INFO(this->get_logger(), "sum result = %f", response->sum);
          if (response->sum == request->a + request->b + request->c) {
            RCLCPP_INFO(this->get_logger(), "Sum service call successful,a: %f, b: %f, c: %f, result: %f", request->a, request->b, request->c, response->sum);
          } else {
            RCLCPP_ERROR(this->get_logger(), "Sum service call failed");
          }
          
      });
      } 
      else {
        auto request = std::make_shared<tutorial_interfaces::srv::Prod::Request>();
        request->a = now_time;
        request->b = now_time + 1;
        request->c = now_time + 2;
        
        if (!prod_client_->wait_for_service(1s)) {
          RCLCPP_WARN(this->get_logger(), "Product service not available");
          return;
        }
        prod_client_->async_send_request(
          request,
          [this, request](rclcpp::Client<tutorial_interfaces::srv::Prod>::SharedFuture future) {
          auto response = future.get();
          RCLCPP_INFO(this->get_logger(), "prod result = %f", response->prod);
          if (response->prod == request->a * request->b * request->c) {
            RCLCPP_INFO(this->get_logger(), 
                        "Product service call successful, a: %f, b: %f, c: %f, result: %f", 
                        request->a, request->b, request->c, response->prod);
          } else {
            RCLCPP_ERROR(this->get_logger(), "Product service call failed");
          }
          });
      }
    }
  private:
    rclcpp::Client<tutorial_interfaces::srv::Prod>::SharedPtr prod_client_;
    rclcpp::Client<tutorial_interfaces::srv::Sum>::SharedPtr sum_client_;
    std::chrono::steady_clock::time_point start_time_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<node_cli>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}