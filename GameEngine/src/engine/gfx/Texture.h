#pragma once  
#include <string>  
#include "engine/io/Asset.h"  

class Texture : public Asset {  
public:  
   Texture(const std::string& path);  
   ~Texture();  

   bool load() override; 
   AssetType getType() const override { return AssetType::Texture; }

   void bind(unsigned int slot = 0) const;  
   void unbind(unsigned int slot = 0) const;  

   unsigned int getWidth() const {  
       return m_Width;  
   }  

   unsigned int getHeight() const {  
       return m_Height;  
   }  

private:  
   unsigned int m_Width = 0;  
   unsigned int m_Height = 0;  
   unsigned int m_TextureId = 0;  
   unsigned int m_RendererID = 0;  
};
