#ifndef __FAARAY_TRACETHREAD_H__
#define __FAARAY_TRACETHREAD_H__

#include "Base/Base.hpp"
#include "GFA.hpp"
#include "Scene/Scene.hpp"
#include "Scene/ViewPlane.hpp"
#include "Tracers/Tracer.hpp"
#include "Lights/Light.hpp"
#include "Materials/Material.hpp"
#include <memory>

namespace FaaRay {

class TraceThread : public FaaRay::Base
{
public:
    TraceThread();
    ~TraceThread();

    void render();
    void renderBlock();
    
    void        initRandom(const uint32_t &s);
    GFA::Scalar rand();

    // shared between threads, objects need to be const
    FaaRay::ConstViewPlaneSPtr  viewPlaneSPtr;
    FaaRay::ConstSceneSPtr      sceneSPtr;
    FaaRay::ConstSamplerSPtr    samplerSPtr;
    FaaRay::ConstTracerSPtr     tracerSPtr;
    FaaRay::ConstLightSPtr      ambientLightSPtr;
    
    GFA::Index      x;
    GFA::Index      y;
    GFA::Index      blockStart;
    GFA::Index      blockEnd;

    GFA::RGBColor   color;
    uint32_t        seedVal;
    
    // optimization variables

    // test variable
    bool            testBit;

    // viewplane data
    GFA::Size       width;
    GFA::Size       height;
    GFA::Scalar     halfWidth;
    GFA::Scalar     halfHeight;
    GFA::Scalar     pixelSize;
    
    // sample data
    GFA::Index      sampleIndex;
    GFA::Index      sampleSetIndex;
    GFA::Point2D    sampleUnitSquare;
    GFA::Point2D    samplePoint;
    
    // ray data
    GFA::Point3D    rayOrigin;
    GFA::Normal     rayDirection;

    // shadow ray data
    GFA::Point3D    sRayOrigin;
    GFA::Vector3D   sRayDirection;
    bool            sRayInShadow;

    // Surface data
    GFA::Normal                 srNormal;
    GFA::Point3D                srHitPoint;
    GFA::RGBColor               srColor;
    bool                        srHitAnObject;
    FaaRay::ConstMaterialSPtr   srMaterialSPtr; // gets changed per hit point

    // light data
    GFA::Normal     lDirection;
    GFA::Scalar     lDistance;
    
private:
    uint32_t        seedValue_;
    FaaRay::MyRNG   rng_;
    std::uniform_real_distribution<GFA::Scalar> distribution;  
};

typedef std::shared_ptr<TraceThread> TraceThreadSPtr;
typedef std::shared_ptr<const TraceThread> ConstTraceThreadSPtr;

}

#endif

