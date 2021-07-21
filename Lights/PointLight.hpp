#ifndef __FAARAY_POINTLIGHT_H__
#define __FAARAY_POINTLIGHT_H__

#include "Lights/Light.hpp"
#include "GFA.hpp"
#include "Render/TraceThread.hpp"
#include <memory>

namespace FaaRay {

class PointLight : public FaaRay::Light
{
public:
    PointLight();
    virtual ~PointLight();

    void setCenter(
        const GFA::Scalar &x,
        const GFA::Scalar &y,
        const GFA::Scalar &z);

    virtual void getLightInfo(FaaRay::TraceThread &ttRef) const;
    virtual GFA::RGBColor L(FaaRay::TraceThread &ttRef) const;
    virtual void inShadow(FaaRay::TraceThread &ttRef) const;    

    void setRadiance(const GFA::Scalar b) { ls_ = b; }
    void setColor(const GFA::RGBColor color) { color_ = color; }

private:
    GFA::Point3D    center_; // center point of the point light
    GFA::Scalar     ls_;     // light strength
    GFA::RGBColor   color_;  // light color
};

typedef std::shared_ptr<PointLight>  PointLightSPtr;
PointLightSPtr MakePointLightSPtr();

}

#endif

