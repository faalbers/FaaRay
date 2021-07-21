#ifndef __FAARAY_AMBIENTLIGHT_H__
#define __FAARAY_AMBIENTLIGHT_H__

#include "Light.hpp"
#include "GFA.hpp"
#include "Render/TraceThread.hpp"
#include <memory>

namespace FaaRay {

class AmbientLight : public FaaRay::Light
{
public:
    AmbientLight();
    virtual ~AmbientLight();

    virtual void getLightInfo(FaaRay::TraceThread &ttRef) const;
    virtual GFA::RGBColor L(FaaRay::TraceThread &ttRef) const;
    virtual void inShadow(FaaRay::TraceThread &ttRef) const;    
    
    void setLs(const GFA::Scalar &ls);

private:
    GFA::Scalar     ls_;     // light strength
    GFA::RGBColor   color_;  // light color
};

typedef std::shared_ptr<AmbientLight>  AmbientLightSPtr;
AmbientLightSPtr MakeAmbientLightSPtr();

}

#endif

