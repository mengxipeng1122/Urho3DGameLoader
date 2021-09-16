#pragma once

#include "../utils/log.hpp"
#include "../Global.h"
 
namespace Urho3D
{

class Widget: public UIElement
{
    public:
        Widget(Context* context) : UIElement(context) {}
        virtual bool HandleKeyDown(InputKey key, int idx){return false;};

    protected:
        void AddTextureBatch(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor, Texture2D* texture, int dx, int dy, int w=-1, int h=-1)
        {
            ASSERT_CPP(texture != nullptr, "texture is null");
            UIBatch batch(this, BLEND_ALPHA, currentScissor, texture, &vertexData);
            auto transform = Matrix3x4::IDENTITY;
            auto position = GetPosition();
            transform.SetTranslation(Vector3((float)position.x_+dx, (float)position.y_+dy, 0.0f));
            auto tw = texture->GetWidth();
            auto th = texture->GetHeight();
            const IntVector2  size{tw,th};
            if(w <0 || h<0) {
                batch.AddQuad(transform, 0, 0, size.x_, size.y_, 0, 0, size.x_, size.y_);
            }
            else {
                batch.AddQuad(transform, 0, 0, w, h, 0, 0, size.x_, size.y_);
            }
            UIBatch::AddOrMerge(batch, batches);
        }

        void AddCharBatch(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor, char c, FontFace* face, const Color& color, int dx, int dy, int w=-1, int h=-1)
        {

            const FontGlyph* glyph = face->GetGlyph(c);
            auto page = glyph->page_;
            const Vector<SharedPtr<Texture2D> >& textures = face->GetTextures();
            ASSERT_CPP(page < textures.Size(), "page is not correct", page, "/", textures.Size());
            UIBatch batch(this, BLEND_ALPHA, currentScissor, textures[page], &vertexData);
            auto transform = Matrix3x4::IDENTITY;
            auto position = GetPosition();
            transform.SetTranslation(Vector3((float)position.x_+dx, (float)position.y_+dy, 0.0f));
            batch.SetColor(color);
            const IntVector2& size {glyph->texWidth_, glyph->texHeight_};

            if(w<0 || h<0) {
                batch.AddQuad(transform, 0, 0, size.x_, size.y_, glyph->x_, glyph->y_,  size.x_, size.y_);
            }
            else {
                auto offsetx=(w-size.x_)/2;
                auto offsety=(h-size.y_)/2;
                batch.AddQuad(transform, offsetx, offsety, size.x_, size.y_, glyph->x_, glyph->y_,  size.x_, size.y_);
            }

            UIBatch::AddOrMerge(batch, batches);
        }

        // NOTE:
        // dx  in is in/out parameter, 
        // output dx will add by string texture width;
        // only support one line so far
        void AddStringBatch(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor, const String& str, FontFace* face, const Color& color, int& dx, int dy, int gap=-1, int w=-1, int h=-1)
        {
            int stringWidth = 0;
            int stringHeight= 0;
            // calculate string texture width first
            {
                for(auto i = 0;i< str.Length(); i++) {
                    auto c = str[i];
                    const FontGlyph* glyph = face->GetGlyph(c);
                    stringWidth += glyph->texWidth_;
                    stringHeight = glyph->texHeight_;
                }
            }

            {
                auto offsetx = 0;
                auto offsety = 0;
                // find string offset x y
                if(w>=0 && h>=0) {
                    offsetx=(w-stringWidth)/2;
                    offsety=(h-stringHeight)/2;
                }
                const Vector<SharedPtr<Texture2D> >& textures = face->GetTextures();
                for(auto i = 0;i< str.Length(); i++) {
                    auto c = str[i];
                    const FontGlyph* glyph = face->GetGlyph(c);
                    auto page = glyph->page_;
                    ASSERT_CPP(page < textures.Size(), "page is not correct", page, "/", textures.Size());
                    UIBatch batch(this, BLEND_ALPHA, currentScissor, textures[page], &vertexData);
                    auto transform = Matrix3x4::IDENTITY;
                    auto position = GetPosition();
                    transform.SetTranslation(Vector3((float)position.x_+dx+offsetx, (float)position.y_+dy+offsety, 0.0f));
                    batch.SetColor(color);

                    const IntVector2& size {glyph->texWidth_, glyph->texHeight_};
                    batch.AddQuad(transform, 0, 0, size.x_, size.y_, glyph->x_, glyph->y_,  size.x_, size.y_);
                    UIBatch::AddOrMerge(batch, batches);

                    offsetx += gap>=0 ? gap : glyph->texWidth_;
                }
            }

            dx += stringWidth;
        }


        void SendLostSelectedEvent(InputKey key, int idx)
        {
            using namespace LostSelected;
            VariantMap& eventData = GetEventDataMap();
            eventData[P_ELEMENT] = this;
            eventData[P_KEY]     = (int)key;
            eventData[P_INDEX]   = (int)idx;
            SendEvent(E_LOSTSELECTED, eventData);
        }

        void SendItemChangedEvent(int idx)
        {
            using namespace ItemChanged;
            VariantMap& eventData = GetEventDataMap();
            eventData[P_ELEMENT] = this;
            eventData[P_INDEX]   = (int)idx;
            SendEvent(E_ITEMCHANGED, eventData);
        }

        void SendStringChanagedEvent(const String& str)
        {
            using namespace StringChanged;
            VariantMap& eventData = GetEventDataMap();
            eventData[P_ELEMENT] = this;
            eventData[P_STRING]  = str;
            SendEvent(E_STRINGCHANGED, eventData);
        }


};

}
