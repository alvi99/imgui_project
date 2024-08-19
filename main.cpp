#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// #include <gl.h>

// Include GLFW after gl.h
#include <GLFW/glfw3.h>

#include <iostream>

// Dummy image data (you would replace this with your actual image loading code)
unsigned char image_data[] = {255, 0, 0, 255, 0, 255, 0, 255}; // RGBA
int image_width = 2;
int image_height = 2;

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

// Hello world
int main()
{
    std::cout << "Hello, World!" << std::endl;
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;
    // GL 3.0 + GLSL 130
    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    GLFWwindow *window = glfwCreateWindow(800, 600, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(2); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
                                                          // io.ConfigViewportsNoAutoMerge = true;
                                                          // io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    // ImGui::StyleColorsDark();
    ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular
    // ones.
    ImGuiStyle &style = ImGui::GetStyle();
    // if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    //{
    //     style.WindowRounding = 0.0f;
    //     style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    // }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    ImGui_ImplOpenGL3_Init(glsl_version);

    // Our state
    bool show_demo_window = false;
    bool show_another_window = false;
    bool alvis_chekbox = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImFont *font1 = io.Fonts->AddFontFromFileTTF("../fonts/FiraCodeNerdFontPropo-Regular.ttf", 24);
    ImFont *font2 = io.Fonts->AddFontFromFileTTF("../fonts/FiraCodeNerdFontPropo-Regular.ttf", 18);

    // Generate OpenGL texture for the image
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Variables for the text fields, checkboxes, and button states
    char text1[128] = "";
    char text2[128] = "";
    char text3[128] = "";
    char text4[128] = "";
    bool checkbox1 = false;
    bool checkbox2 = false;

    io.IniFilename = NULL;
    ImGui::LoadIniSettingsFromDisk("./imgui.ini");

    // Main loop
    while (!glfwWindowShouldClose(window))
    {

        if (alvis_chekbox)
        {
            io.FontDefault = font1;
        }
        else
        {
            io.FontDefault = font2;
        }
        // Take care of all GLFW events
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your
        // inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or
        // clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or
        // clear/overwrite your copy of the keyboard data. Generally you may always pass all inputs to dear imgui, and
        // hide them from your application based on those two flags.
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(100);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // Set the window size to 800x600 and center it
        // ImGui::SetNextWindowSize(ImVec2(1280, 960), ImGuiCond_Always);
        // ImGui::SetNextWindowPos(ImVec2((1280 - 800) / 2, (720 - 600) / 2), ImGuiCond_Always);

        ImGui::DockSpaceOverViewport(ImGui::GetWindowDockID(), ImGui::GetMainViewport(), ImGuiDockNodeFlags_None);

        // Show a single window with both the custom widget and the tree
        ImGui::Begin("Custom Widget with Tree");

        // Display the image
        ImGui::Image((void *)(intptr_t)image_texture, ImVec2(64, 64)); // Display a 64x64 image

        // Text fields
        ImGui::InputText("Text Field 1", text1, IM_ARRAYSIZE(text1));
        ImGui::InputText("Text Field 2", text2, IM_ARRAYSIZE(text2));
        ImGui::InputText("Text Field 3", text3, IM_ARRAYSIZE(text3));
        ImGui::InputText("Text Field 4", text4, IM_ARRAYSIZE(text4));

        // Checkboxes
        ImGui::Checkbox("Checkbox 1", &checkbox1);
        ImGui::Checkbox("Checkbox 2", &checkbox2);

        // Buttons
        if (ImGui::Button("Button 1"))
        {
            std::cout << "Button 1 clicked!" << std::endl;
        }
        if (ImGui::Button("Button 2"))
        {
            std::cout << "Button 2 clicked!" << std::endl;
        }

        // Add a tree with some elements
        if (ImGui::TreeNode("Root Node"))
        {
            if (ImGui::TreeNode("Child Node 1"))
            {
                ImGui::Text("This is Child Node 1");
                ImGui::TreePop(); // End of Child Node 1
            }
            if (ImGui::TreeNode("Child Node 2"))
            {
                ImGui::Text("This is Child Node 2");
                if (ImGui::TreeNode("Grandchild Node"))
                {
                    ImGui::Text("This is a Grandchild Node under Child Node 2");
                    ImGui::TreePop(); // End of Grandchild Node
                }
                ImGui::TreePop(); // End of Child Node 2
            }
            ImGui::TreePop(); // End of Root Node
        }

        ImGui::End();
        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
                     clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste
        // this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
