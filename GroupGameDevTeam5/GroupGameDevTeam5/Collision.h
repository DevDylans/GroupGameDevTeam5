#pragma once
#include "pch.h"
#include <DirectXCollision.h>

using namespace DirectX;

struct BoundingBox {
	size_t CORNER_COUNT;
	XMFLOAT3 Center;
	XMFLOAT3 Extents;

	BoundingBox() noexcept;

	void BoundingBoxF(const BoundingBox &);

	BoundingBox & operator=(const BoundingBox &);
	void BoundingBoxF(BoundingBox &&);

	BoundingBox & operator=(BoundingBox &&);

	XM_CONSTEXPR BoundingBox(const XMFLOAT3 & center,const XMFLOAT3 & extents);

	void XM_CALLCONV Transform(BoundingBox & Out,FXMMATRIX M);
	void XM_CALLCONV Transform(BoundingBox & Out,float  Scale, FXMVECTOR Rotation, FXMVECTOR Translation);

	void  GetCorners(XMFLOAT3 *Corners);

	ContainmentType XM_CALLCONV Contains(FXMVECTOR Point);
	ContainmentType XM_CALLCONV Contains(FXMVECTOR V0,FXMVECTOR V1,FXMVECTOR V2);
	ContainmentType Contains(const BoundingSphere & sh);
	ContainmentType Contains(const BoundingBox & box);
	ContainmentType Contains(const BoundingOrientedBox & box);
	ContainmentType Contains(const BoundingFrustum & fr);

	Platform::Boolean Intersects(const BoundingSphere & sh);
	Platform::Boolean Intersects(const BoundingBox & box);
	Platform::Boolean Intersects(const BoundingOrientedBox & box);
	Platform::Boolean Intersects(const BoundingFrustum & fr);

	bool XM_CALLCONV Intersects(FXMVECTOR V0,FXMVECTOR V1,FXMVECTOR V2);

	PlaneIntersectionType XM_CALLCONV Intersects(FXMVECTOR Plane);

	bool XM_CALLCONV Intersects(FXMVECTOR Origin,FXMVECTOR Direction,float &   Dist);

	ContainmentType XM_CALLCONV ContainedBy(FXMVECTOR Plane0,FXMVECTOR Plane1,FXMVECTOR Plane2,GXMVECTOR Plane3,HXMVECTOR Plane4,HXMVECTOR Plane5);

	void CreateMerged(BoundingBox & Out,const BoundingBox & b1,const BoundingBox & b2);
	void CreateFromSphere(BoundingBox & Out,const BoundingSphere & sh);
	void XM_CALLCONV CreateFromPoints(BoundingBox & Out,FXMVECTOR pt1,FXMVECTOR pt2);
	void CreateFromPoints(BoundingBox &  Out,size_t Count,const XMFLOAT3 *pPoints,size_t Stride);
};