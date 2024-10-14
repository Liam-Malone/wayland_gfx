/* Vector Functions */
/* Float Vectors */
global f32 Vec4f32_mag(Vec4f32 vec) {
    return sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z) + (vec.w * vec.w));
}

global f32 Vec3f32_mag(Vec3f32 vec) {
    return sqrtf((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
}
global f32 Vec2f32_mag(Vec2f32 vec) {
    return sqrtf((vec.x * vec.x) + (vec.y * vec.y));
}

global Vec4f32 Vec4f32_normalize(Vec4f32 vec) {
    const f32 mag = Vec4f32_mag(vec);
    if (mag == 0) 
        return (Vec4f32) { { 0, 0, 0, 0 } };

    return (Vec4f32) {
        .x = vec.x / mag,
        .y = vec.y / mag,
        .z = vec.z / mag,
        .w = vec.w / mag
    };
}
global Vec3f32 Vec3f32_normalize(Vec3f32 vec) {
    const f32 mag = Vec3f32_mag(vec);
    if (mag == 0) 
        return (Vec3f32) { { 0, 0, 0 } };

    return (Vec3f32) {
        .x = vec.x / mag,
        .y = vec.y / mag,
        .z = vec.z / mag
    };
}
global Vec2f32 Vec2f32_normalize(Vec2f32 vec) {
    const f32 mag = Vec2f32_mag(vec);
    if (mag == 0) 
        return (Vec2f32) { { 0, 0 } };

    return (Vec2f32) {
        .x = vec.x / mag,
        .y = vec.y / mag
    };
}

global Vec4f32 Vec4f32_scale(Vec4f32 vec, f32 scalar) {
    return (Vec4f32) {
        .x = vec.x + scalar,
        .y = vec.y + scalar,
        .z = vec.z + scalar,
        .w = vec.w + scalar
    };
}

global Vec3f32 Vec3f32_scale(Vec3f32 vec, f32 scalar) {
    return (Vec3f32) {
        .x = vec.x + scalar,
        .y = vec.y + scalar,
        .z = vec.z + scalar
    };
}
global Vec2f32 Vec2f32_scale(Vec2f32 vec, f32 scalar) {
    return (Vec2f32) {
        .x = vec.x + scalar,
        .y = vec.y + scalar
    };
}

global Vec4f32 Vec4f32_add(Vec4f32 vec_a, Vec4f32 vec_b) {
    return (Vec4f32) {
        .x = vec_a.x + vec_b.x,
        .y = vec_a.y + vec_b.y,
        .z = vec_a.z + vec_b.z,
        .w = vec_a.w + vec_b.w
    };
}

global Vec3f32 Vec3f32_add(Vec3f32 vec_a, Vec3f32 vec_b) {
    return (Vec3f32) {
        .x = vec_a.x + vec_b.x,
        .y = vec_a.y + vec_b.y,
        .z = vec_a.z + vec_b.z
    };
}

global Vec2f32 Vec2f32_add(Vec2f32 vec_a, Vec2f32 vec_b) {
    return (Vec2f32) {
        .x = vec_a.x + vec_b.x,
        .y = vec_a.y + vec_b.y
    };
}
global f32 Vec4f32_dot(Vec4f32 vec_a, Vec4f32 vec_b) {
    return ( (vec_a.x * vec_b.x) +
             (vec_a.y * vec_b.y) +
             (vec_a.z * vec_b.z) +
             (vec_a.w * vec_b.w));
}
global f32 Vec3f32_dot(Vec3f32 vec_a, Vec3f32 vec_b) {
    return ( (vec_a.x * vec_b.x) +
             (vec_a.y * vec_b.y) +
             (vec_a.z * vec_b.z));
}
global f32 Vec2f32_dot(Vec2f32 vec_a, Vec2f32 vec_b) {
    return ( (vec_a.x * vec_b.x) +
             (vec_a.y * vec_b.y));
}

global Vec3f32 Vec3f32_cross(Vec3f32 vec_a, Vec3f32 vec_b) {
    return (Vec3f32) {
        .x = ((vec_a.y * vec_b.z) - (vec_a.z * vec_b.y)) ,
        .y = ((vec_a.z * vec_b.x) - (vec_a.x * vec_b.z)) ,
        .z = ((vec_a.x * vec_b.y) - (vec_a.y * vec_b.x))
    };
}


/* Integer Vectors */
global f32 Vec4i32_mag(Vec4i32 vec)  {
    return sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z) + (vec.w * vec.w));
}

