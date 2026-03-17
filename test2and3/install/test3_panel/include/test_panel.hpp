#include <QLayout>
#include <QLayoutItem>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>

#include <rviz_common/panel.hpp>
#include <rviz_common/ros_integration/ros_node_abstraction_iface.hpp>

#include "tutorial_interfaces/srv/sum.hpp"
#include "tutorial_interfaces/srv/prod.hpp"

class DemoPanel : public rviz_common::Panel
{
  Q_OBJECT
public:
  DemoPanel(QWidget* parent = nullptr);
  ~DemoPanel() override;

  void onInitialize() override;

protected:
  std::shared_ptr<rviz_common::ros_integration::RosNodeAbstractionIface> node_ptr_;
  std::shared_ptr<rclcpp::Client<tutorial_interfaces::srv::Sum>> client_sum_;

  QLabel* input_num1_label_;
  QLabel* input_num2_label_;
  QLabel* input_num3_label_;
  QPushButton* button_;
  QLineEdit* input1_;
  QLineEdit* input2_;
  QLineEdit* input3_;
  QLabel*    result_label_;
  QLabel*    error_label_;
  QVBoxLayout*   layout_;

private:
  void buttonActivated();
  void callback(rclcpp::Client<tutorial_interfaces::srv::Sum>::SharedFuture future);
};