//
// Created by yjxiong on 11/18/15.
//
#include "common.h"
#include "dense_flow.h"
#include <cv.h>
#include <highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <dirent.h>
#include <vector>
#include <algorithm>

using namespace cv;

void calcDenseFlow(std::string folder, int bound, int type, int step,
                   std::vector<std::vector<uchar> >& output_x,
                   std::vector<std::vector<uchar> >& output_y,
                   std::vector<std::vector<uchar> >& output_img){

    //VideoCapture video_stream(file_name);
    //CHECK(video_stream.isOpened())<<"Cannot open video stream \""
    //                              <<file_name
    //                              <<"\" for optical flow extraction.";

    Mat capture_frame, capture_image, prev_image, capture_gray, prev_gray;
    Mat flow, flow_split[2];

    cv::Ptr<cv::DualTVL1OpticalFlow> alg_tvl1 = cv::createOptFlow_DualTVL1();
    bool initialized = false;
    DIR *dp;
    struct dirent *dirp;
    /*if((dp = opendir(folder.c_str())) == NULL) {
      cout << "Error(" << errno << ") opening " << folder << endl;
      return errno;
    }*/
    int iter = 0;
    dp = opendir(folder.c_str());
    if(dp == NULL) {
      std::cout << "Directorio vacio" << std::endl;
    }
    std::vector<std::string> files;
    while (dirp = readdir(dp)) {
      if(dirp->d_name[0] != *(".")) {
        files.push_back(dirp->d_name);
      }
    }
    std::sort(files.begin(), files.end());
    std::string file;
    for(int i = 0; i < files.size(); ++i) {
      //std::cout << "1. Vamos a leer imagen: " << file << std::endl;
      capture_frame = imread(folder + "/" + files[i], 1);
      if(capture_frame.empty()) {
        std::cout << "Imagen vacia" << std::endl;
        continue;
      }
      std::cout << files[i] << std::endl;
      //std::cout << "2. Imagen cargada" << std::endl;
      //build mats for the first frame
      if (!initialized){
        initializeMats(capture_frame, capture_image, capture_gray,
                       prev_image, prev_gray);
        capture_frame.copyTo(prev_image);
        cvtColor(prev_image, prev_gray, CV_BGR2GRAY);
        initialized = true;
        //            LOG(INFO)<<"Initialized";
      }else if(iter % step == 0){
        capture_frame.copyTo(capture_image);
        cvtColor(capture_image, capture_gray, CV_BGR2GRAY);
        
        switch(type){
        case 0: {
          calcOpticalFlowFarneback(prev_gray, capture_gray, flow,
                                   0.702, 5, 10, 2, 7, 1.5,
                                   cv::OPTFLOW_FARNEBACK_GAUSSIAN );
          break;
        }
        case 1: {
          alg_tvl1->calc(prev_gray, capture_gray, flow);
          break;
        }
        default:
          LOG(WARNING)<<"Unknown optical method. Using Farneback";
          calcOpticalFlowFarneback(prev_gray, capture_gray, flow,
                                   0.702, 5, 10, 2, 7, 1.5,
                                   cv::OPTFLOW_FARNEBACK_GAUSSIAN );
        }
        
        std::vector<uchar> str_x, str_y, str_img;
        split(flow, flow_split);
        encodeFlowMap(flow_split[0], flow_split[1], str_x, str_y, bound);
        imencode(".jpg", capture_image, str_img);
        
        output_x.push_back(str_x);
        output_y.push_back(str_y);
        output_img.push_back(str_img);
        //            LOG(INFO)<<iter;
        
        std::swap(prev_gray, capture_gray);
        std::swap(prev_image, capture_image);
      }
      iter += 1;
    }
    
    closedir(dp);
    

    /*bool initialized = false;
    for(int iter = 0;; iter++){
        video_stream >> capture_frame;
        if (capture_frame.empty()) break; // read frames until end

        //build mats for the first frame
        if (!initialized){
            initializeMats(capture_frame, capture_image, capture_gray,
                           prev_image, prev_gray);
            capture_frame.copyTo(prev_image);
            cvtColor(prev_image, prev_gray, CV_BGR2GRAY);
            initialized = true;
//            LOG(INFO)<<"Initialized";
        }else if(iter % step == 0){
            capture_frame.copyTo(capture_image);
            cvtColor(capture_image, capture_gray, CV_BGR2GRAY);

            switch(type){
                case 0: {
                    calcOpticalFlowFarneback(prev_gray, capture_gray, flow,
                                             0.702, 5, 10, 2, 7, 1.5,
                                             cv::OPTFLOW_FARNEBACK_GAUSSIAN );
                    break;
                }
                case 1: {
                    alg_tvl1->calc(prev_gray, capture_gray, flow);
                    break;
                }
                default:
                    LOG(WARNING)<<"Unknown optical method. Using Farneback";
                    calcOpticalFlowFarneback(prev_gray, capture_gray, flow,
                                             0.702, 5, 10, 2, 7, 1.5,
                                             cv::OPTFLOW_FARNEBACK_GAUSSIAN );
            }

            std::vector<uchar> str_x, str_y, str_img;
            split(flow, flow_split);
            encodeFlowMap(flow_split[0], flow_split[0], str_x, str_y, bound);
            imencode(".jpg", capture_image, str_img);

            output_x.push_back(str_x);
            output_y.push_back(str_y);
            output_img.push_back(str_img);
//            LOG(INFO)<<iter;

            std::swap(prev_gray, capture_gray);
            std::swap(prev_image, capture_image);
        }
    }*/
}
