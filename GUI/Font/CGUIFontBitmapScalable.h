// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h
// Sep 11, 2014; Jonathan Frisch
 
#ifndef __C_GUI_FONT_BITMAP_RESIZABLE_H_INCLUDED__
#define __C_GUI_FONT_BITMAP_RESIZABLE_H_INCLUDED__
 
#include "irrlicht.h"
#ifdef _IRR_COMPILE_WITH_GUI_
 
namespace irr
{
 
namespace video
{
    class IVideoDriver;
    class IImage;
}
 
namespace gui
{
 
    class IGUIEnvironment;
 
class CGUIFontBitmapScalable : public IGUIFontBitmap
{
public:
 
    //! constructor
    CGUIFontBitmapScalable(IGUIEnvironment* env, const io::path& filename, ILogger* logger = NULL);
 
    //! destructor
    virtual ~CGUIFontBitmapScalable();
 
    //! loads a font from a texture file
    bool load(const io::path& filename);
 
    //! loads a font from a texture file
    bool load(io::IReadFile* file);
 
    //! loads a font from an XML file
    //\param directory Directory in which the bitmaps can be found
    bool load(io::IXMLReader* xml, const io::path& directory);
 
    //! draws an text and clips it to the specified rectangle if wanted
    virtual void draw(const core::stringw& text, const core::rect<s32>& position,
            video::SColor color, bool hcenter=false,
            bool vcenter=false, const core::rect<s32>* clip=0) _IRR_OVERRIDE_;
 
    //! returns the dimension of a text
    virtual core::dimension2d<u32> getDimension(const wchar_t* text) const _IRR_OVERRIDE_;
 
    //! Calculates the index of the character in the text which is on a specific position.
    virtual s32 getCharacterFromPos(const wchar_t* text, s32 pixel_x) const _IRR_OVERRIDE_;
 
    //! Returns the type of this font
    virtual EGUI_FONT_TYPE getType() const _IRR_OVERRIDE_ { return EGFT_BITMAP; }
 
    //! set an Pixel Offset on Drawing ( scale position on width )
    virtual void setKerningWidth (s32 kerning) _IRR_OVERRIDE_;
    virtual void setKerningHeight (s32 kerning) _IRR_OVERRIDE_;
 
    //! set an Pixel Offset on Drawing ( scale position on width )
    virtual s32 getKerningWidth(const wchar_t* thisLetter=0, const wchar_t* previousLetter=0) const _IRR_OVERRIDE_;
    virtual s32 getKerningHeight() const _IRR_OVERRIDE_;
 
    //! gets the sprite bank
    virtual IGUISpriteBank* getSpriteBank() const _IRR_OVERRIDE_;
 
    //! returns the sprite number from a given character
    virtual u32 getSpriteNoFromChar(const wchar_t *c) const _IRR_OVERRIDE_;
 
    virtual void setInvisibleCharacters( const wchar_t *s ) _IRR_OVERRIDE_;
 
    virtual f32 getFontScale() { return fontScale; }
 
    virtual void setFontScale(f32 scale) { fontScale = scale; }
 
    virtual void setBaseFontScale(f32 baseScale) { baseFontScale = baseScale; }
 
private:
 
    struct SFontArea
    {
        SFontArea() : underhang(0), overhang(0), width(0), spriteno(0) {}
        s32             underhang;
        s32             overhang;
        s32             width;
        s32             height;
        u32             spriteno;
    };
 
    //! load & prepare font from ITexture
    bool loadTexture(video::IImage * image, const io::path& name);
 
    void readPositions(video::IImage* texture, s32& lowerRightPositions);
 
    s32 getAreaFromCharacter (const wchar_t c) const;
    void setMaxHeight();
 
    core::array<SFontArea>      Areas;
    core::map<wchar_t, s32>     CharacterMap;
    video::IVideoDriver*        Driver;
    IGUISpriteBank*         SpriteBank;
    IGUIEnvironment*        Environment;
    ILogger* Logger;
    f32 fontScale, baseFontScale;
    u32             WrongCharacter;
    s32             MaxHeight;
    s32             GlobalKerningWidth, GlobalKerningHeight;
 
    core::stringw Invisible;
};
 
} // end namespace gui
} // end namespace irr
 
#endif // _IRR_COMPILE_WITH_GUI_
 
#endif // __C_GUI_FONT_BITMAP_RESIZABLE_H_INCLUDED__
