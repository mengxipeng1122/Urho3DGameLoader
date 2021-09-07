
#include "../utils/log.hpp"
#include "VideoPlayerComponent.hpp"

VideoPlayerComponent::VideoPlayerComponent(Context* context) :
	Component(context),
	isFileOpened_(false),
	isStopped_(false),
	frameWidth_(0),
	frameHeight_(0),
	file_(0),
	outputMaterial(nullptr),
	prevTime_(0), 
	prevFrame_(0),
	framePlanarDataY_(0),
	framePlanarDataU_(0),
	framePlanarDataV_(0)

{
//	SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(VideoPlayerComponent, HandleUpdate));
}

VideoPlayerComponent::~VideoPlayerComponent()
{

	if (framePlanarDataY_)
	{
		delete[] framePlanarDataY_;
		framePlanarDataY_ = 0;
	}

	if (framePlanarDataU_)
	{
		delete[] framePlanarDataU_;
		framePlanarDataU_ = 0;
	}

	if (framePlanarDataV_)
	{
		delete[] framePlanarDataV_;
		framePlanarDataV_ = 0;
	}

}

void VideoPlayerComponent::RegisterObject(Context* context)
{
	context->RegisterFactory<VideoPlayerComponent>();
}

bool VideoPlayerComponent::OpenFileName(String name)
{
	bool ret = false;

    isFileOpened_ = OpenFile(name);

    frameWidth_ = videoInfo_.GetFrameWidth();    
    frameHeight_= videoInfo_.GetFrameHeight();   

	ret = isFileOpened_;
	return ret;
}

bool VideoPlayerComponent::SetOutputModel(StaticModel* sm)
{
	bool ret = false;
	if (sm)
	{
		// Set model surface
		outputModel = sm;
		outputMaterial = sm->GetMaterial(0);

		// Create textures & images
		InitTexture();
		//InitCopyBuffer();
		ScaleModelAccordingVideoRatio();
	}

	return ret;
}

bool VideoPlayerComponent::SetOutputMaterial(Material* m)
{
	bool ret = false;
	if (m)
	{
		// Set model surface
		outputMaterial = m;

		// Create textures & images
		InitTexture();
		//InitCopyBuffer();
		//ScaleModelAccordingVideoRatio();
	}

	return ret;
}


void VideoPlayerComponent::Play()
{
	isStopped_ = false;
}

void VideoPlayerComponent::Pause() 
{
	isStopped_ = true;
}

void VideoPlayerComponent::Loop(bool isLoop)
{

}

void VideoPlayerComponent::Stop()
{
	isStopped_ = true;
	videoTimer_ = 0;
	prevFrame_ = 0;
	file_->Seek(0);
}

void VideoPlayerComponent::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
	using namespace Update;
	float timeStep = eventData[P_TIMESTEP].GetFloat();
	//Time* time = GetSubsystem<Time>();

	unsigned frame = Advance(timeStep);
	if (prevFrame_ != frame)
	{
		UpdatePlaneTextures();		
	}

	prevFrame_ = frame;
}

bool VideoPlayerComponent::OpenFile(String fileName)
{
    return videoInfo_.OpenVideo(fileName);
}


unsigned VideoPlayerComponent::Advance(float timeStep)
{
	//if (isStopped_) return lastVideoFrame_;

	// advance video timer by delta time in milliseconds
	videoTimer_ += timeStep;

	// calculate current frame
	const unsigned curFrame = static_cast<unsigned>(floor(videoTimer_ * framesPerSecond_));


        LOG_INFOS_CPP(" go here ", lastVideoFrame_, curFrame, timeStep, videoTimer_);
	if (lastVideoFrame_ != curFrame)
	{
        LOG_INFOS_CPP(" go here ");
        videoInfo_.ReadFrame();
		lastVideoFrame_ = curFrame;
		UpdatePlaneTextures();		
	}

	return curFrame;
}