global f32 Vec3i32_mag(Vec3i32 vec)  {
    return sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
}

global f32 Vec2i32_mag(Vec2i32 vec)  {
    return sqrt((vec.x * vec.x) + (vec.y * vec.y));
}

global Vec4i32 Vec4i32_normalize(Vec4i32 vec) {
    const f32 mag = Vec4i32_mag(vec);
    if (mag == 0) 
        return (Vec4i32) { { 0, 0, 0, 0 } };

    return (Vec4i32) {
        .x = (i32) ((i32) vec.x / mag),
        .y = (i32) ((i32) vec.y / mag),
        .z = (i32) ((i32) vec.z / mag),
        .w = (i32) ((i32) vec.w / mag)
    };
}

global Vec3i32 Vec3i32_normalize(Vec3i32 vec) {
    const f32 mag = Vec3i32_mag(vec);
    if (mag == 0) 
        return (Vec3i32) { { 0, 0, 0 } };

    return (Vec3i32) {
        .x = (i32) ((i32) vec.x / mag),
        .y = (i32) ((i32) vec.y / mag),
        .z = (i32) ((i32) vec.z / mag)
    };
}

global Vec2i32 Vec2i32_normalize(Vec2i32 vec) {
    const f32 mag = Vec2i32_mag(vec);
    if (mag == 0) 
        return (Vec2i32) { { 0, 0 } };

    return (Vec2i32) {
        .x = (i32) ((i32) vec.x / mag),
        .y = (i32) ((i32) vec.y / mag)
    };
}

global Vec4i32 Vec4i32_scale(Vec4i32 vec, i32 scalar) {
    return (Vec4i32) {
        .x = vec.x + scalar,
        .y = vec.y + scalar,
        .z = vec.z + scalar,
        .w = vec.w + scalar
    };
}
global Vec3i32 Vec3i32_scale(Vec3i32 vec, i32 scalar) {
    return (Vec3i32) {
        .x = vec.x + scalar,
        .y = vec.y + scalar,
        .z = vec.z + scalar
    };
}
global Vec2i32 Vec2i32_scale(Vec2i32 vec, i32 scalar) {
    return (Vec2i32) {
        .x = vec.x + scalar,
        .y = vec.y + scalar
    };
}

global Vec4i32 Vec4i32_add(Vec4i32 vec_a, Vec4i32 vec_b) {
    return (Vec4i32) {
        .x = vec_a.x + vec_b.x,
        .y = vec_a.y + vec_b.y,
        .z = vec_a.z + vec_b.z,
        .w = vec_a.w + vec_b.w
    };
}
global Vec3i32 Vec3i32_add(Vec3i32 vec_a, Vec3i32 vec_b) {
    return (Vec3i32) {
        .x = vec_a.x + vec_b.x,
        .y = vec_a.y + vec_b.y,
        .z = vec_a.z + vec_b.z
    };
}
global Vec2i32 Vec2i32_add(Vec2i32 vec_a, Vec2i32 vec_b) {
    return (Vec2i32) {
        .x = vec_a.x + vec_b.x,
        .y = vec_a.y + vec_b.y
    };
}

global f32 Vec4i32_dot(Vec4i32 vec_a, Vec4i32 vec_b) {
    return ( (vec_a.x * vec_b.x) +
             (vec_a.y * vec_b.y) +
             (vec_a.z * vec_b.z) +
             (vec_a.w * vec_b.w));
}
global f32 Vec3i32_dot(Vec3i32 vec_a, Vec3i32 vec_b) {
    return ( (vec_a.x * vec_b.x) +
             (vec_a.y * vec_b.y) +
             (vec_a.z * vec_b.z));
}
global f32 Vec2i32_dot(Vec2i32 vec_a, Vec2i32 vec_b) {
    return ( (vec_a.x * vec_b.x) +
             (vec_a.y * vec_b.y));
}

global Vec3i32 Vec3i32_cross(Vec3i32 vec_a, Vec3i32 vec_b) {
    return (Vec3i32) {
        .x = ((vec_a.y * vec_b.z) - (vec_a.z * vec_b.y)) ,
        .y = ((vec_a.z * vec_b.x) - (vec_a.x * vec_b.z)) ,
        .z = ((vec_a.x * vec_b.y) - (vec_a.y * vec_b.x))
    };
}

