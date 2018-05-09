#define BOUNDING_RADIUS_2 4.f
#define ESCAPE_THRESHOLD 1e1f
#define DELTA 1e-4f

#include "include/kernel.h"

static float4 QuatMult(const float4 q1, const float4 q2) {
	float4 r;

	// a1a2 - b1b2 - c1c2 - d1d2
	r.x = q1.x * q2.x - q1.y * q2.y - q1.z * q2.z - q1.w * q2.w;
	// a1b2 + b1a2 + c1d2 - d1c2
	r.y = q1.x * q2.y + q1.y * q2.x + q1.z * q2.w - q1.w * q2.z;
	// a1c2 - b1d2 + c1a2 + d1b2
	r.z = q1.x * q2.z - q1.y * q2.w + q1.z * q2.x + q1.w * q2.y;
	// a1d2 + b1c2 - c1b2 + d1a2
	r.w = q1.x * q2.w + q1.y * q2.z - q1.z * q2.y + q1.w * q2.x;

	return r;
}

static float4 QuatSqr(const float4 q) {
	float4 r;

	r.x = q.x * q.x - q.y * q.y - q.z * q.z - q.w * q.w;
	r.y = 2.f * q.x * q.y;
	r.z = 2.f * q.x * q.z;
	r.w = 2.f * q.x * q.w;

	return r;
}

constant uint maxIterations = 10;

static void IterateIntersect(float4 *q, float4 *qp,
		const float4 c) {
	float4 q0 = *q;
	float4 qp0 = *qp;

	for (uint i = 0; i < maxIterations; ++i) {
		qp0 = 2.f * QuatMult(q0, qp0);
		q0 = QuatSqr(q0) + c;

		if (dot(q0, q0) > ESCAPE_THRESHOLD)
			break;
	}

	*q = q0;
	*qp = qp0;
}

constant float4 c = { -0.291f, -0.399f, 0.399f, -0.437f };
constant float epsilon = 0.003f * 0.75f;

static float IntersectBoundingSphere(const t_ray ray) {
	const float4 op = {-ray.o, 1.f};
	const float b = dot(op, (float4)(ray.d, 1.f));
	float det = b * b - dot(op, op) + 4.f;

	if (det < 0.f)
		return -1.f;
	else
		det = native_sqrt(det);

	float t = b - det;
	if (t > 0.f)
		return t;
	else {
		t = b + det;

		if (t > 0.f) {
			// We are inside, start from the ray origin
			return 0.0f;
		} else
			return -1.f;
	}
}

static float IntersectJulia(const t_ray ray) {
	float dist = IntersectBoundingSphere(ray);
	if (dist <= 0.f)
		return (INFINITY);
	float4 r = {ray.o, 0.f};

	do {
		float4 z = r;
		float4 zp = { 1.f, 0.f, 0.f, 0.f };

		IterateIntersect(&z, &zp, c);

		const float normZP = length(zp);

		// We are inside
		if (normZP == 0.f)
			break;

		const float normZ = length(z);
		dist = 0.5f * normZ * log(normZ) / normZP;

		r += (float4)(ray.d, 0.f) * dist;
 		if (dot(r, r) < BOUNDING_RADIUS_2)
			return (-1);
	} while (dist > epsilon);

	return distance(ray.o, r.xyz);
}
