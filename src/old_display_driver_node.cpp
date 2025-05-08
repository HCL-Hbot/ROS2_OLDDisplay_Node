#include "old_display_driver_node.hpp"
#include <algorithm>

OldDisplayDriverNode::OldDisplayDriverNode()
: Node("old_display_driver_node"), controller_("/dev/ttyACM0", 1200) {
    // Subscriber
    command_subscriber_ = this->create_subscription<std_msgs::msg::String>(
        "display_commands",
        10,
        std::bind(&OldDisplayDriverNode::commandCallback, this, std::placeholders::_1)
    );

    // Timer to blink every 10 seconds
    blink_timer_ = this->create_wall_timer(
        std::chrono::seconds(10),
        std::bind(&OldDisplayDriverNode::blinkBothEyes, this)
    );

    RCLCPP_INFO(this->get_logger(), "OldDisplayDriverNode started.");
}

void OldDisplayDriverNode::blinkBothEyes() {
    controller_.blink(BRAINBOARD_HOST::EyeID::BOTH);
    RCLCPP_INFO(this->get_logger(), "Blinking both eyes.");
}

void OldDisplayDriverNode::commandCallback(const std_msgs::msg::String::SharedPtr msg) {
    std::string command = msg->data;
    std::transform(command.begin(), command.end(), command.begin(), ::tolower);

    if (command == "blink") {
        blinkBothEyes();
    } else if (command == "think") {
        controller_.controlEyes(BRAINBOARD_HOST::EyeID::BOTH, 0, 0, BRAINBOARD_HOST::EyeAnimation::THINKING_ANIM, 100);
        RCLCPP_INFO(this->get_logger(), "Thinking animation for both eyes.");
    } else if (command == "confused") {
        controller_.controlEyes(BRAINBOARD_HOST::EyeID::BOTH, 0, 0, BRAINBOARD_HOST::EyeAnimation::CONFUSED_ANIM, 100);
        RCLCPP_INFO(this->get_logger(), "Confused animation for both eyes.");
    } else {
        RCLCPP_WARN(this->get_logger(), "Unknown command: '%s'", command.c_str());
    }
}


int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<OldDisplayDriverNode>());
  rclcpp::shutdown();
  return 0;
}