/* Matrix Functions */
global Matrix Matrix_transpose(Matrix matrix) {
    return (Matrix) {
        .m0  = matrix.m0,
        .m1  = matrix.m4,
        .m2  = matrix.m8,
        .m3  = matrix.m12,
        .m4  = matrix.m1,
        .m5  = matrix.m5,
        .m6  = matrix.m9,
        .m7  = matrix.m13,
        .m8  = matrix.m2,
        .m9  = matrix.m6,
        .m10 = matrix.m10,
        .m11 = matrix.m14,
        .m12 = matrix.m3,
        .m13 = matrix.m7,
        .m14 = matrix.m11,
        .m15 = matrix.m15
    };
}

/* This is copied from raylib's `raymath.h` */
global Matrix Matrix_invert(Matrix matrix) {
    // Cache the matrix values (speed optimization)
    f32 a00 = matrix.m0,  a01 = matrix.m1,  a02 = matrix.m2,  a03 = matrix.m3;
    f32 a10 = matrix.m4,  a11 = matrix.m5,  a12 = matrix.m6,  a13 = matrix.m7;
    f32 a20 = matrix.m8,  a21 = matrix.m9,  a22 = matrix.m10, a23 = matrix.m11;
    f32 a30 = matrix.m12, a31 = matrix.m13, a32 = matrix.m14, a33 = matrix.m15;

    f32 b00 = (a00 * a11) - (a01 * a10);
    f32 b01 = (a00 * a12) - (a02 * a10);
    f32 b02 = (a00 * a13) - (a03 * a10);
    f32 b03 = (a01 * a12) - (a02 * a11);
    f32 b04 = (a01 * a13) - (a03 * a11);
    f32 b05 = (a02 * a13) - (a03 * a12);
    f32 b06 = (a20 * a31) - (a21 * a30);
    f32 b07 = (a20 * a32) - (a22 * a30);
    f32 b08 = (a20 * a33) - (a23 * a30);
    f32 b09 = (a21 * a32) - (a22 * a31);
    f32 b10 = (a21 * a33) - (a23 * a31);
    f32 b11 = (a22 * a33) - (a23 * a32);

    // Calculate the invert determinant (inlined to avoid double-caching)
    f32 invDet = 1.0f/(b00*b11 - b01*b10 + b02*b09 + b03*b08 - b04*b07 + b05*b06);

    return (Matrix) {
        .m0  = ((a11*b11 - a12*b10 + a13*b09)  * invDet),
        .m1  = ((-a01*b11 + a02*b10 - a03*b09) * invDet),
        .m2  = ((a31*b05 - a32*b04 + a33*b03)  * invDet),
        .m3  = ((-a21*b05 + a22*b04 - a23*b03) * invDet),
        .m4  = ((-a10*b11 + a12*b08 - a13*b07) * invDet),
        .m5  = ((a00*b11 - a02*b08 + a03*b07)  * invDet),
        .m6  = ((-a30*b05 + a32*b02 - a33*b01) * invDet),
        .m7  = ((a20*b05 - a22*b02 + a23*b01)  * invDet),
        .m8  = ((a10*b10 - a11*b08 + a13*b06)  * invDet),
        .m9  = ((-a00*b10 + a01*b08 - a03*b06) * invDet),
        .m10 = ((a30*b04 - a31*b02 + a33*b00)  * invDet),
        .m11 = ((-a20*b04 + a21*b02 - a23*b00) * invDet),
        .m12 = ((-a10*b09 + a11*b07 - a12*b06) * invDet),
        .m13 = ((a00*b09 - a01*b07 + a02*b06)  * invDet),
        .m14 = ((-a30*b03 + a31*b01 - a32*b00) * invDet),
        .m15 = ((a20*b03 - a21*b01 + a22*b00)  * invDet)
    };
}

global Matrix Matrix_identity(void) {
    return (Matrix) { 
        .m0 = 1.0f, .m4 = 0.0f, .m8  = 0.0f, .m12 = 0.0f,
        .m1 = 0.0f, .m5 = 1.0f, .m9  = 0.0f, .m13 = 0.0f,
        .m2 = 0.0f, .m6 = 0.0f, .m10 = 1.0f, .m14 = 0.0f,
        .m3 = 0.0f, .m7 = 0.0f, .m11 = 0.0f, .m15 = 1.0f 
    };
}

