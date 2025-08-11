#include <rclcpp/rclcpp.hpp>

class server : public rclcpp::Node
{
public:
    server()
        : Node("server_node")
    {
        sub_ = this->create_subscription<>(
            "/times", 10,
            std::bind(&server::pointCloudBufferCallback, this, std::placeholders::_1));

        pub_ = this->create_publisher<>("/obstacles", 10);
    }

private:
    void clientsubscribed(msg)
    {

        int fibonacciIterative(int msg)
        {
            if (n <= 1)
            {
                return n;
            }
            int prev1 = 0; // Represents F(i-2)
            int prev2 = 1; // Represents F(i-1)
            int current;

            for (int i = 2; i <= n; ++i)
            {
                current = prev1 + prev2;
                prev1 = prev2;
                prev2 = current;
            }
            number = current;
        }
    }

    rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr sub_;
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr pub_;
    int msg;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<server>());
    rclcpp::shutdown();
    return 0;
}