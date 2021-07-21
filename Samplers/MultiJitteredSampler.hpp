#ifndef __FAARAY_MULTIJITTEREDSAMPLER_H__
#define __FAARAY_MULTIJITTEREDSAMPLER_H__

#include "Sampler.hpp"
#include "GFA.hpp"
#include <memory>

namespace FaaRay {

class MultiJitteredSampler : public FaaRay::Sampler
{
    public:
        MultiJitteredSampler();
        MultiJitteredSampler(const GFA::Size &numSamplesRef);
        virtual ~MultiJitteredSampler();

        virtual void generateSamples();
};

typedef std::shared_ptr<MultiJitteredSampler>  MultiJitteredSamplerSPtr;
MultiJitteredSamplerSPtr MakeMultiJitteredSamplerSPtr();
MultiJitteredSamplerSPtr MakeMultiJitteredSamplerSPtr(const GFA::Size &numSamplesRef);

}

#endif

