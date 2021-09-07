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
	WeakPtr<Material> outputMaterial;
	WeakPtr<Texture2D> outputTexture[YUV_PLANE_MAX_SIZE];

	unsigned prevTime_, prevFrame_;
	unsigned char* framePlanarDataY_;
	unsigned char* framePlanarDataU_;
	unsigned char* framePlanarDataV_;

	VideoPlayerComponent(Context* context);
	virtual ~VideoPlayerComponent();
	static void RegisterObject(Context* context);

	bool OpenFileName(String name);
    void Close();
    bool SetOutputMaterial(Material* m);
	unsigned Advance(float timeStep);

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
                AVFormatContext *pFormatCtx_{nullptr};
                int              videoStream_{-1};
                AVCodecContext  *pCodecCtx_{nullptr};
                AVFrame         *pFrameYUV_{nullptr};
                uint8_t         *buffer_{nullptr};
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
    void ClearTexture();

	File* file_;
	float framesPerSecond_{60.f};
	bool isFileOpened_{false};
	bool isInitilizedTextures_{false};
	unsigned frameWidth_{0};
	unsigned frameHeight_{0};
	float videoTimer_{0.f};
	unsigned lastVideoFrame_{0u};

	
};
