#include "Sampler.hpp"
#include "RegularSampler.hpp"
#include "GFA.hpp"
#include <memory>

FaaRay::RegularSampler::RegularSampler()
    :   FaaRay::Sampler()
{
    std::cout << "BLAAH\n";
    generateSamples();
    constructDebug("FaaRay::RegularSampler");
}

FaaRay::RegularSampler::RegularSampler(const GFA::Size &numSamplesRef)
    :   FaaRay::Sampler(numSamplesRef)
{
    generateSamples();
    constructDebug("FaaRay::RegularSampler(numSamples)");
}

FaaRay::RegularSampler::~RegularSampler()
{
    deconstructDebug("FaaRay::RegularSampler");
}

void FaaRay::RegularSampler::generateSamples()
{
    // Create numSets of numOneDimSamples by numOneDimSamples box
    // each point will be in the middle of each sample box area
    for (GFA::Index p = 0; p < numSets_; p++) {
        for (GFA::Index j = 0; j < numOneDimSamples_; j++) {
            for (GFA::Index k = 0; k < numOneDimSamples_; k++) {
                GFA::Point2D sp(
                    (k + 0.5) / numOneDimSamples_,
                    (j + 0.5) / numOneDimSamples_);
                samples_.push_back(sp);
            }
        }
    }
}

FaaRay::RegularSamplerSPtr FaaRay::MakeRegularSamplerSPtr()
{
    return std::make_shared<FaaRay::RegularSampler>();
}

FaaRay::RegularSamplerSPtr FaaRay::MakeRegularSamplerSPtr(const GFA::Size &numSamplesRef)
{
    return std::make_shared<FaaRay::RegularSampler>(numSamplesRef);
}

