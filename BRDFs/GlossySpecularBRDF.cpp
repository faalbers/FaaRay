#include "BRDFs/GlossySpecularBRDF.hpp"
#include "Render/TraceThread.hpp"

FaaRay::GlossySpecularBRDF::GlossySpecularBRDF()
    : ks_(1.0)
    , cs_(GFA::RGBColor(1.0, 1.0, 1.0))
    , exp_(10.0)
{
}

FaaRay::GlossySpecularBRDF::~GlossySpecularBRDF()
{
}

void FaaRay::GlossySpecularBRDF::setCs(const GFA::RGBColor &c)
{
    cs_ = c;
}

// diffuse color
void FaaRay::GlossySpecularBRDF::setCs(
    const GFA::Scalar &r,
    const GFA::Scalar &g,
    const GFA::Scalar &b)
{
    cs_.r = r; cs_.g = g; cs_.b = b;
}

void FaaRay::GlossySpecularBRDF::setKs(const GFA::Scalar &kd)
{
    ks_ = kd;
}

void FaaRay::GlossySpecularBRDF::setExp(const GFA::Scalar &exp)
{
    exp_ = exp;
}

const GFA::RGBColor & FaaRay::GlossySpecularBRDF::getCd() const
{
    return cs_;
}

GFA::RGBColor FaaRay::GlossySpecularBRDF::rho(FaaRay::TraceThread &ttRef) const
{
    return (cs_*ks_);
}

GFA::RGBColor FaaRay::GlossySpecularBRDF::f(FaaRay::TraceThread &ttRef) const
{
    GFA::Scalar ndotwi, rdotwo;
    GFA::Vector3D r;
    GFA::RGBColor L;

    ndotwi = ttRef.srNormal * ttRef.lDirection;
    r = -ttRef.lDirection + (ttRef.srNormal * ndotwi * 2);
    
    rdotwo = -ttRef.rayDirection * r;

    if (rdotwo > 0.0) L = cs_ * ks_ * pow(rdotwo, exp_);

	return (L);
}
