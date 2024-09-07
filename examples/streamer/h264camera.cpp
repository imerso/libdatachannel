// by imerso

#include "h264camera.hpp"

using namespace std;


H264Camera::H264Camera(std::string device)
{
    capture = make_shared<VideoCapture>(device.c_str());
}


H264Camera::~H264Camera()
{

}

void H264Camera::start(int width, int height, int fps, int bitrate)
{
    capture->Start(width, height, V4L2_PIX_FMT_H264, fps, bitrate);
}

void H264Camera::stop()
{

}

void H264Camera::loadNextSample()
{
}

vector<std::byte> H264Camera::initialNALUS()
{
    vector<std::byte> units{};
    return units;
}

rtc::binary H264Camera::getSample()
{
    return rtc::binary();
}

uint64_t H264Camera::getSampleTime_us()
{
    return 0;
}

uint64_t H264Camera::getSampleDuration_us()
{
    return 0;
}
