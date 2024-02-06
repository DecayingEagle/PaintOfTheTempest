#include "config.h"
#include "main.h"

int main()
{
    if(!glfwInit())
    {
        std::cout << "GLFW couldn't start" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "A window", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        glfwTerminate();
        return -1;
    }
    
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    uint shader = make_shader(
        "../src/shaders/vertex.glsl",
        "../src/shaders/fragment.glsl");

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader);
        glfwSwapBuffers(window);
    }
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}


uint make_shader(const std::string& vertex_filepath, const std::string& fragment_filepath)
{
    std::vector<uint> modules;
    modules.push_back(make_module(vertex_filepath, GL_VERTEX_SHADER));
    modules.push_back(make_module(fragment_filepath, GL_FRAGMENT_SHADER));

    uint shader = glCreateProgram();
    for (uint shaderModule : modules)
    {
        glAttachShader(shader, shaderModule);
    }
    glLinkProgram(shader);
    
    int success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if(!success)
    {
        char errorLog[1024];
        glGetProgramInfoLog(shader, 1024, nullptr, errorLog);
        std::cout << "Shader linking error:\n" << errorLog << std::endl;
    }

    for (uint shaderModule : modules)
    {
        glDeleteShader(shaderModule);
    }
    
    return shader;
}

uint make_module(const std::string& filepath, uint module_type)
{
    std::ifstream file;
    std::stringstream bufferedLines;
    std::string line;

    file.open(filepath);
    while (std::getline(file, line))
    {
        // TODO: Remove as this is for testing only
        //std::cout << line << std::endl;
        bufferedLines << line << "\n";
    }
    std::string sharderSource = bufferedLines.str();
    const char* shaderSrc = sharderSource.c_str();
    bufferedLines.str("");
    file.close();

    uint shaderModule = glCreateShader(module_type);
    glShaderSource(shaderModule, 1, &shaderSrc, nullptr);
    glCompileShader(shaderModule);

    int success;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char errorLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, nullptr, errorLog);
        std::cout << "Shader Module compilation error:\n" << errorLog << std::endl;
    }

    return shaderModule;
}