bool VideoPlayerComponent::InitTexture()
{
	bool ret = false;

	// Try clear if using case of reassingn the movie file
	for (int i = 0; i < YUV_PLANE_MAX_SIZE; ++i)
	{
		if (outputTexture[i])
		{
			outputTexture[i]->ReleaseRef();
			outputTexture[i] = 0;
		}
	}

	// do this for fill m_YUVFrame with properly info about frame
	Advance(0);


	// Planes textures create
	for (int i = 0; i < YUV_PLANE_MAX_SIZE; ++i)
	{
		int texWidth = 0;
		int texHeight = 0;

		switch (i)
		{
		case YUV_PLANE_Y:
			texWidth  = videoInfo_.pFrameYUV_->width;
			texHeight = videoInfo_.pFrameYUV_->height;
            LOG_INFOS_CPP(texWidth, texHeight);
			framePlanarDataY_ = new unsigned char[texWidth * texHeight];
			break;
		
		case YUV_PLANE_U:
			texWidth  = videoInfo_.pFrameYUV_->width/2;
			texHeight = videoInfo_.pFrameYUV_->height/2;
			framePlanarDataU_ = new unsigned char[texWidth * texHeight];
			break;

		case YUV_PLANE_V:
			texWidth  = videoInfo_.pFrameYUV_->width/2;
			texHeight = videoInfo_.pFrameYUV_->height/2;
			framePlanarDataV_ = new unsigned char[texWidth * texHeight];
			break;
		}

		outputTexture[i] = SharedPtr<Texture2D>(new Texture2D(context_));
		outputTexture[i]->SetSize(texWidth, texHeight, Graphics::GetLuminanceFormat(), TEXTURE_DYNAMIC);
		outputTexture[i]->SetFilterMode(FILTER_BILINEAR);
		outputTexture[i]->SetNumLevels(1);
		outputTexture[i]->SetAddressMode(TextureCoordinate::COORD_U, TextureAddressMode::ADDRESS_MIRROR);
		outputTexture[i]->SetAddressMode(TextureCoordinate::COORD_V, TextureAddressMode::ADDRESS_MIRROR);

    }


	// assign planes textures into sepparated samplers for shader
	outputMaterial->SetTexture(TextureUnit::TU_DIFFUSE, outputTexture[YUV_PLANE_Y]);
	outputMaterial->SetTexture(TextureUnit::TU_SPECULAR, outputTexture[YUV_PLANE_U]);
	outputMaterial->SetTexture(TextureUnit::TU_NORMAL, outputTexture[YUV_PLANE_V]);
	
	//outputModel->SetMaterial(0, outputMaterial);

	return ret;
	
}

void VideoPlayerComponent::UpdatePlaneTextures() 
{
	Graphics* graphics = GetSubsystem<Graphics>();
    if(framePlanarDataU_==nullptr) return;
    if(framePlanarDataY_==nullptr) return;
    if(framePlanarDataV_==nullptr) return;

	auto texWidth  = videoInfo_.pFrameYUV_->width;
	auto texHeight = videoInfo_.pFrameYUV_->height;


	// Convert non-planar YUV-frame into separated planar raw-textures 
	for (int y = 0; y < texHeight; ++y)
	{
        {
            unsigned char* sd = videoInfo_.pFrameYUV_->data[0];
            //LOG_INFOS_CPP("y", y, texWidth, texHeight, (int)videoInfo_.pFrameYUV_->linesize[0], (void*)framePlanarDataY_);
		    memcpy(&framePlanarDataY_[y*texWidth], &sd[y*videoInfo_.pFrameYUV_->linesize[0]], texWidth);
        }
    }

	for (int y = 0; y < texHeight/2; ++y)
	{
        {
            unsigned char* sd = videoInfo_.pFrameYUV_->data[1];
		    memcpy(&framePlanarDataU_[y*texWidth/2], &sd[y*videoInfo_.pFrameYUV_->linesize[1]], texWidth/2);
        }
    }

	for (int y = 0; y < texHeight/2; ++y)
	{
        {
            unsigned char* sd = videoInfo_.pFrameYUV_->data[2];
		    memcpy(&framePlanarDataV_[y*texWidth/2], &sd[y*videoInfo_.pFrameYUV_->linesize[2]], texWidth/2);
        }
    }


    {
		for (int x = 0; x < texWidth; ++x)
		{

//			const int offsetUV = x + y * m_YUVFrame.uv_width;

//			framePlanarDataU_[offsetUV] = m_YUVFrame.u[x + y * m_YUVFrame.uv_stride];
//			framePlanarDataV_[offsetUV] = m_YUVFrame.v[x + y * m_YUVFrame.uv_stride];

			// 2x2 more work for Y

//			const int offsetLUTile = x + y * m_YUVFrame.y_width;
//			framePlanarDataY_[offsetLUTile] = m_YUVFrame.y[x + y * m_YUVFrame.y_stride];

//			const int offsetRUTile = m_YUVFrame.uv_width + x + y * m_YUVFrame.y_width;
//			framePlanarDataY_[offsetRUTile] = m_YUVFrame.y[m_YUVFrame.uv_width + x + y * m_YUVFrame.y_stride];
//
//			const int offsetLBTile = x + (y + m_YUVFrame.uv_height) * m_YUVFrame.y_width;
//			framePlanarDataY_[offsetLBTile] = m_YUVFrame.y[x + ((y + m_YUVFrame.uv_height) * m_YUVFrame.y_stride)];
//
//			const int offsetRBTile = (m_YUVFrame.uv_width + x) + (y + m_YUVFrame.uv_height) * m_YUVFrame.y_width;
//			framePlanarDataY_[offsetRBTile] = m_YUVFrame.y[(m_YUVFrame.uv_width + x) + ((y + m_YUVFrame.uv_height) * m_YUVFrame.y_stride)];

		}
	}

	// Fill textures with new data
	for (int i = 0; i < YUV_PLANE_MAX_SIZE; ++i)
	{
		switch (i)
		{
		case YUVP420PlaneType::YUV_PLANE_Y:
			outputTexture[i]->SetSize(texWidth, texHeight, Graphics::GetLuminanceFormat(), TEXTURE_DYNAMIC);
			outputTexture[i]->SetData(0, 0, 0,texWidth, texHeight, (const void*)framePlanarDataY_);			
			break;

		case YUVP420PlaneType::YUV_PLANE_U:
			outputTexture[i]->SetSize(texWidth/2, texHeight/2, Graphics::GetLuminanceFormat(), TEXTURE_DYNAMIC);
			outputTexture[i]->SetData(0, 0, 0,texWidth/2, texHeight/2, (const void*)framePlanarDataU_);			
			break;

		case YUVP420PlaneType::YUV_PLANE_V:
			outputTexture[i]->SetSize(texWidth/2, texHeight/2, Graphics::GetLuminanceFormat(), TEXTURE_DYNAMIC);
			outputTexture[i]->SetData(0, 0, 0,texWidth/2, texHeight/2, (const void*)framePlanarDataV_);			
			break;
		}
	}
}