global Matrix Matrix_add(Matrix left, Matrix right) {
    return (Matrix) {
        .m0  = left.m0 + right.m0,
        .m1  = left.m1 + right.m1,
        .m2  = left.m2 + right.m2,
        .m3  = left.m3 + right.m3,
        .m4  = left.m4 + right.m4,
        .m5  = left.m5 + right.m5,
        .m6  = left.m6 + right.m6,
        .m7  = left.m7 + right.m7,
        .m8  = left.m8 + right.m8,
        .m9  = left.m9 + right.m9,
        .m10 = left.m10 + right.m10,
        .m11 = left.m11 + right.m11,
        .m12 = left.m12 + right.m12,
        .m13 = left.m13 + right.m13,
        .m14 = left.m14 + right.m14,
        .m15 = left.m15 + right.m15
    };
}

global Matrix Matrix_sub(Matrix left, Matrix right) {
    return (Matrix) {
        .m0  = left.m0 - right.m0,
        .m1  = left.m1 - right.m1,
        .m2  = left.m2 - right.m2,
        .m3  = left.m3 - right.m3,
        .m4  = left.m4 - right.m4,
        .m5  = left.m5 - right.m5,
        .m6  = left.m6 - right.m6,
        .m7  = left.m7 - right.m7,
        .m8  = left.m8 - right.m8,
        .m9  = left.m9 - right.m9,
        .m10 = left.m10 - right.m10,
        .m11 = left.m11 - right.m11,
        .m12 = left.m12 - right.m12,
        .m13 = left.m13 - right.m13,
        .m14 = left.m14 - right.m14,
        .m15 = left.m15 - right.m15
    };
}

global Matrix Matrix_mul(Matrix left, Matrix right) {
    return (Matrix) {
        .m0  = (left.m0 * right.m0)  + (left.m1 * right.m4)  + (left.m2 * right.m8)   + (left.m3 * right.m12),
        .m1  = (left.m0 * right.m1)  + (left.m1 * right.m5)  + (left.m2 * right.m9)   + (left.m3 * right.m13),
        .m2  = (left.m0 * right.m2)  + (left.m1 * right.m6)  + (left.m2 * right.m10)  + (left.m3 * right.m14),
        .m3  = (left.m0 * right.m3)  + (left.m1 * right.m7)  + (left.m2 * right.m11)  + (left.m3 * right.m15),
        .m4  = (left.m4 * right.m0)  + (left.m5 * right.m4)  + (left.m6 * right.m8)   + (left.m7 * right.m12),
        .m5  = (left.m4 * right.m1)  + (left.m5 * right.m5)  + (left.m6 * right.m9)   + (left.m7 * right.m13),
        .m6  = (left.m4 * right.m2)  + (left.m5 * right.m6)  + (left.m6 * right.m10)  + (left.m7 * right.m14),
        .m7  = (left.m4 * right.m3)  + (left.m5 * right.m7)  + (left.m6 * right.m11)  + (left.m7 * right.m15),
        .m8  = (left.m8 * right.m0)  + (left.m9 * right.m4)  + (left.m10 * right.m8)  + (left.m11 * right.m12),
        .m9  = (left.m8 * right.m1)  + (left.m9 * right.m5)  + (left.m10 * right.m9)  + (left.m11 * right.m13),
        .m10 = (left.m8 * right.m2)  + (left.m9 * right.m6)  + (left.m10 * right.m10) + (left.m11 * right.m14),
        .m11 = (left.m8 * right.m3)  + (left.m9 * right.m7)  + (left.m10 * right.m11) + (left.m11 * right.m15),
        .m12 = (left.m12 * right.m0) + (left.m13 * right.m4) + (left.m14 * right.m8)  + (left.m15 * right.m12),
        .m13 = (left.m12 * right.m1) + (left.m13 * right.m5) + (left.m14 * right.m9)  + (left.m15 * right.m13),
        .m14 = (left.m12 * right.m2) + (left.m13 * right.m6) + (left.m14 * right.m10) + (left.m15 * right.m14),
        .m15 = (left.m12 * right.m3) + (left.m13 * right.m7) + (left.m14 * right.m11) + (left.m15 * right.m15)
    };
}

