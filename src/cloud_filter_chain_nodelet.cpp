#include <nodelet/nodelet.h>
#include <pluginlib/class_list_macros.h>

#include <hector_filter_nodelets/cloud_filter_chain.h>

namespace hector_filter_nodelets {

class CloudFilterChainNodelet : public nodelet::Nodelet {
  virtual void onInit() {
    ros::NodeHandle& nh = getNodeHandle();
    ros::NodeHandle& pnh = getPrivateNodeHandle();
    chain_ = std::make_shared<CloudFilterChain>(nh, pnh);
  }

  std::shared_ptr<CloudFilterChain> chain_;
};

}

PLUGINLIB_EXPORT_CLASS(hector_filter_nodelets::CloudFilterChainNodelet, nodelet::Nodelet);