void VideoPlayerComponent::ScaleModelAccordingVideoRatio()
{
	if (outputModel)
	{
		Node* node = outputModel->GetNode();
		float ratioW = (float)frameWidth_ / (float)frameHeight_;
		float ratioH = (float)frameHeight_ / (float)frameWidth_;

		Vector3 originalScale = node->GetScale();
		node->SetScale(Vector3(originalScale.x_, originalScale.x_ * ratioH, originalScale.z_ * ratioH));
	}
}

bool VideoPlayerComponent::VideoInfo::OpenVideo(const String& fn)
{
    CloseVideo();

    //mutex_.lock();

    // Open video file  
    if( avformat_open_input(&pFormatCtx_, fn.CString(), NULL, NULL) != 0 ) {  
        LOG_INFOS_CPP(" avformat_open_input failed ", fn.CString());
        return false;

    }  

    // Retrieve stream information  
    if( avformat_find_stream_info(pFormatCtx_, NULL) <0 ) {  
        avformat_close_input(&pFormatCtx_); pFormatCtx_=nullptr;
        LOG_INFOS_CPP(" avformat_find_stream_info failed %s ", fn.CString());
        return false;
    }  

    // Dump information about file onto standard error  
    // av_dump_format(videoInfo_.pFormatCtx, 0, file_name, 0);  
    // Find the first video stream  
    videoStream_ = -1;  
    for(size_t i=0; i <pFormatCtx_->nb_streams; i++) {  
        if( pFormatCtx_->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO ) {
            videoStream_=i;
            break;  
        }  
    }  
    if( videoStream_<0)
    {
        LOG_INFOS_CPP(" can not find video stream  %s ", fn.CString());
        avformat_close_input(&pFormatCtx_); pFormatCtx_=nullptr;
        return false;
    }  

    // Get a pointer to the codec context for the video stream  
    pCodecCtx_ = avcodec_alloc_context3(NULL);
    if (pCodecCtx_ == NULL)
    {
        printf("Could not allocate AVCodecContext\n");
        return -1;
    }
    avcodec_parameters_to_context(pCodecCtx_, pFormatCtx_->streams[videoStream_]->codecpar);
    // Find the decoder for the video stream  
    AVCodec* pCodec_ = avcodec_find_decoder(pFormatCtx_->streams[videoStream_]->codecpar->codec_id);  
    if( pCodec_ == nullptr ) {  
        LOG_INFOS_CPP("Unsupported codec! %s",fn.CString());  
        avformat_close_input(&pFormatCtx_); pFormatCtx_=nullptr;
        return false;
    }  

    // Open codec  
    AVDictionary* optionsDict = NULL;  
    if( avcodec_open2(pCodecCtx_, pCodec_, &optionsDict) <0 ) {  
        avcodec_close(pCodecCtx_); pCodecCtx_=nullptr;
        avformat_close_input(&pFormatCtx_); pFormatCtx_=nullptr;
        return false;
    }  
    //Source color format
    pFrameYUV_ = av_frame_alloc();  
    if( pFrameYUV_ == NULL ) {  
        LOG_INFOS_CPP("av_frame_alloc failed!");  
        avcodec_free_context(&pCodecCtx_); pCodecCtx_=nullptr;
        avformat_close_input(&pFormatCtx_); pFormatCtx_=nullptr;
        return false;
    }  
    //int numBytes = avpicture_get_size(  
    //        AV_PIX_FMT_YUV420P,
    //        pCodecCtx_->width,  
    //        pCodecCtx_->height);  
    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, pCodecCtx_->width, pCodecCtx_->height, 1);
    buffer_ = (uint8_t *)av_malloc( numBytes*sizeof(uint8_t) );  
    if(buffer_ == NULL)
    {
        LOG_INFOS_CPP("av_alloc failed!");  
        av_frame_free(&pFrameYUV_); pFrameYUV_=nullptr;
        avcodec_close(pCodecCtx_); pCodecCtx_=nullptr;
        avformat_close_input(&pFormatCtx_); pFormatCtx_=nullptr;
    }

    //avpicture_fill((AVPicture *)pFrameYUV_, buffer_, AV_PIX_FMT_YUV420P,  pCodecCtx_->width, pCodecCtx_->height);  
    av_image_fill_arrays(pFrameYUV_->data, pFrameYUV_->linesize, buffer_,  AV_PIX_FMT_YUV420P, pCodecCtx_->width, pCodecCtx_->height,1);

    frameWidth_ = 512;
    frameHeight_= 320;

    opened_ = true;
    //mutex_.unlock();

    return true;
}

