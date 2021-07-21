#include "Sampler.hpp"
#include "GFA.hpp"
#include "Render/TraceThread.hpp"
#include <math.h>
#include <algorithm>   // for random_shuffle in Sampler::setupShuffledIndices

// NeedFix: because TraceThread also uses Sampler
#include "Render/TraceThread.hpp"

FaaRay::Sampler::Sampler()
    :   numOneDimSamples_(1),
        numSamples_(1),
        numSets_(83) // some kind of magical number
{
    // Set sandom seed for samples
    rng_.seed(numSets_);

    // reserve space but do not set yet
    samples_.reserve(numSamples_ * numSets_);

	setupShuffledIndices();
}

// The numSamples will be changed to lowes nomber that has a int square root
// ex: 10 will be changed to 9 because lowest square root is 3
FaaRay::Sampler::Sampler(const GFA::Size &numSamplesRef)
    :   numOneDimSamples_((GFA::Size) sqrt((float) numSamplesRef)),
        numSamples_(numOneDimSamples_ * numOneDimSamples_),
        numSets_(83) // some kind of magical number
{
    // Set sandom seed for samples
    rng_.seed(numSets_);

    // reserve space but do not set yet
    samples_.reserve(numSamples_ * numSets_);

	setupShuffledIndices();
}

FaaRay::Sampler::~Sampler()
{
}

const GFA::Size & FaaRay::Sampler::numSamples() const
{
    return numSamples_;
}

// sets up randomly shuffled indices for the samples
void FaaRay::Sampler::setupShuffledIndices()
{
	shuffledIndices_.reserve(numSamples_ * numSets_);
	std::vector<GFA::Index> indices;
	
	for (GFA::Index j = 0; j < numSamples_; j++)
		indices.push_back(j);
	
	for (GFA::Index p = 0; p < numSets_; p++) { 
		random_shuffle(indices.begin(), indices.end());	
		
		for (GFA::Index j = 0; j < numSamples_; j++)
			shuffledIndices_.push_back(indices[j]);
	}	
}

// This method is called from multiple threads at the same time
// Do NOT use this class's random method, only the given random method in the
// render thread. TraceThread will be updated.
void FaaRay::Sampler::setSampleUnitSquare(FaaRay::TraceThread &ttRef) const
{
    GFA::Index newIndex;
    
    if (ttRef.sampleIndex == 0)
        ttRef.sampleSetIndex = GFA::Index (numSets_ * ttRef.rand()) * numSamples_;

    newIndex = ttRef.sampleSetIndex + ttRef.sampleIndex;
    newIndex = ttRef.sampleSetIndex + shuffledIndices_[newIndex];

    //NOTE: further optimize samples vector search up ?
    ttRef.sampleUnitSquare.x = samples_[newIndex].x;
    ttRef.sampleUnitSquare.y = samples_[newIndex].y;
}

// Get next random scalar between 0.0 and less then 1.0
GFA::Scalar FaaRay::Sampler::rand_()
{
    return distribution(rng_);
}
