#ifndef __FAARAY_REGULARSAMPLER_H__
#define __FAARAY_REGULARSAMPLER_H__

#include "Sampler.hpp"
#include "GFA.hpp"
#include <memory>

namespace FaaRay {

class RegularSampler : public FaaRay::Sampler
{
    public:
        RegularSampler();
        RegularSampler(const GFA::Size &numSamplesRef);
        virtual ~RegularSampler();

        virtual void generateSamples();

};

typedef std::shared_ptr<RegularSampler>  RegularSamplerSPtr;
RegularSamplerSPtr MakeRegularSamplerSPtr();
RegularSamplerSPtr MakeRegularSamplerSPtr(const GFA::Size &numSamplesRef);

}

#endif

