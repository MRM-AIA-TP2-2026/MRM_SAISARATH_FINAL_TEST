#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <sensor_msgs/msg/Image.hpp>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>

class ObstacleDetectionNode : public rclcpp::Node
{
public:
    ObstacleDetectionNode()
        : Node("question4")
    {
        sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            "/Image", 10,
            std::bind(&ObstacleDetectionNode::pointCloudBufferCallback, this, std::placeholders::_1));

        pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/cloud", 10);
    }

private:
    void pointCloudBufferCallback(const sensor_msgs::msg::Image::SharedPtr msg)
    {

        if (!msg)
        {
            RCLCPP_WARN(this->get_logger(), "No Image received yet.");
            return;
        }

        sensor_msgs::msg::PointCloud2 output;
        pcl::toROSMsg(*cloud_no_ground, output);
        output.header = msg->header;
        pub_->publish(output);
    }

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr sub_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ObstacleDetectionNode>());
    rclcpp::shutdown();
    return 0;
}