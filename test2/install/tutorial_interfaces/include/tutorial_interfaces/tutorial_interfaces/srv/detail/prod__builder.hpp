// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from tutorial_interfaces:srv/Prod.idl
// generated code does not contain a copyright notice

#ifndef TUTORIAL_INTERFACES__SRV__DETAIL__PROD__BUILDER_HPP_
#define TUTORIAL_INTERFACES__SRV__DETAIL__PROD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "tutorial_interfaces/srv/detail/prod__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace tutorial_interfaces
{

namespace srv
{

namespace builder
{

class Init_Prod_Request_c
{
public:
  explicit Init_Prod_Request_c(::tutorial_interfaces::srv::Prod_Request & msg)
  : msg_(msg)
  {}
  ::tutorial_interfaces::srv::Prod_Request c(::tutorial_interfaces::srv::Prod_Request::_c_type arg)
  {
    msg_.c = std::move(arg);
    return std::move(msg_);
  }

private:
  ::tutorial_interfaces::srv::Prod_Request msg_;
};

class Init_Prod_Request_b
{
public:
  explicit Init_Prod_Request_b(::tutorial_interfaces::srv::Prod_Request & msg)
  : msg_(msg)
  {}
  Init_Prod_Request_c b(::tutorial_interfaces::srv::Prod_Request::_b_type arg)
  {
    msg_.b = std::move(arg);
    return Init_Prod_Request_c(msg_);
  }

private:
  ::tutorial_interfaces::srv::Prod_Request msg_;
};

class Init_Prod_Request_a
{
public:
  Init_Prod_Request_a()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Prod_Request_b a(::tutorial_interfaces::srv::Prod_Request::_a_type arg)
  {
    msg_.a = std::move(arg);
    return Init_Prod_Request_b(msg_);
  }

private:
  ::tutorial_interfaces::srv::Prod_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::tutorial_interfaces::srv::Prod_Request>()
{
  return tutorial_interfaces::srv::builder::Init_Prod_Request_a();
}

}  // namespace tutorial_interfaces


namespace tutorial_interfaces
{

namespace srv
{

namespace builder
{

class Init_Prod_Response_prod
{
public:
  Init_Prod_Response_prod()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::tutorial_interfaces::srv::Prod_Response prod(::tutorial_interfaces::srv::Prod_Response::_prod_type arg)
  {
    msg_.prod = std::move(arg);
    return std::move(msg_);
  }

private:
  ::tutorial_interfaces::srv::Prod_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::tutorial_interfaces::srv::Prod_Response>()
{
  return tutorial_interfaces::srv::builder::Init_Prod_Response_prod();
}

}  // namespace tutorial_interfaces

#endif  // TUTORIAL_INTERFACES__SRV__DETAIL__PROD__BUILDER_HPP_
