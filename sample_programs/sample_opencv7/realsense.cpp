// realsense-test_06 --- 2022.04.19
#include "realsense.h"

// Constructor
RsCamera::RsCamera(rs2::config cfg, rs2::align _align)
{   
  if(isConnectedDevices()){
    rs2::pipeline_profile profile = pipe.start(cfg); 
    auto stream_profile = profile.get_stream(RS2_STREAM_DEPTH).as<rs2::video_stream_profile>();
    intr = stream_profile.get_intrinsics();
  }
  else{
    throw std::runtime_error("ERR: No cameras are connected.");  
  }
   
   align = _align; 
}

// Destructor
RsCamera::~RsCamera()
{
  pipe.stop();
}

// obtain device information
bool RsCamera::isConnectedDevices(){
  
  devices = ctx.query_devices();
  if(!devices.size())
    return false;
    
  return true;
}

// obtain color frame
void RsCamera::getColorFrame(cv::Mat& color_image) 
{
  rs2::frameset frames = pipe.wait_for_frames();
  rs2::video_frame color_frame = frames.get_color_frame();

  cv::Mat image(cv::Size(WIDTH, HEIGHT), CV_8UC3, (void*)color_frame.get_data(), cv::Mat::AUTO_STEP);

  image.copyTo(color_image);
}

// change image coordinate to world coordinate
void RsCamera::doDeprojectPosition(cv::Mat& depth_image, int x_pix, int y_pix)
{
  const float pixel[] = { (float)x_pix,(float)y_pix };

  rs2::frameset frames = pipe.wait_for_frames();
  auto aligned_frames = align.process(frames);

  rs2::depth_frame depth = aligned_frames.get_depth_frame();
  rs2::video_frame depth_frame = depth.apply_filter(color_map);

  rs2_deproject_pixel_to_point(point, &intr, pixel, depth.get_distance(x_pix, y_pix));

  //std::cout << "[ " << x_pix << "px, " << y_pix << "px ] = " << "[ " << point[0] << ", " << point[1] << ", " << point[2] << "]" << std::endl;

  cv::Mat image(cv::Size(WIDTH, HEIGHT), CV_8UC3, (void*)depth_frame.get_data(), cv::Mat::AUTO_STEP);

  image.copyTo(depth_image);

  return {point[0], point[1], point[2]};
}


