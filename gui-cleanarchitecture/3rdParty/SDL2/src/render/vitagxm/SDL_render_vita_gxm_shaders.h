/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2021 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef SDL_RENDER_VITA_GXM_SHADERS_H
#define SDL_RENDER_VITA_GXM_SHADERS_H

#include <psp2/gxm.h>

#define gxm_shader_clear_f_size 232
static const unsigned char gxm_shader_clear_f[gxm_shader_clear_f_size] = {
    0x47, 0x58, 0x50, 0x00, 0x01, 0x05, 0x50, 0x03, 
    0xe8, 0x00, 0x00, 0x00, 0xa2, 0x55, 0x22, 0x3e, 
    0xc6, 0x7e, 0x77, 0xf1, 0x01, 0x00, 0x18, 0x00, 
    0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
    0xa4, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 
    0x02, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 
    0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x68, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 
    0x5c, 0x00, 0x00, 0x00, 0xc0, 0x3d, 0x03, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 
    0x01, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x07, 0x44, 0xfa, 0x02, 0x80, 0x19, 0xf0, 
    0x7e, 0x0d, 0x80, 0x40, 0x0e, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 
    0x01, 0xe4, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x75, 0x43, 0x6c, 0x65, 
    0x61, 0x72, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x00, 
};

#define gxm_shader_clear_v_size 252
static const unsigned char gxm_shader_clear_v[gxm_shader_clear_v_size] = {
    0x47, 0x58, 0x50, 0x00, 0x01, 0x05, 0x50, 0x03, 
    0xfa, 0x00, 0x00, 0x00, 0xdc, 0x25, 0x34, 0x74, 
    0x53, 0x4a, 0x7a, 0x5b, 0x04, 0x00, 0x19, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
    0xb8, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x74, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x78, 0x00, 0x00, 0x00, 0xc0, 0x3d, 0x03, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x6c, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x5c, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x4c, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x04, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x44, 0xfa, 
    0x01, 0x00, 0x04, 0x90, 0x85, 0x11, 0xa5, 0x08, 
    0x01, 0x80, 0x56, 0x90, 0x81, 0x11, 0x83, 0x08, 
    0x00, 0x00, 0x20, 0xa0, 0x00, 0x50, 0x27, 0xfb, 
    0x10, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x61, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 
    0x6e, 0x00, 0x00, 0x00, 
};

#define gxm_shader_color_f_size 212
static const unsigned char gxm_shader_color_f[gxm_shader_color_f_size] = {
    0x47, 0x58, 0x50, 0x00, 0x01, 0x05, 0x50, 0x03, 
    0xd4, 0x00, 0x00, 0x00, 0x9c, 0xd6, 0x9b, 0xf7, 
    0x78, 0x00, 0x5d, 0x31, 0x01, 0x10, 0x18, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0xac, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 
    0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x78, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x6c, 0x00, 0x00, 0x00, 0xc0, 0x3d, 0x03, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 
    0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 
    0x0f, 0xa0, 0xd0, 0x0e, 0x00, 0x00, 0x00, 0x00, 
    0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x07, 0x44, 0xfa, 0x02, 0x80, 0x19, 0xa0, 
    0x7e, 0x0d, 0x80, 0x40, 
};

#define gxm_shader_color_v_size 368
static const unsigned char gxm_shader_color_v[gxm_shader_color_v_size] = {
    0x47, 0x58, 0x50, 0x00, 0x01, 0x05, 0x50, 0x03, 
    0x6d, 0x01, 0x00, 0x00, 0x09, 0xce, 0x4e, 0xc2, 
    0xe1, 0xcd, 0x24, 0xbc, 0x00, 0x00, 0x19, 0x00, 
    0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
    0x00, 0x01, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 
    0x08, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x01, 0x00, 0x09, 0x00, 0x00, 0x00, 
    0x98, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
    0x74, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 
    0xb8, 0x00, 0x00, 0x00, 0xc0, 0x3d, 0x03, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0xac, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0xac, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x9c, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x94, 0x00, 0x00, 0x00, 
    0x01, 0x00, 0x00, 0x00, 0x8c, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0xf3, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x19, 0x00, 0x09, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x06, 0x43, 0x00, 0x61, 
    0x86, 0x81, 0xa2, 0x00, 0x07, 0x53, 0x40, 0x61, 
    0x86, 0x81, 0xa2, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x40, 0x01, 0x04, 0xf8, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x44, 0xfa, 
    0x80, 0x00, 0x08, 0x83, 0x21, 0x1d, 0x80, 0x38, 
    0x00, 0x00, 0xf0, 0x83, 0x20, 0x0d, 0x80, 0x38, 
    0x0a, 0x84, 0xb9, 0xff, 0xbc, 0x0d, 0xc0, 0x40, 
    0x02, 0x11, 0x45, 0xcf, 0x80, 0x8f, 0xb1, 0x18, 
    0x00, 0x11, 0x01, 0xc0, 0x81, 0x81, 0xb1, 0x18, 
    0x01, 0xd1, 0x42, 0xc0, 0x81, 0x81, 0xb1, 0x18, 
    0x40, 0x00, 0x10, 0x41, 0x09, 0x05, 0x82, 0x38, 
    0x00, 0x00, 0x20, 0xa0, 0x00, 0x50, 0x27, 0xfb, 
    0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 
    0x30, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x2a, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 
    0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 
    0x21, 0x00, 0x00, 0x00, 0x01, 0xe4, 0x00, 0x00, 
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x61, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 
    0x6e, 0x00, 0x61, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 
    0x00, 0x77, 0x76, 0x70, 0x00, 0x00, 0x00, 0x00, 
};

