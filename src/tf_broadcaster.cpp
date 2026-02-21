#include <chrono>
#include <memory>
#include <cmath>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2_ros/transform_broadcaster.h"

using namespace std::chrono_literals;

class TFBroadcaster : public rclcpp::Node
{
public:
  TFBroadcaster()
  : Node("tf_broadcaster"),
    time_(0.0)
  {
    tf_broadcaster_ =
      std::make_shared<tf2_ros::TransformBroadcaster>(this);

    timer_ = this->create_wall_timer(
      100ms,
      std::bind(&TFBroadcaster::broadcast_transform, this));
  }

private:
  void broadcast_transform()
  {
    geometry_msgs::msg::TransformStamped transform;

    transform.header.stamp = this->get_clock()->now();
    transform.header.frame_id = "world";
    transform.child_frame_id = "robot";

    // Circular motion
    transform.transform.translation.x = 2.0 * std::cos(time_);
    transform.transform.translation.y = 2.0 * std::sin(time_);
    transform.transform.translation.z = 0.0;

    // Identity quaternion (no rotation)
    transform.transform.rotation.x = 0.0;
    transform.transform.rotation.y = 0.0;
    transform.transform.rotation.z = 0.0;
    transform.transform.rotation.w = 1.0;

    tf_broadcaster_->sendTransform(transform);

    time_ += 0.05;  // Increment time for smooth circular motion
  }

  std::shared_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  rclcpp::TimerBase::SharedPtr timer_;
  double time_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TFBroadcaster>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
