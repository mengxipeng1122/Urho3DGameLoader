
#include "Settings.hpp"
#include "../utils/log.hpp"
#include "../Global.h"

Settings::Settings(Context* context, const char* xmlfileName)
    : Object(context)
{
    xmlFile_ = new XMLFile(context);
    auto success = xmlFile_->LoadFile(xmlfileName);
    //ASSERT_CPP(success, "loading", xmlfileName, "failed");
    if(success) {
        auto root = xmlFile_->GetRoot();
        { String key = "language";            if(root.HasChild(key)) lang_                = Urho3DStringStrip(root.GetChild(key).GetValue()); }
        { String key = "VideoPathFormat";     if(root.HasChild(key)) videoPathFormat_     = Urho3DStringStrip(root.GetChild(key).GetValue()); }
        { String key = "ThumbnailPathFormat"; if(root.HasChild(key)) thumbnailPathFormat_ = Urho3DStringStrip(root.GetChild(key).GetValue()); }
        { String key = "IconPathFormat";      if(root.HasChild(key)) iconPathFormat_      = Urho3DStringStrip(root.GetChild(key).GetValue()); }
    }
}
