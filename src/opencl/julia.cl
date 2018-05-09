#define BOUNDING_RADIUS_2 4.f
#define ESCAPE_THRESHOLD 1e1f
#define DELTA 1e-4f

static float4 QuatMult(const float4 q1, const float4 q2) {
	float4 r;

	r.x = q1.x * q2.x - dot(q1.yzw, q2.yzw);
	r.yzw = q1.x * q2.yzw + q2.x * q1.yzw + cross(q1.yzw, q2.yzw);

	return r;
}

static float4 QuatSqr(const float4 q) {
	float4 r;

	r.x = q.x * q.x - dot(q.yzw, q.yzw);
	r.yzw = 2 * q.x * q.yzw;

	return r;
}

constant uint maxIterations = 10;

constant float4 c = {0.285f, 0.485f, 0.f, 0.f};
constant float epsilon = 0.003f * 0.75f;

static void IterateIntersect(float4 *q, float4 *qp) {
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
	if (dist < 0)
		return (INFINITY);
	float4 r = {ray.o, 0.f};

	do {
		float4 z = r;
		float4 zp = { 1.f, 0.f, 0.f, 0.f };

		IterateIntersect(&z, &zp);

		const float normZP = length(zp);

		// We are inside
		if (normZP == 0.f)
			break;

		const float normZ = length(z);
		dist = 0.5f * normZ * log(normZ) / normZP;

		r += (float4)(ray.d, 0.f) * dist;
 		if (dot(r, r) > BOUNDING_RADIUS_2)
			return (INFINITY);
	} while (dist > epsilon);

	return distance(ray.o, r.xyz);
}
