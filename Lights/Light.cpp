#include "Light.hpp"

// NeedFix: because TraceThread also uses Material
#include "Render/TraceThread.hpp"

FaaRay::Light::Light()
    :   shadows_(false)
{
}

FaaRay::Light::~Light()
{
}

const bool & FaaRay::Light::castsShadows() const
{
    return shadows_;
}

void FaaRay::Light::castShadows(const bool &shadows)
{
    shadows_ = shadows;
}


