#ifndef __FAARAY_LAMBERTIANBRDF_H__
#define __FAARAY_LAMBERTIANBRDF_H__

#include "BRDF.hpp"
#include "GFA.hpp"
#include "Render/TraceThread.hpp"

namespace FaaRay {

class LambertianBRDF : public FaaRay::BRDF
{
public:
    LambertianBRDF();
    virtual ~LambertianBRDF();

    void setCd(const GFA::RGBColor &c);
    void setCd(
        const GFA::Scalar &r,
        const GFA::Scalar &g,
        const GFA::Scalar &b);
    void setKd(const GFA::Scalar &kd);
        
    const GFA::RGBColor & getCd() const;
    
    virtual GFA::RGBColor rho(FaaRay::TraceThread &ttRef) const;
    virtual GFA::RGBColor f(FaaRay::TraceThread &ttRef) const;
    
private:
    GFA::RGBColor   cd_;    // diffuse color
    GFA::Scalar     kd_;    // Diffuse Reflection Coefficient
};

}

#endif

