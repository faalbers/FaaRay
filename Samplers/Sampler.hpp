#ifndef __FAARAY_SAMPLER_H__
#define __FAARAY_SAMPLER_H__

#include "Base/Base.hpp"
#include "Shared/Shared.hpp"
#include "GFA.hpp"
#include <vector>

namespace FaaRay {

// forward decleration because TraceThread also includes Sampler through ViewPlane
class TraceThread;

class Sampler : public FaaRay::Base
{
    public:
        Sampler();
        Sampler(const GFA::Size &numSamplesRef);
        virtual ~Sampler();
        
        const GFA::Size & numSamples() const;
        
        virtual void generateSamples() = 0;
        void setupShuffledIndices();
    
        void setSampleUnitSquare(FaaRay::TraceThread &ttRef) const;
        
    protected:
        GFA::Size                   numOneDimSamples_;  // one dim of samples
        GFA::Size                   numSamples_;        // sample count in set
        GFA::Size                   numSets_;           // sample sets count
        std::vector<GFA::Point2D>   samples_;
        std::vector<GFA::Index>     shuffledIndices_;
        FaaRay::MyRNG               rng_;
        std::uniform_real_distribution<GFA::Scalar> distribution;  
        GFA::Scalar rand_();
};

typedef std::shared_ptr<Sampler>  SamplerSPtr;
typedef std::shared_ptr<const Sampler>  ConstSamplerSPtr;
}

#endif


