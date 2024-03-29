#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
#include "example_interfaces/msg/int64.hpp"

class Number_publisher : public rclcpp::Node 
{
public:
    Number_publisher() : Node("publisher") 
    {
        this->declare_parameter("number_to_publish",2);
        this->declare_parameter("publish_frequency",1.0);

        double publish_frequency =this->get_parameter("publish_frequency").as_double();

        number_=this->get_parameter("number_to_publish").as_int();
        publisher_ = this-> create_publisher<example_interfaces::msg::Int64>("Number", 10);
        timer_ = this-> create_wall_timer(std::chrono::milliseconds((int)(1000.0 / publish_frequency)),
                                        std::bind(&Number_publisher::publishNews, this));
                                       

    }
private:
    void publishNews()
    {
        auto msg = example_interfaces::msg::Int64();
        msg.data = number_;
        publisher_->publish(msg);
    }

    int number_;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

};


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Number_publisher>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}