#include <math.h> /* Provides: sinf(), cosf(), tan(), atan2f(), sqrtf(), floor(), fminf(), fmaxf(), fabsf() */

typedef f32 Rad;
typedef f32 Deg;

typedef union Vec4f32 Vec4f32;
union Vec4f32 {
    struct {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    };
    struct {
        f32 r;
        f32 g;
        f32 b;
        f32 a;
    };
    f32 ptr[4];
};

typedef union Vec3f32 Vec3f32;
union Vec3f32 {
    struct {
        f32 x;
        f32 y;
        f32 z;
    };
    struct {
        f32 r;
        f32 g;
        f32 b;
    };
    f32 ptr[3];
};
typedef union Vec2f32 Vec2f32;
union Vec2f32 {
    struct {
        f32 x;
        f32 y;
    };
    f32 ptr[2];
};

typedef union Vec4i32 Vec4i32;
union Vec4i32 {
    struct {
        i32 x;
        i32 y;
        i32 z;
        i32 w;
    };
    struct {
        i32 r;
        i32 g;
        i32 b;
        i32 a;
    };
    i32 ptr[4];
};

typedef union Vec3i32 Vec3i32;
union Vec3i32 {
    struct {
        i32 x;
        i32 y;
        i32 z;
    };
    struct {
        i32 r;
        i32 g;
        i32 b;
    };
    i32 ptr[3];
};
typedef union Vec2i32 Vec2i32;
union Vec2i32 {
    struct {
        i32 x;
        i32 y;
    };
    i32 ptr[2];
};

typedef Vec4f32 Quaternion;

// Matrix, 4x4 components, column major, OpenGL style, right-handed
typedef struct Matrix Matrix;
struct Matrix {
    f32 m0, m4, m8,  m12; /*  Matrix 1st row (4 components)  */
    f32 m1, m5, m9,  m13; /*  Matrix 2nd row (4 components)  */
    f32 m2, m6, m10, m14; /*  Matrix 3rd row (4 components)  */
    f32 m3, m7, m11, m15; /*  Matrix 4th row (4 components)  */
};


/* Vector Functions */
global f32 Vec4f32_mag(Vec4f32 vec);
global f32 Vec3f32_mag(Vec3f32 vec);
global f32 Vec2f32_mag(Vec2f32 vec);

global Vec4f32 Vec4f32_normalize(Vec4f32 vec);
global Vec3f32 Vec3f32_normalize(Vec3f32 vec);
global Vec2f32 Vec2f32_normalize(Vec2f32 vec);

global Vec4f32 Vec4f32_scale(Vec4f32 vec, f32 scalar);
global Vec3f32 Vec3f32_scale(Vec3f32 vec, f32 scalar);
global Vec2f32 Vec2f32_scale(Vec2f32 vec, f32 scalar);

global Vec4f32 Vec4f32_add(Vec4f32 vec_a, Vec4f32 vec_b);
global Vec3f32 Vec3f32_add(Vec3f32 vec_a, Vec3f32 vec_b);
global Vec2f32 Vec2f32_add(Vec2f32 vec_a, Vec2f32 vec_b);

global f32 Vec4f32_dot(Vec4f32 vec_a, Vec4f32 vec_b);
global f32 Vec3f32_dot(Vec3f32 vec_a, Vec3f32 vec_b);
global f32 Vec2f32_dot(Vec2f32 vec_a, Vec2f32 vec_b);

global Vec3f32 Vec3f32_cross(Vec3f32 vec_a, Vec3f32 vec_b); /* Cross product only applies to 3D Vectors*/

global f32 Vec4i32_mag(Vec4i32 vec);
global f32 Vec3i32_mag(Vec3i32 vec);
global f32 Vec2i32_mag(Vec2i32 vec);

global Vec4i32 Vec4i32_normalize(Vec4i32 vec);
global Vec3i32 Vec3i32_normalize(Vec3i32 vec);
global Vec2i32 Vec2i32_normalize(Vec2i32 vec);

global Vec4i32 Vec4i32_scale(Vec4i32 vec, i32 scalar);
global Vec3i32 Vec3i32_scale(Vec3i32 vec, i32 scalar);
global Vec2i32 Vec2i32_scale(Vec2i32 vec, i32 scalar);

global Vec4i32 Vec4i32_add(Vec4i32 vec_a, Vec4i32 vec_b);
global Vec3i32 Vec3i32_add(Vec3i32 vec_a, Vec3i32 vec_b);
global Vec2i32 Vec2i32_add(Vec2i32 vec_a, Vec2i32 vec_b);

global f32 Vec4i32_dot(Vec4i32 vec_a, Vec4i32 vec_b);
global f32 Vec3i32_dot(Vec3i32 vec_a, Vec3i32 vec_b);
global f32 Vec2i32_dot(Vec2i32 vec_a, Vec2i32 vec_b);

global Vec3i32 Vec3i32_cross(Vec3i32 vec_a, Vec3i32 vec_b); /* Cross product only applies to 3D Vectors*/

/* Matrix Functions */
global Matrix Matrix_transpose(Matrix matrix);
global Matrix Matrix_invert(Matrix matrix);
global Matrix Matrix_identity(void);
global Matrix Matrix_add(Matrix left, Matrix right);
global Matrix Matrix_sub(Matrix left, Matrix right);
global Matrix Matrix_mul(Matrix left, Matrix right);
global Matrix Matrix_trans(f32 x, f32 y, f32 z);

/* Rotation Functions Assume Angle in Radians */
global Matrix Matrix_rotate_x(Rad angle);
global Matrix Matrix_rotate_y(Rad angle);
global Matrix Matrix_rotate_z(Rad angle);
global Matrix Matrix_rotate_xyz(Vec3f32 angle);
global Matrix Matrix_rotate_zyx(Vec3f32 angle);
global Matrix Matrix_scale(f32 x, f32 y, f32 z);
