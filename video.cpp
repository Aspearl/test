#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <stdexcept>
#include <Windows.h>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include <libavdevice/avdevice.h>
}

void initialize_ffmpeg() {
    avdevice_register_all();
    avformat_network_init();
}

void capture_desktop_and_audio(const std::string& output_url) {
    AVFormatContext* input_format_context = nullptr;
    AVFormatContext* output_format_context = nullptr;

    // Initialize FFmpeg
    initialize_ffmpeg();

    // Set up desktop capture
    const AVInputFormat* input_format = av_find_input_format("gdigrab");
    if (!input_format) {
        throw std::runtime_error("Failed to find gdigrab input format.");
    }

    AVDictionary* options = nullptr;
    av_dict_set(&options, "framerate", "30", 0);
    av_dict_set(&options, "video_size", "1920x1080", 0);
    av_dict_set(&options, "rtbufsize", "10000000", 0);
    av_dict_set(&options, "sample_rate", "44100", 0);
    av_dict_set(&options, "channels", "2", 0);
    av_dict_set(&options, "audio_buffer_size", "20480", 0);

    if (avformat_open_input(&input_format_context, "desktop", input_format, &options) < 0) {
        throw std::runtime_error("Failed to open desktop input.");
    }

    // Set up audio capture
    const AVInputFormat* audio_input_format = av_find_input_format("dshow");
    if (!audio_input_format) {
        throw std::runtime_error("Failed to find dshow input format.");
    }

    AVFormatContext* audio_format_context = nullptr;
    if (avformat_open_input(&audio_format_context, "audio=@device_cm_{33D9A762-90C8-11D0-BD43-00A0C911CE86}\\wave_{DF97586B-D1B8-4490-8F07-81DA1F6F472B}", audio_input_format, nullptr) < 0) {
        throw std::runtime_error("Failed to open audio input.");
    }

    // Set up output format
    avformat_alloc_output_context2(&output_format_context, nullptr, "flv", output_url.c_str());
    if (!output_format_context) {
        throw std::runtime_error("Failed to allocate output context.");
    }

    // Add streams and configure codec
    AVStream* video_stream = avformat_new_stream(output_format_context, nullptr);
    if (!video_stream) {
        throw std::runtime_error("Failed to create video stream.");
    }

    const AVCodec* video_codec = avcodec_find_encoder(AV_CODEC_ID_H264);
    if (!video_codec) {
        throw std::runtime_error("Failed to find H264 encoder.");
    }

    AVCodecContext* video_codec_context = avcodec_alloc_context3(video_codec);
    if (!video_codec_context) {
        throw std::runtime_error("Failed to allocate video codec context.");
    }

    video_codec_context->width = 1920;
    video_codec_context->height = 1080;
    video_codec_context->time_base = { 1, 30 };
    video_codec_context->framerate = { 30, 1 };
    video_codec_context->pix_fmt = AV_PIX_FMT_YUV420P;
    video_codec_context->bit_rate = 400000;
    video_codec_context->max_b_frames = 0;
    video_codec_context->gop_size = 60;
    av_opt_set(video_codec_context->priv_data, "preset", "veryfast", 0);

    if (avcodec_open2(video_codec_context, video_codec, nullptr) < 0) {
        throw std::runtime_error("Failed to open video codec.");
    }

    if (avcodec_parameters_from_context(video_stream->codecpar, video_codec_context) < 0) {
        throw std::runtime_error("Failed to copy video codec parameters.");
    }

    if (!(output_format_context->oformat->flags & AVFMT_NOFILE)) {
        if (avio_open(&output_format_context->pb, output_url.c_str(), AVIO_FLAG_WRITE) < 0) {
            throw std::runtime_error("Failed to open output file.");
        }
    }

    if (avformat_write_header(output_format_context, nullptr) < 0) {
        throw std::runtime_error("Failed to write header to output file.");
    }

    // Start streaming loop
    while (true) {
        // Capture frame, encode, and write to output
    }

    // Cleanup
    avformat_close_input(&input_format_context);
    avformat_close_input(&audio_format_context);
    avformat_free_context(output_format_context);
}

int main() {
    // 初始化为多线程公寓（MTA）
    std::string ff("hello");
    auto fds= ff.find("elx");


    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(hr)) {
        std::cerr << "CoInitializeEx failed\n";
        return -1;
    }

    try {
        const std::string output_url = "rtmp://127.0.0.1:1935/stream/test";
        capture_desktop_and_audio(output_url);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    // Add blocking logic to prevent immediate exit
    std::cout << "Streaming started. Press Enter to stop..." << std::endl;
    std::cin.get();
    CoUninitialize();
    return EXIT_SUCCESS;
}   
