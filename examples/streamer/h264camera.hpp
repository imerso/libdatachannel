// by imerso

#ifndef h264camera_hpp
#define h264camera_hpp

#include <string>
#include <vector>
#include <videocapture/VideoCapture.h>
#include "stream.hpp"


class H264Camera: public StreamSource {
    std::string directory;
    std::string extension;
    uint64_t sampleDuration_us;
    uint64_t sampleTime_us = 0;
    uint32_t counter = -1;
    bool loop;
    uint64_t loopTimestampOffset = 0;
    std::shared_ptr<VideoCapture> capture;
protected:
    rtc::binary sample = {};
public:
    H264Camera(std::string device);
    virtual ~H264Camera();
    void start(int width, int height, int fps, int bitrate);
    void stop() override;
    void loadNextSample() override;
    std::vector<std::byte> initialNALUS();

    rtc::binary getSample() override;
    uint64_t getSampleTime_us() override;
    uint64_t getSampleDuration_us() override;
};

#endif /* fileparser_hpp */
