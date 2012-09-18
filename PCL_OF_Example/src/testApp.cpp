#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB>);
	if (pcl::io::loadPCDFile<pcl::PointXYZRGB> (ofToDataPath("table_scene_mug_stereo_textured.pcd", true), *cloud) == -1) // load the file
	{
		ofLogVerbose ("Couldn't read file");
		
	}else {
		ofLogVerbose() << "Loaded " << cloud->points.size();
		for (int i=0; i<cloud->points.size(); i++) 
		{
			mesh.addVertex(ofVec3f(cloud->points[i].x, cloud->points[i].y, cloud->points[i].z));
			mesh.addColor(ofColor(cloud->points[i].r, cloud->points[i].g, cloud->points[i].b));
		}
		
	}
	// Create a KD-Tree
	pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZRGB>);
	
	// Output has the PointNormal type in order to store the normals calculated by MLS
	pcl::PointCloud<pcl::PointNormal> mls_points;
	
	// Init object (second point type is for the normals, even if unused)
	pcl::MovingLeastSquaresOMP<pcl::PointXYZRGB, pcl::PointNormal> mls(12);
	
	mls.setComputeNormals (true);
	
	// Set parameters
	mls.setInputCloud (cloud);
	mls.setPolynomialFit (true);
	mls.setSearchMethod (tree);
	mls.setSearchRadius (0.03);
	
	// Reconstruct
	mls.process (mls_points);
	cout << "MADE IT" << endl;
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
	
	glPointSize(10);
	
	ofPushStyle();
		camera.begin();
			//ofSetColor(ofColor::blue);
			ofScale(500, 500, 500);
			mesh.drawVertices();
		camera.end();
	ofPopStyle();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}