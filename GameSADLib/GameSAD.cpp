//
//  GameSAD.cpp
//  GameSADLib
//
//  Created by Fancyzero on 13-7-12.
//  Copyright (c) 2013年 Fancyzero. All rights reserved.
//

#include "GameSAD.h"
#include "GameSADLevel.h"
using namespace cocos2d;

GameSAD::GameSAD()
{
    init_shaders();
    level.reset(new GameSADLevel());

}

bool GameSAD::init_shaders()
{
	CCGLProgram *p = new CCGLProgram();
    p->initWithVertexShaderFilename("shaders/base.vs.fsh", "shaders/base.ps.fsh");
    
    p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
    p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);    
    p->addAttribute(kCCAttributeNameMaskColor, kCCVertexAttrib_MaskColor);
    p->link();
    p->updateUniforms();
    CCShaderCache::sharedShaderCache()->addProgram(p, "base_shader");
    p->release();
    
	p = new CCGLProgram();
    p->initWithVertexShaderFilename("shaders/base.vs.fsh", "shaders/multiply_mask_color.fsh");
    
    p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
    p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    p->addAttribute(kCCAttributeNameMaskColor, kCCVertexAttrib_MaskColor);
    p->link();
    p->updateUniforms();
    CCShaderCache::sharedShaderCache()->addProgram(p, "multiply_mask_shader");
    p->release();
    
    return true;
}