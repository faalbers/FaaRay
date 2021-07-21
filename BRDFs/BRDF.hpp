#ifndef __FAARAY_BRDF_H__
#define __FAARAY_BRDF_H__

#include "GFA.hpp"
#include "Render/TraceThread.hpp"

namespace FaaRay {

class BRDF
{
    public:
        BRDF();
        virtual ~BRDF();
        
        virtual GFA::RGBColor rho(FaaRay::TraceThread &ttRef) const = 0;
        virtual GFA::RGBColor f(FaaRay::TraceThread &ttRef) const = 0;
};

}

#endif