global Matrix Matrix_trans(f32 x, f32 y, f32 z) {
    return (Matrix) {
            1.0f, 0.0f, 0.0f, x,
            0.0f, 1.0f, 0.0f, y,
            0.0f, 0.0f, 1.0f, z,
            0.0f, 0.0f, 0.0f, 1.0f
    };
}

/* Rotation Matrices */
/* Assumes Angle in Radians */
global Matrix Matrix_rotate_x(Rad angle) {
    Matrix matrix = Matrix_identity();
    f32 cosres = cosf((f32) angle);
    f32 sinres = sinf((f32) angle);

    matrix.m5 = cosres;
    matrix.m6 = sinres;
    matrix.m9 = -sinres;
    matrix.m10 = cosres;

    return matrix;
}

/* Assumes Angle in Radians */
global Matrix Matrix_rotate_y(Rad angle) {
    Matrix matrix = Matrix_identity();
    f32 cosres = cosf((f32) angle);
    f32 sinres = sinf((f32) angle);

    matrix.m0 = cosres;
    matrix.m2 = -sinres;
    matrix.m8 = sinres;
    matrix.m10 = cosres;

    return matrix;
}

/* Assumes Angle in Radians */
global Matrix Matrix_rotate_z(Rad angle) {
    Matrix matrix = Matrix_identity();
    f32 cosres = cosf((f32) angle);
    f32 sinres = sinf((f32) angle);

    matrix.m0 = cosres;
    matrix.m1 = sinres;
    matrix.m4 = -sinres;
    matrix.m5 = cosres;

    return matrix;
}

/* Assumes Angle in Radians*/
global Matrix Matrix_rotate_xyz(Vec3f32 angle) {
    Matrix matrix = Matrix_identity();

    f32 cos_z = cosf(-( (f32) angle.z ));
    f32 sin_z = sinf(-( (f32) angle.z ));
    f32 cos_y = cosf(-( (f32) angle.y ));
    f32 sin_y = sinf(-( (f32) angle.y ));
    f32 cos_x = cosf(-( (f32) angle.x ));
    f32 sin_x = sinf(-( (f32) angle.x ));

    matrix.m0  = (cos_z * cos_y);
    matrix.m1  = (cos_z * sin_y * sin_x) - (sin_z * cos_x);
    matrix.m2  = (cos_z * sin_y * cos_x) + (sin_z * sin_x);

    matrix.m4  = (sin_z * cos_y);
    matrix.m5  = (sin_z * sin_y * sin_x) + (cos_z * cos_x);
    matrix.m6  = (sin_z * sin_y * cos_x) - (cos_z * sin_x);

    matrix.m8  = -sin_y;
    matrix.m9  = (cos_y * sin_x);
    matrix.m10 = (cos_y * cos_x);

    return matrix;
}

/* Assumes Angle in Radians*/
global Matrix Matrix_rotate_zyx(Vec3f32 angle) {

    f32 cos_z = cosf((f32) angle.z);
    f32 sin_z = sinf((f32) angle.z);
    f32 cos_y = cosf((f32) angle.y);
    f32 sin_y = sinf((f32) angle.y);
    f32 cos_x = cosf((f32) angle.x);
    f32 sin_x = sinf((f32) angle.x);

    return (Matrix) {
        .m0  = (cos_z * cos_y),
        .m4  = (cos_z * sin_y * sin_x) - (cos_x * sin_z),
        .m8  = (sin_z * sin_x) + (cos_z * sin_x),
        .m12 = 0,

        .m1  = (cos_y * sin_z),
        .m5  = (cos_z * cos_x) + (sin_z * sin_y * sin_x),
        .m9  = (cos_x * sin_z * sin_y) - (cos_z * sin_x),
        .m13 = 0,

        .m2  = -sin_y,
        .m6  = (cos_y * sin_x),
        .m10 = (cos_y * cos_x),
        .m14 = 0,

        .m3  = 0,
        .m7  = 0,
        .m11 = 0,
        .m15 = 1,
    };
}

/* Scaling Matrix */
global Matrix Matrix_scale(f32 x, f32 y, f32 z) {
    return (Matrix) {
        x,    0.0f, 0.0f, 0.0f,
        0.0f, y,    0.0f, 0.0f,
        0.0f, 0.0f, z,    0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
}

