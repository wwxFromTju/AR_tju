/**
* Copyright (c) 2015 VisionStar Information Technology (Shanghai) Co., Ltd. All Rights Reserved.
* EasyAR is the registered trademark or trademark of VisionStar Information Technology (Shanghai) Co., Ltd in China
* and other countries for the augmented reality technology developed by VisionStar Information Technology (Shanghai) Co., Ltd.
*/

#ifndef __EASYAR_AUGMENTER_HPP__
#define __EASYAR_AUGMENTER_HPP__

#include "easyar/base.hpp"
#include "easyar/matrix.hpp"
#include "easyar/image.hpp"

namespace EasyAR{

class ImageTracker;
class BarCodeScanner;
class Frame;

class Augmenter : public RefBase
{
public:
    enum API
    {
        kAugmenterAPIDefault,
        kAugmenterAPINONE,
        kAugmenterAPIGLES2,
        kAugmenterAPIGL,
        kAugmenterAPID3D9,
        kAugmenterAPID3D11,
    };
    Augmenter();
    virtual ~Augmenter();

    void chooseAPI(API api = kAugmenterAPIDefault, void* device = 0);
    Frame newFrame(const ImageTracker& obj);
    Frame newFrame(const BarCodeScanner& obj);
    void setViewPort(const Vec4I& viewport);
    Vec4I viewPort() const;
    bool drawVideoBackground();

    Vec2I videoBackgroundTextureSize();
    PixelFormat videoBackgroundTextureFormat();
    bool setVideoBackgroundTextureID(int id);
    bool setVideoBackgroundTextureID(void* id);
    bool retrieveVideoBackground(int id);
    bool retrieveVideoBackground(void* id);

    int id() const;
};

}
#endif
