#include "AmbientLight.hpp"
#include "GFA.hpp"
#include "Render/TraceThread.hpp"

FaaRay::AmbientLight::AmbientLight()
    :   ls_(1.0),
        color_(GFA::RGBColor(1.0, 1.0, 1.0))
{
    constructDebug("FaaRay::AmbientLight");
}

FaaRay::AmbientLight::~AmbientLight()
{
    deconstructDebug("FaaRay::AmbientLight");
}

void FaaRay::AmbientLight::setLs(const GFA::Scalar &ls)
{
    ls_ = ls;
}

void  FaaRay::AmbientLight::getLightInfo(FaaRay::TraceThread &ttRef) const
{
    ttRef.lDirection = GFA::Vector3D(0.0, 0.0, 0.0);
}

void  FaaRay::AmbientLight::inShadow(FaaRay::TraceThread &ttRef) const
{
    ttRef.sRayInShadow = false;
}

GFA::RGBColor  FaaRay::AmbientLight::L(FaaRay::TraceThread &ttRef) const
{
    return (color_ * ls_);
}

FaaRay::AmbientLightSPtr FaaRay::MakeAmbientLightSPtr()
{
    return std::make_shared<FaaRay::AmbientLight>();
}


