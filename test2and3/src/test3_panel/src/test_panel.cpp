#include <test_panel.hpp>

#include <rviz_common/display_context.hpp>
#include <rclcpp/rclcpp.hpp>

DemoPanel::DemoPanel(QWidget* parent) : rviz_common::Panel(parent){
  layout_ = new QVBoxLayout(this);
  input_num1_label_ = new QLabel("Input 1:");
  input_num2_label_ = new QLabel("Input 2:");
  input_num3_label_ = new QLabel("Input 3:");
  button_ = new QPushButton("sum!");
  input1_ = new QLineEdit();
  input2_ = new QLineEdit();
  input3_ = new QLineEdit();
  result_label_ = new QLabel("Result:");
  error_label_ = new QLabel("");

  layout_-> addWidget(input_num1_label_);
  layout_->addWidget(input1_);
  layout_->addWidget(input_num2_label_);
  layout_->addWidget(input2_);
  layout_->addWidget(input_num3_label_);
  layout_->addWidget(input3_);
  layout_->addWidget(button_);
  layout_->addWidget(result_label_);
  layout_->addWidget(error_label_);

  QObject::connect(button_, &QPushButton::released, this, &DemoPanel::buttonActivated);
}

DemoPanel::~DemoPanel() = default;

void DemoPanel::onInitialize() {
  node_ptr_ = getDisplayContext()->getRosNodeAbstraction().lock();

  rclcpp::Node::SharedPtr node = node_ptr_->get_raw_node();
  client_sum_ = node->create_client<tutorial_interfaces::srv::Sum>("sum");
}

void DemoPanel::buttonActivated() {
  if (!client_sum_) {
    error_label_->setText("Client not initialized");
    return;
  }

  bool ok1 = false;
  bool ok2 = false;
  bool ok3 = false;

  double a = input1_->text().toDouble(&ok1);
  double b = input2_->text().toDouble(&ok2);
  double c = input3_->text().toDouble(&ok3);

  if (!ok1 || !ok2 || !ok3) {
    error_label_->setText("Invalid input");
    return;
  }

  auto request = std::make_shared<tutorial_interfaces::srv::Sum::Request>();
  request->a = a;
  request->b = b;
  request->c = c;

  if (!client_sum_->wait_for_service(std::chrono::seconds(1))) {
    error_label_->setText("Service not available");
    return;
  } else {
    error_label_->setText("");
    client_sum_->async_send_request(
      request,
      std::bind(&DemoPanel::callback, this, std::placeholders::_1));
  }
}

void DemoPanel::callback(rclcpp::Client<tutorial_interfaces::srv::Sum>::SharedFuture future) {
  auto response = future.get();
  result_label_->setText(QString::number(response->sum));
  error_label_->setText("");
}

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(DemoPanel, rviz_common::Panel)