#define gxm_shader_texture_f_size 288
static const unsigned char gxm_shader_texture_f[gxm_shader_texture_f_size] = {
    0x47, 0x58, 0x50, 0x00, 0x01, 0x05, 0x50, 0x03, 
    0x20, 0x01, 0x00, 0x00, 0xeb, 0x4f, 0xb5, 0xba, 
    0x60, 0xb2, 0xd0, 0x8d, 0x05, 0x18, 0x18, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 
    0xc4, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 
    0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x01, 0x00, 0x05, 0x00, 0x00, 0x00, 
    0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x78, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x84, 0x00, 0x00, 0x00, 0xc0, 0x3d, 0x03, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 
    0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 
    0x01, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00, 
    0x00, 0xa9, 0xd0, 0x0e, 0x00, 0x00, 0x00, 0x00, 
    0xf0, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x07, 0x44, 0xfa, 0x00, 0x00, 0x00, 0x00, 
    0x40, 0x09, 0x00, 0xf8, 0x02, 0x80, 0x99, 0xaf, 
    0xbc, 0x0d, 0xc0, 0x40, 0x06, 0x82, 0xb9, 0xaf, 
    0xbc, 0x0d, 0x80, 0x40, 0x7c, 0x0f, 0x04, 0x00, 
    0x86, 0x47, 0xa4, 0x10, 0x30, 0x00, 0x00, 0x00, 
    0x02, 0x04, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x74, 0x65, 0x78, 0x00, 
};

#define gxm_shader_texture_v_size 400
static const unsigned char gxm_shader_texture_v[gxm_shader_texture_v_size] = {
    0x47, 0x58, 0x50, 0x00, 0x01, 0x05, 0x50, 0x03, 
    0x8f, 0x01, 0x00, 0x00, 0x60, 0x1e, 0x69, 0x97, 
    0x82, 0x7e, 0x0c, 0xac, 0x00, 0x00, 0x19, 0x00, 
    0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 
    0x08, 0x01, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 
    0x0c, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x01, 0x00, 0x0a, 0x00, 0x00, 0x00, 
    0x98, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 
    0x74, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 
    0xc0, 0x00, 0x00, 0x00, 0xc0, 0x3d, 0x03, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0xb4, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0xb4, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0xa4, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x9c, 0x00, 0x00, 0x00, 
    0x01, 0x00, 0x00, 0x00, 0x94, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x33, 0x0f, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x0a, 
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x06, 0x43, 0x00, 0x61, 
    0x86, 0x81, 0xa2, 0x00, 0x07, 0x53, 0x40, 0x61, 
    0x86, 0x81, 0xa2, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x40, 0x01, 0x04, 0xf8, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x44, 0xfa, 
    0x01, 0x0e, 0x01, 0x01, 0x02, 0x00, 0x10, 0xfa, 
    0x80, 0x00, 0x08, 0x83, 0x21, 0x25, 0x80, 0x38, 
    0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x14, 0xfa, 
    0x00, 0x00, 0xf0, 0x83, 0x20, 0x0d, 0x80, 0x38, 
    0x0a, 0x84, 0xb9, 0xff, 0xbc, 0x0d, 0xc0, 0x40, 
    0x02, 0x11, 0x45, 0xcf, 0x80, 0x8f, 0xb1, 0x18, 
    0x00, 0x11, 0x01, 0xc0, 0x81, 0x81, 0xb1, 0x18, 
    0x01, 0xd1, 0x42, 0xc0, 0x81, 0x81, 0xb1, 0x18, 
    0x00, 0x00, 0x20, 0xa0, 0x00, 0x50, 0x27, 0xfb, 
    0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 
    0x40, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x3a, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 
    0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 
    0x34, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 
    0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 
    0x2b, 0x00, 0x00, 0x00, 0x01, 0xe4, 0x00, 0x00, 
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x61, 0x50, 0x6f, 0x73, 0x69, 0x74, 0x69, 0x6f, 
    0x6e, 0x00, 0x61, 0x54, 0x65, 0x78, 0x63, 0x6f, 
    0x6f, 0x72, 0x64, 0x00, 0x61, 0x43, 0x6f, 0x6c, 
    0x6f, 0x72, 0x00, 0x77, 0x76, 0x70, 0x00, 0x00, 
};

static const SceGxmProgram *const clearVertexProgramGxp         = (const SceGxmProgram *)gxm_shader_clear_v;
static const SceGxmProgram *const clearFragmentProgramGxp       = (const SceGxmProgram *)gxm_shader_clear_f;
static const SceGxmProgram *const colorVertexProgramGxp         = (const SceGxmProgram *)gxm_shader_color_v;
static const SceGxmProgram *const colorFragmentProgramGxp       = (const SceGxmProgram *)gxm_shader_color_f;
static const SceGxmProgram *const textureVertexProgramGxp       = (const SceGxmProgram *)gxm_shader_texture_v;
static const SceGxmProgram *const textureFragmentProgramGxp     = (const SceGxmProgram *)gxm_shader_texture_f;

#endif // SDL_RENDER_VITA_GXM_SHADERS_H

/* vi: set ts=4 sw=4 expandtab: */
