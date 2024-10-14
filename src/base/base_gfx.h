/* Color Types */
/* RGBA */
typedef struct Color Color;
struct Color {
    f32 r;
    f32 g;
    f32 b;
    f32 a;
};

/* HSV */
typedef struct ColorHSV ColorHSV;
struct ColorHSV {
    f32 h;
    f32 s;
    f32 v;
};

/* Color Type Functions */
global Color Color_HSV_to_RGBA(ColorHSV hsv_color);
global ColorHSV Color_RGBA_to_HSV(Color color);

/* Shader data types */
typedef struct Shader Shader;
struct Shader {
    u32 id;    /* Shader Program ID */
    i32 *locs; /* Shader Locations Array */
};

typedef enum ShaderUniformDataType {
        shader_uniform_f32 = 0,       /* Shader uniform type: float */
        shader_uniform_vec2f32,            /* Shader uniform type: vec2 (2 float) */
        shader_uniform_vec3f32,            /* Shader uniform type: vec3 (3 float) */
        shader_uniform_vec4f32,            /* Shader uniform type: vec4 (4 float) */
        shader_uniform_i32,             /* Shader uniform type: int */
        shader_uniform_vec2i32,           /* Shader uniform type: ivec2 (2 int) */
        shader_uniform_vec3i32,           /* Shader uniform type: ivec3 (3 int) */
        shader_uniform_vec4i32,           /* Shader uniform type: ivec4 (4 int) */
        shader_uniform_sampler2d        /* Shader uniform type: sampler2d */
} ShaderUniformDataType;

typedef enum ShaderAttributeDataType {
        shader_attribute_f32 = 0,     /* Shader attribute type: float */
        shader_attribute_vec2f32,          /* Shader attribute type: vec2 (2 float) */
        shader_attribute_vec3f32,          /* Shader attribute type: vec3 (3 float) */
        shader_attribute_vec4f32           /* Shader attribute type: vec4 (4 float) */
} ShaderAttributeDataType;

global Shader Shader_load(const char* restrict vs_filepath, const char* restrict fs_filepath);
global i32 Shader_get_uniform_location(Shader shader, const char* restrict value);
global void Shader_set_value(Shader shader, i32 location, void* value, ShaderUniformDataType data_type);
global void Shader_unload(Shader shader);
global void Shader_use(Shader shader);
