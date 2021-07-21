#ifndef __FAARAY_PHONGMATERIAL_H__
#define __FAARAY_PHONGMATERIAL_H__

#include "Materials/Material.hpp"
#include "GFA.hpp"
#include "BRDFs/LambertianBRDF.hpp"
#include "BRDFs/GlossySpecularBRDF.hpp"
#include "Render/TraceThread.hpp"
#include <memory>

namespace FaaRay {

class PhongMaterial : public FaaRay::Material
{
    public:
        PhongMaterial();
        virtual ~PhongMaterial();

        void setKa(const GFA::Scalar k);
        
        void setKd(const GFA::Scalar k);
        void setCd(const GFA::RGBColor &c);
        void setCd(
            const GFA::Scalar &r,
            const GFA::Scalar &g,
            const GFA::Scalar &b) const;
        
        void setKs(const GFA::Scalar k);
        void setCs(const GFA::RGBColor &c);
        void setExp(const GFA::Scalar exp);

        virtual const GFA::RGBColor & getDiffuseCd() const;
        virtual void shade(FaaRay::TraceThread &ttRef) const;
        virtual void diffuse(FaaRay::TraceThread &ttRef) const;
        
    private:
        FaaRay::LambertianBRDF      *ambientBrdfPtr_;
        FaaRay::LambertianBRDF      *diffuseBrdfPtr_;
        FaaRay::GlossySpecularBRDF  *specularBrdfPtr_;
};

typedef std::shared_ptr<PhongMaterial>  PhongMaterialSPtr;
typedef std::shared_ptr<const PhongMaterial>  ConstPhongMaterialSPtr;

}

#endif

