#include "GeometricObject.hpp"
#include "Materials/Material.hpp"

FaaRay::GeometricObject::GeometricObject()
{
}

FaaRay::GeometricObject::~GeometricObject()
{
}

void FaaRay::GeometricObject::setMaterialSPtr(FaaRay::ConstMaterialSPtr materialSPtr)
{
    materialSPtr_ = materialSPtr;
}

FaaRay::ConstMaterialSPtr FaaRay::GeometricObject::getMaterialSPtr() const
{
    return materialSPtr_;
}