void VideoPlayerComponent::VideoInfo::CloseVideo()
{
    // Open video file  
    if(buffer_     != nullptr)  {av_free(buffer_);                   buffer_=nullptr;            }
    if(pFrameYUV_  != nullptr)  {av_frame_free(&pFrameYUV_);         pFrameYUV_=nullptr;         }
    if(pCodecCtx_  != nullptr)  {avcodec_close(pCodecCtx_);          pCodecCtx_=nullptr;         }
    if(pFormatCtx_ != nullptr)  {avformat_close_input(&pFormatCtx_); pFormatCtx_=nullptr;        }

    frameWidth_ = 0;
    frameHeight_= 0;

    opened_ = false;
}


VideoPlayerComponent::VideoInfo::VideoInfo():
      opened_       (false)
    , pFormatCtx_   (nullptr)
    , videoStream_  (-1)
    , pCodecCtx_    (nullptr)
    , pFrameYUV_    (nullptr)
    , buffer_       (nullptr)
{
}

VideoPlayerComponent::VideoInfo::~VideoInfo()
{
    CloseVideo();
}

void VideoPlayerComponent::VideoInfo::ReadFrame()
{
    if(!opened_ ) return;
    // 
    AVPacket packet;  
    if( av_read_frame(pFormatCtx_, &packet) >= 0 ) {  
    }
    else
    {
        av_seek_frame(pFormatCtx_, videoStream_, 0,  AVSEEK_FLAG_FRAME);
        if(av_read_frame(pFormatCtx_, &packet)<0)
        {
            LOG_INFOS_CPP(" av_read_frame failed "); exit(-9);
        }
    }
    {  
        // Is this a packet from the video stream?  
        if( packet.stream_index == videoStream_ ) {  
            // Decode video frame  
            int frameFinished=0;  
            //avcodec_decode_video2(pCodecCtx_, pFrameYUV_, &frameFinished, &packet);
            //avcodec_send_packet(pCodecCtx_, &packet);
            //avcodec_receive_frame(pCodecCtx_, pFrameYUV_);
            int used;
            if (pCodecCtx_->codec_type == AVMEDIA_TYPE_VIDEO ||
                    pCodecCtx_->codec_type == AVMEDIA_TYPE_AUDIO) {
                used = avcodec_send_packet(pCodecCtx_, &packet);
                if (used < 0 && used != AVERROR(EAGAIN) && used != AVERROR_EOF) {
                } else {
                    if (used >= 0) packet.size = 0;
                    used = avcodec_receive_frame(pCodecCtx_, pFrameYUV_);
                    if (used >= 0) frameFinished = 1;
                }
            }

            if( frameFinished ) 
            {  
            }

        }  
    }  

    // Free the packet that was allocated by av_read_frame  
    av_packet_unref(&packet);  
}  


