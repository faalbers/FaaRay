#include "OpenCylinder.hpp"
#include "GFA.hpp"
#include "Render/TraceThread.hpp"

FaaRay::OpenCylinder::OpenCylinder()
    : radius_(1.0)
    , invRadius_(1.0/radius_)
    , radiusQuad_(1.0)
    , bottom_(0.0)
    , top_(1.0)
{
    constructDebug("FaaRay::OpenCylinder");
}

FaaRay::OpenCylinder::~OpenCylinder(void)
{
    deconstructDebug("FaaRay::OpenCylinder");
}

void FaaRay::OpenCylinder::setCenter(
    const GFA::Scalar &x,
    const GFA::Scalar &y,
    const GFA::Scalar &z)
{
    center_.x = x;
    center_.y = y;
    center_.z = z;
}

void FaaRay::OpenCylinder::setRadius(const GFA::Scalar &radius)
{
    radius_ = radius;
    radiusQuad_ = radius_*radius_;
}

void FaaRay::OpenCylinder::setBottom(const GFA::Scalar &bottom)
{
    bottom_ = bottom;
}

void FaaRay::OpenCylinder::setTop(const GFA::Scalar &top)
{
    top_ = top;
}

bool FaaRay::OpenCylinder::hit(FaaRay::TraceThread &ttRef, GFA::Scalar &tmin, GFA::Normal &srNormal) const
{
	GFA::Scalar t;
	GFA::Scalar ox = ttRef.rayOrigin.x-center_.x;
	GFA::Scalar oy = ttRef.rayOrigin.y-center_.y;
	GFA::Scalar oz = ttRef.rayOrigin.z-center_.z;
	GFA::Scalar dx = ttRef.rayDirection.x;
	GFA::Scalar dy = ttRef.rayDirection.y;
	GFA::Scalar dz = ttRef.rayDirection.z;
	
	GFA::Scalar a = dx * dx + dz * dz;  	
	GFA::Scalar b = 2.0 * (ox * dx + oz * dz);					
	GFA::Scalar c = ox * ox + oz * oz - radiusQuad_;
	GFA::Scalar disc = b * b - 4.0 * a * c ;

			
	if (disc < 0.0)
		return(false);
	else {	
		GFA::Scalar e = sqrt(disc);
		GFA::Scalar denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
		
		if (t > GFA::EPSILON) {
			GFA::Scalar yhit = oy + t * dy;
			
			if (yhit > bottom_ && yhit < top_) {
				tmin = t;
				srNormal = GFA::Normal((ox + t * dx) * invRadius_, 0.0, (oz + t * dz) * invRadius_);
				
				// test for hitting from inside
			
				if (-ttRef.rayDirection * srNormal < 0.0)
					srNormal = srNormal * (-1.0);
				ttRef.srHitPoint = ttRef.rayOrigin + ttRef.rayDirection * tmin;
				
				return (true);
			}
		} 
		
		t = (-b + e) / denom;    // larger root
		
		if (t > GFA::EPSILON) {
			GFA::Scalar yhit = oy + t * dy;
			
			if (yhit > bottom_ && yhit < top_) {
				tmin = t;
				srNormal = GFA::Normal((ox + t * dx) * invRadius_, 0.0, (oz + t * dz) * invRadius_);
				
				// test for hitting inside surface
			
				if (-ttRef.rayDirection * srNormal < 0.0)
					srNormal = srNormal * (-1.0);
					
				ttRef.srHitPoint = ttRef.rayOrigin + ttRef.rayDirection * tmin;
	
				return (true);
			}
		} 
	}
	
	return (false);
}

bool FaaRay::OpenCylinder::shadowHit(FaaRay::TraceThread &ttRef, GFA::Scalar &tmin) const
{
    // page 57
	GFA::Scalar t;
	GFA::Scalar ox = ttRef.sRayOrigin.x-center_.x;
	GFA::Scalar oy = ttRef.sRayOrigin.y-center_.y;
	GFA::Scalar oz = ttRef.sRayOrigin.z-center_.z;
	GFA::Scalar dx = ttRef.sRayDirection.x;
	GFA::Scalar dy = ttRef.sRayDirection.y;
	GFA::Scalar dz = ttRef.sRayDirection.z;
	
	GFA::Scalar a = dx * dx + dz * dz;  	
	GFA::Scalar b = 2.0 * (ox * dx + oz * dz);					
	GFA::Scalar c = ox * ox + oz * oz - radiusQuad_;
	GFA::Scalar disc = b * b - 4.0 * a * c ;

			
	if (disc < 0.0)
		return(false);
	else {	
		GFA::Scalar e = sqrt(disc);
		GFA::Scalar denom = 2.0 * a;
		t = (-b - e) / denom;    // smaller root
		
		if (t > GFA::EPSILON) {
			GFA::Scalar yhit = oy + t * dy;
			
			if (yhit > bottom_ && yhit < top_) {
				tmin = t;
				return (true);
			}
		} 
		
		t = (-b + e) / denom;    // larger root
		
		if (t > GFA::EPSILON) {
			GFA::Scalar yhit = oy + t * dy;
			
			if (yhit > bottom_ && yhit < top_) {
				tmin = t;
				return (true);
			}
		} 
	}
	
	return (false);
}

FaaRay::OpenCylinderSPtr FaaRay::MakeOpenCylinderSPtr()
{
    return std::make_shared<FaaRay::OpenCylinder>();
}

/*
void FaaRay::OpenCylinder::setCenter(const GFA::Point3D& p)
{
    center.x = p.x;
    center.y = p.y;
    center.z = p.z;
}

bool FaaRay::OpenCylinder::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
    // page 57
    double t;
    GFA::Vector3D temp = ray.origin - center;
    double a = ray.direction * ray.direction;
    double b = 2.0 * (temp * ray.direction);
    double c = (temp * temp) - (radius * radius);
    double disc = (b * b) - (4 * a * c);
    
    if (disc < 0.0)
        return (false);
    else {
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) / denom; // smaller root

        if (t > kEpsilon) {
            tmin = t;
            sr.normal       = (temp + ray.direction * t) / radius;
            sr.localHitPoint = ray.origin + ray.direction * t;
            sr.color = color;
            return (true);
        }

        t = (-b + e) / denom; // larger root

        if (t > kEpsilon) {
            tmin = t;
            sr.normal       = (temp + ray.direction * t) / radius;
            sr.localHitPoint = ray.origin + ray.direction * t;
            sr.color = color;
            return (true);
        }
    }
    
    return (false);
}

bool FaaRay::OpenCylinder::shadowHit(const Ray& ray, double& tmin) const
{
    double t;
    GFA::Vector3D temp = ray.origin - center;
    double a = ray.direction * ray.direction;
    double b = 2.0 * (temp * ray.direction);
    double c = (temp * temp) - (radius * radius);
    double disc = (b * b) - (4 * a * c);
    
    if (disc < 0.0)
        return (false);
    else {
        double e = sqrt(disc);
        double denom = 2.0 * a;
        t = (-b - e) / denom; // smaller root

        if (t > kEpsilon) {
            tmin = t;
            return (true);
        }

        t = (-b + e) / denom; // larger root

        if (t > kEpsilon) {
            tmin = t;
            return (true);
        }
    }
    
    return (false);
}
*/
