#pragma once

#include "../utils/log.hpp"
#include "../Global.h"
 
namespace Urho3D
{

// send from widget classes
URHO3D_EVENT(E_ITEMCHANGED, ItemChanged)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_INDEX,   Index);                // Integer [in/out]
}

URHO3D_EVENT(E_LOSTSELECTED, LostSelected)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_KEY,     InputKey);             // pressed key;
    URHO3D_PARAM(P_INDEX,   Index);                // Integer [in/out]
}

URHO3D_EVENT(E_STRINGCHANGED,   StringChanged)
{
    URHO3D_PARAM(P_ELEMENT, Element);              // UIElement pointer
    URHO3D_PARAM(P_STRING,  String);               // pressed key;
}


class Widget: public UIElement
{
    public:
        static void RegisterObject(Context* context);
        explicit Widget(Context* context);
        virtual bool HandleKeyDown(InputKey key, int idx){return false;};

    protected:

        virtual void Start(){};

        bool LoadXML(const XMLElement& source) override
        {
            bool success = UIElement::LoadXML(source);
            ASSERT_CPP(success, "load XML failed ");
            Start();
            return success;
        }

        void ApplyAttributes() override
        {
            UIElement::ApplyAttributes();
            Start();
            return;
        }

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
        // only support one line so far
        void AddStringBatch(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor, const String& str, FontFace* face, const Color& color, int dx, int dy, int spacing=1,int gap=-1)
        {
            PODVector<unsigned> unicodeText;
            for (unsigned i = 0; i < str.Length();) unicodeText.Push(str.NextUTF8Char(i));

            AddStringBatch(
                  batches
                , vertexData
                , currentScissor
                , unicodeText
                , face
                , color
                , dx
                , dy
                , spacing
                , gap
                );

        }

        int GetStringLineWidth(const String& str, FontFace* face)
        {
            PODVector<unsigned> unicodeText;
            for (unsigned i = 0; i < str.Length();) unicodeText.Push(str.NextUTF8Char(i));
            return GetStringLineWidth(unicodeText, face);
        }


        int GetStringLineWidth(const PODVector<unsigned>& unicodeText, FontFace* face)
        {
            int width=0;
            for(const auto& c : unicodeText)
            {
                const FontGlyph* glyph = face->GetGlyph(c);
                width += glyph->advanceX_ + glyph->offsetX_;
            }
            return width;
        }


        // NOTE:
        // only support one line so far
        void AddStringBatch(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor, const PODVector<unsigned>& unicodeText, FontFace* face, const Color& color, int dx, int dy,  int spacing=1, int gap=-1)
        {
            {
                auto position = GetPosition();
                auto offsetx = 0;
                // find string offset x y
                const Vector<SharedPtr<Texture2D> >& textures = face->GetTextures();
                for(const auto& c: unicodeText) {
                    const FontGlyph* glyph = face->GetGlyph(c);
                    auto page = glyph->page_;
                    ASSERT_CPP(page < textures.Size(), "page is not correct", page, "/", textures.Size());
                    UIBatch batch(this, BLEND_ALPHA, currentScissor, textures[page], &vertexData);
                    auto transform = Matrix3x4::IDENTITY;
                    transform.SetTranslation(Vector3((float)position.x_+dx+offsetx, (float)position.y_+dy, 0.0f));
                    batch.SetColor(color);

                    const IntVector2& size {glyph->texWidth_, glyph->texHeight_};
                    batch.AddQuad(transform,  glyph->offsetX_, glyph->offsetY_, size.x_, size.y_, glyph->x_, glyph->y_,  size.x_, size.y_);
                    UIBatch::AddOrMerge(batch, batches);

                    offsetx += gap>=0 ? gap : glyph->advanceX_+glyph->offsetX_;
                    offsetx += spacing;
                }
            }
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
