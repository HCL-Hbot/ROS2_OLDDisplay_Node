#ifndef OLD_DISPLAY_DRIVER_NODE_HPP
#define OLD_DISPLAY_DRIVER_NODE_HPP

#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/string.hpp"
#include "brainboard_host.hpp"

class OldDisplayDriverNode : public rclcpp::Node {
public:
    OldDisplayDriverNode();

private:
    void commandCallback(const std_msgs::msg::String::SharedPtr msg);
    void blinkBothEyes();

    BRAINBOARD_HOST::DeviceController controller_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr command_subscriber_;
    rclcpp::TimerBase::SharedPtr blink_timer_;
};

#endif // OLD_DISPLAY_DRIVER_NODE_HPP