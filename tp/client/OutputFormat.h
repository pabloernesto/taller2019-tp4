#ifndef OUTPUTFORMAT_H
#define OUTPUTFORMAT_H
#include <string>

class AVCodec;
class AVFrame;
class AVPacket;
class AVOutputFormat;
class AVStream;
class AVCodecContext;
class FormatContext;
class SwsContext;

class OutputFormat {
public:
    OutputFormat(FormatContext& context, const std::string& filename);
    ~OutputFormat();
    void writeFrame(const char* data, SwsContext* swsContext);
    void close();
private:
    void initFrame();
    void codecContextInit(AVCodec* codec);
    FormatContext& context;
    int width;
    int height;
    AVOutputFormat* avOutputFormat;
    AVStream* video_avstream;
    AVCodecContext* codecContext;
    int currentPts;
    FILE* outputFile;
    AVFrame* frame;
    AVPacket* pkt;
};
#endif
