/*
 * VoxelDownsampling.cpp
 *
 *  Created on: 04/04/2014
 *      Author: rgap
 */

#include "VoxelDownsampling.h"

VoxelDownsampling::VoxelDownsampling() {
}

void VoxelDownsampling::downSample(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud) {
	//std::cout << "Before : " << cloud->points.size() << " points." << std::endl;
	vg.setInputCloud(cloud);
	vg.setLeafSize(0.4f, 0.4f, 0.4f);
	vg.filter(*cloud);
	//std::cout << "After : " << cloud->points.size() << " points." << std::endl;
}

VoxelDownsampling::~VoxelDownsampling() {
}
