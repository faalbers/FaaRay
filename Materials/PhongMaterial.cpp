#include "PhongMaterial.hpp"
#include "GFA.hpp"
#include "BRDFs/LambertianBRDF.hpp"
#include "BRDFs/GlossySpecularBRDF.hpp"
#include "Render/TraceThread.hpp"
#include "Lights/Light.hpp"

FaaRay::PhongMaterial::PhongMaterial()
    : ambientBrdfPtr_(new FaaRay::LambertianBRDF)
    , diffuseBrdfPtr_(new FaaRay::LambertianBRDF)
    , specularBrdfPtr_(new FaaRay::GlossySpecularBRDF)
{
    constructDebug("FaaRay::PhongMaterial");
}

FaaRay::PhongMaterial::~PhongMaterial()
{
    deconstructDebug("FaaRay::PhongMaterial");
    delete ambientBrdfPtr_;
    delete diffuseBrdfPtr_;
}

void FaaRay::PhongMaterial::setKa(const GFA::Scalar k)
{
    ambientBrdfPtr_->setKd(k);
}

void FaaRay::PhongMaterial::setKd(const GFA::Scalar k)
{
    diffuseBrdfPtr_->setKd(k);
}

void FaaRay::PhongMaterial::setCd(const GFA::RGBColor &c)
{
    ambientBrdfPtr_->setCd(c);
    diffuseBrdfPtr_->setCd(c);
}

void FaaRay::PhongMaterial::setCd(
            const GFA::Scalar &r,
            const GFA::Scalar &g,
            const GFA::Scalar &b) const
{
    ambientBrdfPtr_->setCd(r, g, b);
    diffuseBrdfPtr_->setCd(r, g, b);
}

void FaaRay::PhongMaterial::setKs(const GFA::Scalar k)
{
    specularBrdfPtr_->setKs(k);
}

void FaaRay::PhongMaterial::setCs(const GFA::RGBColor &c)
{
    specularBrdfPtr_->setCs(c);
}

void FaaRay::PhongMaterial::setExp(const GFA::Scalar exp)
{
    specularBrdfPtr_->setExp(exp);
}


const GFA::RGBColor & FaaRay::PhongMaterial::getDiffuseCd() const
{
    return diffuseBrdfPtr_->getCd();
}

void FaaRay::PhongMaterial::shade(FaaRay::TraceThread &ttRef) const
{
    //ttRef.testBit = (ttRef.x == 256) && (ttRef.y == 256);

    // Ambient BRDF reflectance mult Ambient Light 
    GFA::RGBColor srRhoColor, srAmbientL, srFColor, srFSpecular, srLightL;
    srRhoColor = ambientBrdfPtr_->rho(ttRef);
    srAmbientL = ttRef.ambientLightSPtr->L(ttRef);
    ttRef.srColor = srRhoColor * srAmbientL;
    
    // Add receiving lights.
    GFA::Scalar ndotwi;
    std::vector<FaaRay::LightSPtr> lightSPtrs(ttRef.sceneSPtr->getLightSPtrs());
    for (GFA::Index j = 0; j < lightSPtrs.size(); j++) {
        // get light direction vector from light to hit point
        lightSPtrs[j]->getLightInfo(ttRef);
        // now that the direction is set we can run the BRDF f
        srFColor = diffuseBrdfPtr_->f(ttRef);
        srFSpecular = specularBrdfPtr_->f(ttRef);
        srLightL = lightSPtrs[j]->L(ttRef);
        // get multiplier between light and surface vectors
        ndotwi = ttRef.lDirection * ttRef.srNormal;
        if (ndotwi > 0.0) {
            if (lightSPtrs[j]->castsShadows()) {
                ttRef.sRayOrigin = ttRef.srHitPoint;
                ttRef.sRayDirection = ttRef.lDirection;
                // check if surface point is obscured from the light by any other object
                ttRef.sceneSPtr->shadowHitObjects(ttRef);
            }

            if ( !ttRef.sRayInShadow ) {
                lightSPtrs[j]->L(ttRef);
                ttRef.srColor += (srFColor + srFSpecular) * srLightL * ndotwi;
            }
        }
    }
}

void FaaRay::PhongMaterial::diffuse(FaaRay::TraceThread &ttRef) const
{
}


