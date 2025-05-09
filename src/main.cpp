#include "../offsets/offsets.h"
#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_opengl3.h"
#include "../imgui/backends/imgui_impl_win32.h"
#include "../UI/UI.h"
#include <Windows.h>
#include <dwmapi.h>
#include <gl/GL.h>
#include <tchar.h>
#include "../GLFW/include/GLFW/glfw3.h"
#include "../GLFW/include/GLFW/glfw3native.h"
#include "../GLFW/include/GLFW/glfw3.h"
#include <string>
#include <iostream>
#include <thread> 
#include "../proc/proc.h"
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "Dwmapi.lib")
#include "../mem/mem.h"


int main()
{
    // works dont touch below NOTHING AT ALL MF 
    

    // Hide console window
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    // Initialize GLFW
    if (!glfwInit())
        return -1;

    // Set window hints for transparency and OpenGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE); // Enable transparency

    GLFWwindow* window = glfwCreateWindow(1280, 720, "", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    // Make ImGui background transparent
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg].w = 0.0f; // Transparent windows

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // get proc id and make sure its open below


    const char* procName = "cs2.exe";
    DWORD procId = GetProcId(procName);
    DWORD error = procId;
    const char* moduleName = "client.dll";
    DWORD GetModule = GetModuleAddr(moduleName);
    // fix this 
    if (GetModule == 0)
    {
        std::cout << "couldnt find your client.dll / not running / not working with cheat. contact devs for help";
        // fix this 
    }
    else
    {
        std::cout << "Your client.dll is working here it is. : " << moduleName << std::endl;
        // fix this 
    }
    if (procId == 0)
    {
        std::cerr << "If this says 0 then open your game... :  " << error << std::endl;
        Sleep(2000);
        std::cout << "Closeing now...";
        Sleep(5000);
        exit(0);
        // works dont touch
    }
    else
    {
        std::cout << "Process is opeoning... Please wait";
        Sleep(5000);


        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();

            // Start frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // Draw UI
            RenderUIForLoginAndShit();

            // Rendering
            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);

            // Transparent clear
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);
        }
        // works dont touch
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    // works dont touch
    return 0;
    // works dont touch
}