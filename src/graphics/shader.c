//
// Created by mat on 6/9/2022.
//

#include "shader.h"

// array that holds all the shaders in memory
int SHADERS[SHADER_RESERVED];

void shader_load_shaders() {
    // load the texture shaders
    SHADERS[SHADER_TEXTURE] = shader_load("texture");
}

void shader_start(SHADER shader) {
    // use the provided shader
    glUseProgram(SHADERS[shader]);
}

void shader_uniform_vec4(SHADER shader, char *name, float x, float y, float z, float w) {
    int location = glGetUniformLocation(SHADERS[shader], name);
    glUniform4f(location, x, y, z, w);
}

void shader_stop() {
    // unload active shader
    glUseProgram(0);
}

int shader_load(char *name) {
    // get the paths to the shader files
    char *vertex_path = shader_get_path("res/shader/", name, ".vsh");
    char *fragment_path = shader_get_path("res/shader/", name, ".fsh");

    // load the shader
    int shader = shader_load_from_path(vertex_path, fragment_path);

    // if the shader failed to load
    if (shader == -1) {
        // print to console that loading the shader has failed
        printf("ERR: Failed to load the shader\n");

        // exit the application
        exit(1);
    }

    // free the paths from memory
    free(vertex_path);
    free(fragment_path);

    // return the shader id
    return shader;
}

int shader_load_from_path(char *vertex, char *fragment) {
    // read the vertex source
    char *vertex_source = shader_read_source(vertex);
    if (vertex_source == NULL) {
        printf("ERR: Failed to read vertex source\n");
        return -1;
    }

    // read the fragment source
    char *fragment_source = shader_read_source(fragment);
    if (fragment_source == NULL) {
        printf("ERR: Failed to read fragment source\n");
        return -1;
    }

    // create both of the shaders
    int vertex_shader = shader_create(vertex_source, GL_VERTEX_SHADER);
    int fragment_shader = shader_create(fragment_source, GL_FRAGMENT_SHADER);

    // create a shader program
    int shader = glCreateProgram();

    // attach vertex and fragment shaders to the program
    glAttachShader(shader, vertex_shader);
    glAttachShader(shader, fragment_shader);

    // link and validate everything
    glLinkProgram(shader);
    glValidateProgram(shader);

    // free the sources from the memory
    free(vertex_source);
    free(fragment_source);

    // return the shader id
    return shader;
}

int shader_create(char *source, int type) {
    // create the shader id based on the shader type
    int shader_id = glCreateShader(type);

    // load the shader source into opengl memory
    glShaderSource((GLuint) shader_id, 1, (const GLchar **) &source, NULL);

    // compile the shader
    glCompileShader(shader_id);

    // define space in memory where the response of the compilation will go
    GLint response;

    // get the status of the compilation
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &response);

    // if the compilation has failed
    if (response == GL_FALSE) {

        // read the log into the info buffer
        GLchar info[MAX_READ_BUFFER];
        glGetShaderInfoLog(shader_id, MAX_READ_BUFFER, NULL, &info[0]);

        // print the buffer to the console
        printf("%s\n", info);

        // and exit the application
        exit(1);
    }

    // return the id of the shader that was created
    return shader_id;
}

char *shader_read_source(char *path) {
    printf("Path: %s\n", path);

    // open the file handle
    FILE *file = fopen(path, "r");
    if (file == NULL) {
        return NULL;
    }

    // define space in memory where the file contents will be read into
    char *data = calloc(MAX_READ_BUFFER, sizeof(char));

    // define character data
    char current_char;
    int current_index = 0;

    // loop until the file has reached its end
    do {
        // read the character from the file
        current_char = (char) fgetc(file);

        // save it into the buffer
        data[current_index] = current_char;

        // increment the index
        current_index++;
    } while (current_char != EOF);

    // null terminate the string
    data[current_index - 1] = '\0';

    // close the file
    fclose(file);

    // return the file data
    return data;
}

char *shader_get_path(char *path, char *name, char *type) {
    size_t size = strlen(path) + strlen(name) + strlen(type) + 1;
    char *buffer = (char *) malloc(size);
    snprintf(buffer, size, "%s%s%s", path, name, type);
    return buffer;
}