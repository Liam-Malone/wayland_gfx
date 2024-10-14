/* Begin Color Functions */
global Color Color_HSV_to_RGBA(ColorHSV hsv_color) {
    TODO("Add HSV -> RGBA Conversion");
    Color col = {};
    return col;
}
global ColorHSV Color_RGBA_to_HSV(Color color) {
    TODO("Add RGBA -> HSV Conversion");
    ColorHSV col = {};
    return col;
}

/* Begin Shader Functions */
global Shader Shader_load(const char* restrict vs_filepath, const char* restrict fs_filepath) {
    #ifdef _debug_shader_load
    printf(" :: Shader Loading ::\n   > Attempting to load:\n    vs: %s\n    fs: %s\n\n",
            vs_filepath,
            fs_filepath);
    #endif
    /* Return var, 0 init */
    Shader shader = {};

    /* File Usage Vars */
    u64 fsize;
    FILE* fp = nullptr;
    char* vsbuf = nullptr;
    char* fsbuf = nullptr;

    /* Shader Compilation Vars */
    u32 vert_shader = 0;
    u32 frag_shader = 0;
    i32 success;
    char err_log[512];

    /* Vertex Shader Load */
    fsize = 0;
    fp = fopen(vs_filepath, "rb");
    if (!fp) {
        shader = (Shader) {};

        fprintf(stderr, 
                "  Failed to open file: %s\n",
                vs_filepath);
        goto exit;
    } else {
        fseek(fp, 0, SEEK_END);
        fsize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        vsbuf = malloc(sizeof(char) * (fsize + 1));
        fread(vsbuf, fsize, 1, fp);
        vsbuf[fsize] = 0;

        /* Actually use the buffer to create vert shader */
        {
            #ifdef _debug_shader_load
            fprintf(stderr, " :: Vert Shader Code ::\n%s\n", vsbuf);
            #endif

            vert_shader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vert_shader, 1, &vsbuf, NULL);
            glCompileShader(vert_shader);

            memset(err_log, 0, 512);
            glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(vert_shader, 512, NULL, err_log);
                fprintf(stderr, 
                        " :: ERR: Vertex Shader Compilation Failed ::\n  > %s\n\n", 
                        err_log);

                goto exit;
            }
        }

        fclose(fp);
        fp = 0;
    }

    /* Fragment Shader Load */
    fsize = 0;
    fp = fopen(fs_filepath, "rb");
    if (!fp) {
        shader = (Shader) {};
        fprintf(stderr, 
                "  Failed to open file: %s\n",
                fs_filepath);
        goto exit;
    } else {
        fseek(fp, 0, SEEK_END);
        fsize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        fsbuf = malloc(sizeof(char) * (fsize + 1));
        fread(fsbuf, fsize, 1, fp);
        fsbuf[fsize] = 0;

        /* Actually use the buffer to create frag shader */
        {
            #ifdef _debug_shader_load
            fprintf(stderr, " :: Frag Shader Code ::\n%s\n", fsbuf);
            #endif

            frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(frag_shader, 1, &fsbuf, NULL);
            glCompileShader(frag_shader);

            memset(err_log, 0, 512);
            glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(frag_shader, 512, NULL, err_log);
                fprintf(stderr,
                        " :: ERR: Fragment Shader Compilation Failed ::\n  > %s\n\n", 
                        err_log);

                goto exit;
            }
        }

        fclose(fp);
        fp = 0;
    }

    /* Construct full shader program */
    {
        shader.id = glCreateProgram();
        glAttachShader(shader.id, vert_shader);
        glAttachShader(shader.id, frag_shader);
        glLinkProgram(shader.id);

        /* Err check and log */
        glGetProgramiv(shader.id, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(shader.id, 512, NULL, err_log);
            fprintf(stderr,
                    " :: ERR: Shader Program Linking Failed ::\n  > %s\n\n",
                    err_log);

            glDeleteProgram(shader.id);
            goto exit;
        }

        glDeleteShader(vert_shader);
        glDeleteShader(frag_shader);
        vert_shader = frag_shader = 0;

        #ifdef _debug_shader_load
        printf("  :: Shader Load Successful!! ::\n");
        #endif
    }
    
exit: 
    if (fp) 
        fclose(fp);

    if (vsbuf) 
        free(vsbuf);

    if (fsbuf) 
        free(fsbuf);

    if (vert_shader) 
        glDeleteShader(vert_shader);

    if (frag_shader) 
        glDeleteShader(frag_shader);

    return shader;
}

global i32 Shader_get_uniform_location(Shader shader, const char* restrict value) {
    return glGetUniformLocation(shader.id, value);
}

global void Shader_set_value(Shader shader, i32 location, void* value, ShaderUniformDataType data_type) {
    switch (data_type) {
        case shader_uniform_f32:     { 
                                         glUniform1f(location, *((f32*) value));
                                         break;
                                     }
        case shader_uniform_vec2f32:  { 
                                         glUniform2f(location, 
                                                 ((Vec2f32*)value)->x, 
                                                 ((Vec2f32*)value)->y);
                                         break;
                                     }
        case shader_uniform_vec3f32:  { 
                                         glUniform3f(location, 
                                                 ((Vec3f32*)value)->x, 
                                                 ((Vec3f32*)value)->y, 
                                                 ((Vec3f32*)value)->z); 
                                         break; 
                                     }
        case shader_uniform_vec4f32:  { 
                                         glUniform4f(location,
                                                 ((Vec4f32*)value)->x, 
                                                 ((Vec4f32*)value)->y, 
                                                 ((Vec4f32*)value)->z, 
                                                 ((Vec4f32*)value)->w); 
                                         break;
                                     }
        case shader_uniform_i32:     { 
                                         glUniform1i(location, *((i32*) value));
                                         break;
                                     }
        case shader_uniform_vec2i32: { 
                                         glUniform2i(location,
                                                 ((Vec2i32*)value)->x, 
                                                 ((Vec2i32*)value)->y);
                                         break;
                                     }
        case shader_uniform_vec3i32: { 
                                         glUniform3i(location,
                                                 ((Vec3i32*)value)->x, 
                                                 ((Vec3i32*)value)->y,
                                                 ((Vec3i32*)value)->z);
                                         break;
                                     }
        case shader_uniform_vec4i32: { 
                                         glUniform4i(location,
                                                 ((Vec4i32*)value)->x, 
                                                 ((Vec4i32*)value)->y,
                                                 ((Vec4i32*)value)->z,
                                                 ((Vec4i32*)value)->w);
                                         break; 
                                     }
        case shader_uniform_sampler2d: { assert(false) ; break;} /* not gonna handle this yet */
    }
}

global void Shader_unload(Shader shader) {
    glDeleteProgram(shader.id);
}

global void Shader_use(Shader shader) {
    glUseProgram(shader.id);
}

/* End Shader Functions */
