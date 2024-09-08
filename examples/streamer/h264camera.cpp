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

void H264Camera::start()
{
    // should be parameters:
    // int width, int height, int fps, int bitrate
    int samplesPerSecond = 30;
    capture->Start(1280, 720, V4L2_PIX_FMT_H264, samplesPerSecond, 1500000);
    sampleDuration_us = 1000 * 1000 / samplesPerSecond;
    sampleTime_us = 0;
    //loadNextSample();
}

void H264Camera::stop()
{
    capture->Stop();
}

void H264Camera::loadNextSample()
{
    sample = {};
    //if (!capture->ReadFrame()) return;
    while (!capture->ReadFrame()) {};
    auto *b = reinterpret_cast<const std::byte*>((char*)capture->GetLastBuffer());
    sample.assign(b, b + capture->GetLastSize());
    sampleTime_us += sampleDuration_us;
}

vector<std::byte> H264Camera::initialNALUS()
{
    vector<std::byte> units{};
    if (capture->GetH264HeaderLen() == 0) return units;

    for (int i=0; i<capture->GetH264HeaderLen(); i++)
    {
        units.push_back((std::byte)capture->GetH264Header()[i]);
    }

    return units;
}

rtc::binary H264Camera::getSample()
{
    return sample;
}

uint64_t H264Camera::getSampleTime_us()
{
    return sampleTime_us;
}

uint64_t H264Camera::getSampleDuration_us()
{
    return sampleDuration_us;
}
