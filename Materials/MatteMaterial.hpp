#ifndef __FAARAY_MATTEMATERIAL_H__
#define __FAARAY_MATTEMATERIAL_H__

#include "Materials/Material.hpp"
#include "GFA.hpp"
#include "BRDFs/LambertianBRDF.hpp"
#include "Render/TraceThread.hpp"

#include <memory>

namespace FaaRay {

class MatteMaterial : public FaaRay::Material
{
    public:
        MatteMaterial();
        virtual ~MatteMaterial();

        void setKd(const GFA::Scalar k);
        void setCd(const GFA::RGBColor &c);
        void setCd(
            const GFA::Scalar &r,
            const GFA::Scalar &g,
            const GFA::Scalar &b);
        
        virtual const GFA::RGBColor & getDiffuseCd() const;
        virtual void shade(FaaRay::TraceThread &ttRef) const;
        virtual void diffuse(FaaRay::TraceThread &ttRef) const;
        
    private:
        FaaRay::LambertianBRDF *ambientBrdfPtr_;
        FaaRay::LambertianBRDF *diffuseBrdfPtr_;
};

typedef std::shared_ptr<MatteMaterial>  MatteMaterialSPtr;
typedef std::shared_ptr<const MatteMaterial>  ConstMatteMaterialSPtr;

}

#endif

