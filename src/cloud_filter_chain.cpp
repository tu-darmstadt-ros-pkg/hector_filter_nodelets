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
  sensor_msgs::PointCloud2 cloud_out;
  chain_.update(*cloud_msg, cloud_out);
  if (cloud_out.data.empty()) {
    ROS_WARN_STREAM("CloudFilterChain output is empty.");
    return;
  }
  if (cloud_out.header.frame_id.empty()) {
    ROS_WARN_STREAM("CloudFilterChain output has an empty frame_id.");
    return;
  }
  cloud_pub_.publish(cloud_out);
}

}
