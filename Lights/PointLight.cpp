#include "PointLight.hpp"
#include "GFA.hpp"
#include "Render/TraceThread.hpp"

FaaRay::PointLight::PointLight()
    :   ls_(1.0),
        color_(GFA::RGBColor(1.0, 1.0, 1.0))
{
    constructDebug("FaaRay::PointLight");
}

FaaRay::PointLight::~PointLight()
{
    deconstructDebug("FaaRay::PointLight");
}

void FaaRay::PointLight::setCenter(
    const GFA::Scalar &x,
    const GFA::Scalar &y,
    const GFA::Scalar &z)
{
    center_.x = x;
    center_.y = y;
    center_.z = z;
}

void  FaaRay::PointLight::getLightInfo(FaaRay::TraceThread &ttRef) const
{
    GFA::Vector3D lVector = center_ - ttRef.srHitPoint;
    ttRef.lDirection = lVector;
    ttRef.lDistance = lVector.length();
} 

void  FaaRay::PointLight::inShadow(FaaRay::TraceThread &ttRef) const
{
    if ( castsShadows() ) {
        ttRef.sRayInShadow = false;
    } else
        ttRef.sRayInShadow = false;
}

GFA::RGBColor FaaRay::PointLight::L(FaaRay::TraceThread &ttRef) const
{
    return (color_ * ls_);
}

void FaaRay::PointLight::setColor(const GFA::Scalar &r, const GFA::Scalar &g, const GFA::Scalar &b)
{
    color_.r = r; color_.g = g; color_.b = b; color_.a = 1.0; 
}

FaaRay::PointLightSPtr FaaRay::MakePointLightSPtr()
{
    return std::make_shared<FaaRay::PointLight>();
}

/*
    double t;
    int numObjects = sr.world.objects.size();
    double d = location.distance(ray.origin);

    for (int j = 0; j < numObjects; j++)
        if (sr.world.objects[j]->shadowHit(ray, t) && t < d)
            return true;
    
    return false;
*/
