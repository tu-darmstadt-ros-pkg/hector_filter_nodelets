#ifndef HECTOR_FILTER_NODELETS_CLOUD_FILTER_CHAIN_H
#define HECTOR_FILTER_NODELETS_CLOUD_FILTER_CHAIN_H

#include <ros/ros.h>
#include <filters/filter_chain.hpp>
#include <sensor_msgs/PointCloud2.h>

namespace hector_filter_nodelets {

class CloudFilterChain {
public:
  CloudFilterChain(const ros::NodeHandle& nh, const ros::NodeHandle& pnh);
private:
  void cloudCb(const sensor_msgs::PointCloud2ConstPtr& cloud_msg);
  ros::NodeHandle nh_;
  ros::NodeHandle pnh_;

  filters::FilterChain<sensor_msgs::PointCloud2> chain_;

  ros::Subscriber cloud_sub_;
  ros::Publisher cloud_pub_;
};

}

#endif
