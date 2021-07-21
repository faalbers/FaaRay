
#include "Scene.hpp"
#include "GFA.hpp"
#include "Cameras/Camera.hpp"
#include "Render/TraceThread.hpp"
#include "Lights/Light.hpp"
#include "GeometricObjects/GeometricObject.hpp"
#include "Tracers/Tracer.hpp"
#include <vector>

FaaRay::Scene::Scene()
    : cameraSPtr_(nullptr)
    , tracerSPtr_(nullptr)
    , ambientLightSPtr_(nullptr)
{
    constructDebug("FaaRay::Scene");
}

FaaRay::Scene::~Scene()
{
    sPtrDebug("FaaRay::Scene::cameraSPtr_", cameraSPtr_);
    sPtrDebug("FaaRay::Scene::tracerSPtr_", tracerSPtr_);
    sPtrDebug("FaaRay::Scene::ambientLightSPtr_", ambientLightSPtr_);
    for (GFA::Index j = 0; j < objectSPtrs_.size(); j++)
        sPtrDebug("FaaRay::Scene::objectSPtrs_", objectSPtrs_[j], j);
    for (GFA::Index j = 0; j < lightSPtrs_.size(); j++)
        sPtrDebug(("FaaRay::Scene::lightSPtrs_"), lightSPtrs_[j], j);
    deconstructDebug("FaaRay::Scene");
}

void FaaRay::Scene::setCamera(FaaRay::CameraSPtr cameraSPtr)
{
    cameraSPtr_ = cameraSPtr;
    cameraSPtr_->computeUVW();
}

void FaaRay::Scene::setTracer(FaaRay::TracerSPtr tracerSPtr)
{
    tracerSPtr_ = tracerSPtr;
}

void FaaRay::Scene::setAmbientLight(FaaRay::LightSPtr ambientLightSPtr)
{
    ambientLightSPtr_ = ambientLightSPtr;
}

void FaaRay::Scene::addLight(FaaRay::LightSPtr lightSPtr)
{                                       
    lightSPtrs_.push_back(lightSPtr);
}

void FaaRay::Scene::addObject(FaaRay::GeometricObjectSPtr objectSPtr)
{                                       
    objectSPtrs_.push_back(objectSPtr);
}

FaaRay::CameraSPtr FaaRay::Scene::getCameraSPtr() const
{
    return cameraSPtr_;
}

const FaaRay::Tracer * FaaRay::Scene::getTracerPtr() const
{
    return tracerSPtr_.get();
}

FaaRay::TracerSPtr FaaRay::Scene::getTracerSPtr() const
{
    return tracerSPtr_;
}

FaaRay::ConstTracerSPtr FaaRay::Scene::getConstTracerSPtr() const
{
    return tracerSPtr_;
}

FaaRay::ConstLightSPtr FaaRay::Scene::getConstAmbientLightSPtr() const
{
    return ambientLightSPtr_;
}

std::vector<FaaRay::LightSPtr> FaaRay::Scene::getLightSPtrs() const
{
    return lightSPtrs_;
}

void FaaRay::Scene::hitObjects(FaaRay::TraceThread &ttRef) const
{
    GFA::Scalar t;
    GFA::Normal srNormal, srNormalmin;
    GFA::Scalar tmin = GFA::HUGE_SCALAR;
    GFA::Index  closestHit = 0;

    // Find closest hit
    ttRef.srHitAnObject = false;
    for (GFA::Index j = 0; j < objectSPtrs_.size(); j++) {
        if (objectSPtrs_[j]->hit(ttRef, t, srNormal) && (t < tmin)) {
            closestHit = j;
            tmin = t;
            srNormalmin = srNormal;
            ttRef.srHitAnObject = true;
        }
    }

    if (ttRef.srHitAnObject) {
        ttRef.srMaterialSPtr = objectSPtrs_[closestHit]->getMaterialSPtr();
        ttRef.srHitPoint = ttRef.rayOrigin + ttRef.rayDirection * tmin;
        ttRef.srNormal = srNormalmin;
    }
}

void FaaRay::Scene::shadowHitObjects(FaaRay::TraceThread &ttRef) const
{
    GFA::Scalar t;

    for (GFA::Index j = 0; j < objectSPtrs_.size(); j++) {
        if ( objectSPtrs_[j]->shadowHit(ttRef, t) ) {
            if ( t <= ttRef.lDistance ) {
                ttRef.sRayInShadow = true;
                return;
            }
        }
    }
    ttRef.sRayInShadow = false;
}

/*
            bool inShadow = false;
            
            if ( sr.world.lights[j]->castsShadows() ) {
                Ray shadowRay(sr.hitPoint, wi);
                inShadow = sr.world.lights[j]->inShadow(shadowRay, sr);
            }
            if (!inShadow) 
                L += diffuseBrdf->f(sr, wi, wo) * sr.world.lights[j]->L(sr) * ndotwi;
*/

/*
    for (GFA::Index j = 0; j < numLights; j++) {
        GFA::Vector3D wi = sr.world.lights[j]->getDirection(sr);
        double ndotwi = wi * sr.normal;
        
        if (ndotwi > 0.0) {
            bool inShadow = false;
            
            if ( sr.world.lights[j]->castsShadows() ) {
                Ray shadowRay(sr.hitPoint, wi);
                inShadow = sr.world.lights[j]->inShadow(shadowRay, sr);
            }
            if (!inShadow) 
                L += diffuseBrdf->f(sr, wi, wo) * sr.world.lights[j]->L(sr) * ndotwi;
        }
    }
*/
