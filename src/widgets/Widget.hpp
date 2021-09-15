#pragma once

#include "../utils/log.hpp"
#include "../Global.h"
 
namespace Urho3D
{

class Widget: public UIElement
{
    public:
        Widget(Context* context) : UIElement(context) {}
        virtual bool HandleKeyDown(InputKey key)=0;

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
            if(w <0 || h<0) 
            {
                batch.AddQuad(transform, 0, 0, size.x_, size.y_, 0, 0, size.x_, size.y_);
            }
            else 
            {
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

            if(w<0 || h<0)
            {
                batch.AddQuad(transform, 0, 0, size.x_, size.y_, glyph->x_, glyph->y_,  size.x_, size.y_);
            }
            else
            {
                auto offsetx=(w-size.x_)/2;
                auto offsety=(h-size.y_)/2;
                batch.AddQuad(transform, offsetx, offsety, size.x_, size.y_, glyph->x_, glyph->y_,  size.x_, size.y_);
            }

            UIBatch::AddOrMerge(batch, batches);
        }

};

}
