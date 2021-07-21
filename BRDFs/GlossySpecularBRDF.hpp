#ifndef __FAARAY_GLOSSYSPECULARBRDF_H__
#define __FAARAY_GLOSSYSPECULARBRDF_H__

#include "BRDF.hpp"
#include "GFA.hpp"
#include "Render/TraceThread.hpp"

namespace FaaRay {

class GlossySpecularBRDF : public FaaRay::BRDF
{
public:
    GlossySpecularBRDF();
    virtual ~GlossySpecularBRDF();

    void setCs(const GFA::RGBColor &c);
    void setCs(
        const GFA::Scalar &r,
        const GFA::Scalar &g,
        const GFA::Scalar &b);
    void setKs(const GFA::Scalar &ks);
    void setExp(const GFA::Scalar &exp);
        
    const GFA::RGBColor & getCd() const;
    
    virtual GFA::RGBColor rho(FaaRay::TraceThread &ttRef) const;
    virtual GFA::RGBColor f(FaaRay::TraceThread &ttRef) const;
    
private:
    GFA::RGBColor   cs_;    // Specular color
    GFA::Scalar     ks_;    // Diffuse Reflection Coefficient
    GFA::Scalar     exp_;   // Specular Exponent
};

}

#endif

