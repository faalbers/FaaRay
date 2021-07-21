
#ifndef __FAARAY_VIEWPLANE_H__
#define __FAARAY_VIEWPLANE_H__

#include "Base/Base.hpp"
#include "GFA.hpp"
#include "Samplers/Sampler.hpp"
#include <memory>

namespace FaaRay {

class ViewPlane : public FaaRay::Base
{
    public:
        ViewPlane();
        ViewPlane(const GFA::Size width, const GFA::Size height);
        virtual ~ViewPlane(void);
    
        const GFA::Size   & width() const;
        const GFA::Size   & height() const;
        const GFA::Scalar & pixelSize() const;
        const GFA::Size   & numSamples() const;
        
        void setPixel(const GFA::Index &x, const GFA::Index &y,
            const GFA::RGBColor &col) const; 
    
        void setNumSamples(const GFA::Size &numSamples);
        const FaaRay::Sampler * getSamplerPtr() const;
        FaaRay::SamplerSPtr getSamplerSPtr() const;
        FaaRay::ConstSamplerSPtr getConstSamplerSPtr() const;
       
    protected:
        GFA::RGBColorBuffer         *frameBufferPtr_;
        GFA::Scalar                 pixelSize_;
        FaaRay::SamplerSPtr    samplerSPtr_;
    
        virtual void setGUIPixel_(const GFA::Index &x, const GFA::Index &y,
            const GFA::RGBColor &col) const; 
};

typedef std::shared_ptr<ViewPlane> ViewPlaneSPtr;
typedef std::shared_ptr<const ViewPlane> ConstViewPlaneSPtr;
}

#endif


