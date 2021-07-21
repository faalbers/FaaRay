#ifndef __FAARAY_LIGHT_H__
#define __FAARAY_LIGHT_H__

#include "Base/Base.hpp"
#include "GFA.hpp"

namespace FaaRay {

// forward decleration because TraceThread also Light
class TraceThread;

class Light : public  FaaRay::Base
{
public:
    Light();
    virtual ~Light();

    virtual void getLightInfo( FaaRay::TraceThread &ttRef) const = 0;
    virtual GFA::RGBColor L(FaaRay::TraceThread &ttRef) const = 0;
    virtual void inShadow( FaaRay::TraceThread &ttRef) const = 0;

    const bool & castsShadows() const;
    void castShadows(const bool &shadows);

protected:
    bool    shadows_;
};

typedef std::shared_ptr<Light> LightSPtr;
typedef std::shared_ptr<const Light> ConstLightSPtr;

}

#endif

