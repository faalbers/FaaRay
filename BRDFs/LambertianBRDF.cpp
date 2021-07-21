#include "LambertianBRDF.hpp"
#include "GFA.hpp"
#include "Render/TraceThread.hpp"

FaaRay::LambertianBRDF::LambertianBRDF()
    : kd_(1.0)
    , cd_(GFA::RGBColor(1.0, 1.0, 1.0))
{
}

FaaRay::LambertianBRDF::~LambertianBRDF()
{
}

// diffuse color
void FaaRay::LambertianBRDF::setCd(const GFA::RGBColor &c)
{
    cd_ = c;
}

void FaaRay::LambertianBRDF::setCd(
    const GFA::Scalar &r,
    const GFA::Scalar &g,
    const GFA::Scalar &b)
{
    cd_.r = r; cd_.g = g; cd_.b = b;
}

// Diffuse Reflection Coefficient
void FaaRay::LambertianBRDF::setKd(const GFA::Scalar &kd)
{
    kd_ = kd;
}

const GFA::RGBColor & FaaRay::LambertianBRDF::getCd() const
{
    return cd_;
}

GFA::RGBColor FaaRay::LambertianBRDF::rho(FaaRay::TraceThread &ttRef) const
{
    return (cd_*kd_);
}

GFA::RGBColor FaaRay::LambertianBRDF::f(FaaRay::TraceThread &ttRef) const
{
    return (cd_ * kd_ * GFA::invPI);
}
