#include <hector_filter_nodelets/cloud_filter_chain.h>

namespace hector_filter_nodelets {

CloudFilterChain::CloudFilterChain(const ros::NodeHandle& nh, const ros::NodeHandle& pnh)
  : nh_(nh), pnh_(pnh), chain_("sensor_msgs::PointCloud2")
{
  chain_.configure("cloud_filter_chain", pnh_);
  cloud_sub_ = nh_.subscribe<sensor_msgs::PointCloud2>("cloud_in", 100, &CloudFilterChain::cloudCb, this);
  cloud_pub_ = nh_.advertise<sensor_msgs::PointCloud2>("cloud_out", 100, false);
}

void CloudFilterChain::cloudCb(const sensor_msgs::PointCloud2ConstPtr& cloud_msg)
{
  sensor_msgs::PointCloud2Ptr cloud_out = boost::make_shared<sensor_msgs::PointCloud2>();
  chain_.update(*cloud_msg, *cloud_out);

  // Validity checks
  if (cloud_out->data.empty()) {
    ROS_WARN_STREAM_THROTTLE(10, "CloudFilterChain output is empty. This message is throttled (10 s).");
    return;
  }
  if (cloud_out->header.frame_id.empty()) {
    ROS_WARN_STREAM_THROTTLE(10, "CloudFilterChain output has an empty frame_id. This message is throttled (10 s).");
    return;
  }
  cloud_pub_.publish(cloud_out);
}

}
