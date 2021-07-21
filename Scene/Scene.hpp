
#ifndef __FAARAY_SCENE_H__
#define __FAARAY_SCENE_H__

#include "Base/Base.hpp"
#include "Cameras/Camera.hpp"
#include "Tracers/Tracer.hpp"
#include "Lights/Light.hpp"
#include "GeometricObjects/GeometricObject.hpp"
#include <memory>
#include <vector>

namespace FaaRay {

class Scene : public FaaRay::Base
{
    public:
        Scene();
        ~Scene();

        // Setup methods
        // NeedFix: change shared ptr declarators
        void setCamera(FaaRay::CameraSPtr cameraSPtr);
        void setTracer(FaaRay::TracerSPtr tracerSPtr);
        void setAmbientLight(FaaRay::LightSPtr ambientLightSPtr);
        
        // add methods
        void addObject(FaaRay::GeometricObjectSPtr objectSPtr);
        void addLight(FaaRay::LightSPtr lightSPtr);

        // Retrieving methods
        FaaRay::CameraSPtr              getCameraSPtr() const;
        const FaaRay::Tracer            *getTracerPtr() const;
        FaaRay::TracerSPtr              getTracerSPtr() const;
        FaaRay::ConstTracerSPtr         getConstTracerSPtr() const;
        FaaRay::ConstLightSPtr          getConstAmbientLightSPtr() const;
        std::vector<FaaRay::LightSPtr>  getLightSPtrs() const;

        // ray trace methods
        void hitObjects(FaaRay::TraceThread &ttRef) const;
        void shadowHitObjects(FaaRay::TraceThread &ttRef) const;
    
    private:
        // NeedFix: These are not const, so they could get changed ??
        FaaRay::CameraSPtr                         cameraSPtr_;
        FaaRay::TracerSPtr                         tracerSPtr_;
        FaaRay::LightSPtr                          ambientLightSPtr_;
        std::vector<FaaRay::LightSPtr>             lightSPtrs_;
        std::vector<FaaRay::GeometricObjectSPtr>   objectSPtrs_;
};

typedef std::shared_ptr<Scene>  SceneSPtr;
typedef std::shared_ptr<const Scene>  ConstSceneSPtr;

}

#endif


