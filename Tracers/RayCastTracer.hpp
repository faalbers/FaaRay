#ifndef __FAARAY_RAYCASTTRACER_H__
#define __FAARAY_RAYCASTTRACER_H__

#include "Tracer.hpp"
#include "Render/TraceThread.hpp"
#include <memory>

namespace FaaRay {
    
class RayCastTracer : public FaaRay::Tracer
{
    public:
        RayCastTracer();
        ~RayCastTracer();

        virtual void traceRay(FaaRay::TraceThread &ttRef) const;
};
                                  
typedef std::shared_ptr<RayCastTracer>  RayCastTracerSPtr;
RayCastTracerSPtr MakeRayCastTracerSPtr();

}

#endif


