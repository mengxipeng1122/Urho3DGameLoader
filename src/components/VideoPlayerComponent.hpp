#include "../Urho3DAll.h"

// ffmpeg
extern "C"{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavformat/avio.h>
    #include <libavutil/avutil.h>
    #include <libavutil/frame.h>
    #include <libavutil/imgutils.h>
}



class URHO3D_API VideoPlayerComponent : public Component
{
    enum YUVP420PlaneType
    {
    	YUV_PLANE_Y,
    	YUV_PLANE_U,
    	YUV_PLANE_V,
    	YUV_PLANE_MAX_SIZE
    };

	URHO3D_OBJECT(VideoPlayerComponent, Component);

public:
	SharedPtr<StaticModel> outputModel;
	SharedPtr<Material> outputMaterial;
	SharedPtr<Texture2D> outputTexture[YUV_PLANE_MAX_SIZE];

	unsigned prevTime_, prevFrame_;
	unsigned char* framePlanarDataY_;
	unsigned char* framePlanarDataU_;
	unsigned char* framePlanarDataV_;

	VideoPlayerComponent(Context* context);
	virtual ~VideoPlayerComponent();
	static void RegisterObject(Context* context);

	bool OpenFileName(String name);
	bool SetOutputModel(StaticModel* sm);
    bool SetOutputMaterial(Material* m);
	void Play();
	void Pause();
	void Loop(bool isLoop = true);
	void Stop();
	unsigned Advance(float timeStep);

	void ScaleModelAccordingVideoRatio();

	int GetFrameWidth(void) const { return frameWidth_; };
	int GetFrameHeight(void) const { return frameHeight_; };
	float GetFramesPerSecond(void) const { return framesPerSecond_; };
	//void GetFrameRGB(char* outFrame, int pitch);
	//void GetFrameYUV444(char* outFrame, int pitch);
	void UpdatePlaneTextures();
	void HandleUpdate(StringHash eventType, VariantMap& eventData);
private:

        class VideoInfo
        {
            public:
                bool opened_;
                AVFormatContext *pFormatCtx_;
                int              videoStream_;
                AVCodecContext  *pCodecCtx_;
                AVFrame         *pFrameYUV_;
                uint8_t         *buffer_;
                int              frameWidth_{0};
                int              frameHeight_{0};
            public:
                VideoInfo();
                virtual ~VideoInfo();
                bool OpenVideo(const String& fn);
                void CloseVideo();
                void ReadFrame();
                int  GetFrameWidth()  const noexcept { return frameWidth_ ;}
                int  GetFrameHeight() const noexcept { return frameHeight_;}
        };

        VideoInfo videoInfo_;

	bool OpenFile(String fileName);
	int BufferData(void);
	void DecodeVideoFrame(void);
	bool InitTexture();

	File* file_;
	float framesPerSecond_{60.f};
	bool isFileOpened_;
	bool isStopped_;
	unsigned frameWidth_;
	unsigned frameHeight_;
	float videoTimer_{0.f};
	unsigned lastVideoFrame_{0xffffff};

	
};
