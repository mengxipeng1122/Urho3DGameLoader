
#include "Settings.hpp"
#include "utils/log.hpp"

Settings::Settings(Context* context, const char* xmlfileName)
{
    xmlFile_ = new XMLFile(context);
    auto success = xmlFile_->LoadFile(xmlfileName);
    ASSERT_CPP(success, "loading", xmlfileName, "failed");

    auto root = xmlFile_->GetRoot();
    lang_ = root.GetChild("language").GetValue();

}
