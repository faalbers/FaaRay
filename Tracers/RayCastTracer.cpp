
#include "RayCastTracer.hpp"
#include "GFA.hpp"
#include "Render/TraceThread.hpp"

FaaRay::RayCastTracer::RayCastTracer()
{
    constructDebug("RayCastTracer");
}

FaaRay::RayCastTracer::~RayCastTracer()
{
    deconstructDebug("RayCastTracer");
}

void FaaRay::RayCastTracer::traceRay(FaaRay::TraceThread &ttRef) const
{
    ttRef.sceneSPtr->hitObjects(ttRef);
    if(ttRef.srHitAnObject) {
        if ( ttRef.srMaterialSPtr.use_count() != 0) {
            ttRef.srMaterialSPtr->shade(ttRef);
        } else {
            ttRef.srColor = GFA::RGBColor(1, 0, 0, 1);
        }
    } else {
        ttRef.srColor.r = 0.0; ttRef.srColor.g = 0.0; ttRef.srColor.b = 0.0;
    // NeedFix: Does Alpha need to be 0 ?
        ttRef.srColor.a = 0.0;
    }
}

FaaRay::RayCastTracerSPtr FaaRay::MakeRayCastTracerSPtr()
{
    return std::make_shared<FaaRay::RayCastTracer>();
}


