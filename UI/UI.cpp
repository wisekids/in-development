#include "UI.h"
#include "../sqlite3/sqlite3.h"
#include <iostream>
#include <d3d11.h>
#include "../proc/proc.h"

bool trigger = false;
bool login_success = false;
bool login_failed = false;
bool login_attempted = false;
bool show_account_making = false;
bool show_login = true;
bool show_create_account = false;

const char* username[64];
static char username_making[64] = "";
static char password_making[64] = "";
static char username_input[64] = "";
static char password_input[64] = "";
static char key_inpt[64] = "";

float window_width = 300.0f;
float window_height = 400.0f;
bool show_credentials_page = true;

void CreateAccount(); // Forward declaration

void LogIn()
{
    ImGuiStyle& style = ImGui::GetStyle();
    auto& colors = style.Colors;
    style.ScrollbarRounding = 0;
    style.WindowRounding = 0;
    colors[ImGuiCol_ResizeGrip] = ImColor(64, 64, 64, 128);
    colors[ImGuiCol_ResizeGripHovered] = ImColor(90, 90, 90, 192);
    colors[ImGuiCol_ResizeGripActive] = ImColor(110, 110, 110, 255);
    colors[ImGuiCol_Button] = ImColor(50, 50, 50, 200);
    colors[ImGuiCol_ButtonHovered] = ImColor(70, 70, 70, 220);
    colors[ImGuiCol_ButtonActive] = ImColor(90, 90, 90, 255);
    colors[ImGuiCol_FrameBg] = ImColor(40, 40, 40, 200);
    colors[ImGuiCol_FrameBgHovered] = ImColor(60, 60, 60, 220);
    colors[ImGuiCol_FrameBgActive] = ImColor(80, 80, 80, 255);
    colors[ImGuiCol_WindowBg] = ImColor(20, 20, 20, 255);

    ImGui::InputText("Username", username_input, IM_ARRAYSIZE(username_input));
    ImGui::InputText("Password", password_input, IM_ARRAYSIZE(password_input), ImGuiInputTextFlags_Password);

    if (ImGui::Button("Log In"))
    {
        sqlite3* db;
        sqlite3_stmt* stmt;
        int rc = sqlite3_open("Tokens.db", &db);

        if (rc != SQLITE_OK) {
            std::cerr << "Cannot open database: " << sqlite3_errmsg(db) << std::endl;
        }
        else {
            const char* sql = "SELECT * FROM users WHERE username = ? AND password = ?;";
            rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
            if (rc != SQLITE_OK) {
                std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
            }
            else {
                sqlite3_bind_text(stmt, 1, username_input, -1, SQLITE_TRANSIENT);
                sqlite3_bind_text(stmt, 2, password_input, -1, SQLITE_TRANSIENT);

                rc = sqlite3_step(stmt);
                if (rc == SQLITE_ROW) {
                    login_success = true;
                    show_login = false;
                    show_create_account = false;  // Hide create account page
                    show_credentials_page = false;  // ? Hide credentials page after login
                    std::cout << "Login successful\n";
                }
                else {
                    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Login failed...");
                }

                sqlite3_finalize(stmt);
            }
            sqlite3_close(db);
        }
    }

    if (ImGui::Button("Create Account")) {
        show_create_account = true;
        show_login = false;
    }
}

void CreateAccount()
{
    ImGuiStyle& style = ImGui::GetStyle();
    auto& colors = style.Colors;
    style.ScrollbarRounding = 0;
    style.WindowRounding = 0;
    colors[ImGuiCol_ResizeGrip] = ImColor(64, 64, 64, 128);
    colors[ImGuiCol_ResizeGripHovered] = ImColor(90, 90, 90, 192);
    colors[ImGuiCol_ResizeGripActive] = ImColor(110, 110, 110, 255);
    colors[ImGuiCol_Button] = ImColor(50, 50, 50, 200);
    colors[ImGuiCol_ButtonHovered] = ImColor(70, 70, 70, 220);
    colors[ImGuiCol_ButtonActive] = ImColor(90, 90, 90, 255);
    colors[ImGuiCol_FrameBg] = ImColor(40, 40, 40, 200);
    colors[ImGuiCol_FrameBgHovered] = ImColor(60, 60, 60, 220);
    colors[ImGuiCol_FrameBgActive] = ImColor(80, 80, 80, 255);
    colors[ImGuiCol_WindowBg] = ImColor(20, 20, 20, 255);

    ImGui::SeparatorText("Create Username");
    ImGui::InputText("Username", username_making, IM_ARRAYSIZE(username_making));

    ImGui::SeparatorText("Create Password");
    ImGui::InputText("Password", password_making, IM_ARRAYSIZE(password_making));

    ImGui::SeparatorText("Key");
    ImGui::InputText("Key", key_inpt, IM_ARRAYSIZE(key_inpt));


    if (ImGui::Button("Return To Log In"))
    {
        show_login = true;
        LogIn();
    }
}

void Menu()
{
    static float window_width = 400.0f;
    static float window_height = 300.0f;

    ImGui::SetNextWindowPos(ImVec2(
        (ImGui::GetIO().DisplaySize.x - window_width) * 0.5f,
        (ImGui::GetIO().DisplaySize.y - window_height) * 0.5f
    ), ImGuiCond_Always);

    ImGui::SetNextWindowSize(ImVec2(window_width, window_height), ImGuiCond_Always);

    ImGuiStyle& style = ImGui::GetStyle();
    auto& colors = style.Colors;
    style.ScrollbarRounding = 0;
    style.WindowRounding = 0;

    colors[ImGuiCol_ResizeGrip] = ImColor(60, 60, 60, 60);
    colors[ImGuiCol_ResizeGripHovered] = ImColor(90, 90, 90, 100);
    colors[ImGuiCol_ResizeGripActive] = ImColor(120, 120, 120, 160);
    colors[ImGuiCol_Button] = ImColor(40, 40, 40, 180);
    colors[ImGuiCol_ButtonHovered] = ImColor(65, 65, 65, 200);
    colors[ImGuiCol_ButtonActive] = ImColor(90, 90, 90, 220);
    colors[ImGuiCol_FrameBg] = ImColor(35, 35, 35, 255);
    colors[ImGuiCol_FrameBgHovered] = ImColor(55, 55, 55, 255);
    colors[ImGuiCol_FrameBgActive] = ImColor(75, 75, 75, 255);
    colors[ImGuiCol_WindowBg] = ImColor(20, 30, 50, 240);

    ImGui::Begin("Main Menu", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);

    if (ImGui::BeginTabBar("##tabs"))
    {
        if (ImGui::BeginTabItem("ESP"))
        {
            float halfWidth = ImGui::GetContentRegionAvail().x * 0.5f;
            float fullHeight = ImGui::GetContentRegionAvail().y;

            ImGui::BeginChild("##left_esp", ImVec2(halfWidth, fullHeight), true);
            static bool esp = false;
            static bool slider = false;
            ImGui::Checkbox("Enable ESP", &esp);
            static bool health= false;
            ImGui::Checkbox("Show Health", &health);
            // Only show this if ESP is enabled
            static bool show_slider = false;
            static float a = 0.0f;
            if (esp)
            {

                // here is where u will implant the esp - i++
                ImGui::Checkbox("Enable Slider?", &show_slider);

                // Optional: Show the message box only once when ESP is first enabled
                static bool espMessageShown = false;
                if (!espMessageShown)
                {
                    MessageBox(nullptr, L"Process not found", L"Accepted", MB_OK);
                    espMessageShown = true;
                }

                if (show_slider)
                {
                    ImGui::SliderFloat("Distance", &a, 0.0f, 200.0f);
                }
            }
            ImGui::EndChild();

            ImGui::SameLine();

            ImGui::BeginChild("##right_esp", ImVec2(halfWidth, fullHeight), true);
            ImGui::Text("ESP Settings");
            ImGui::EndChild();

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Aimbot"))
        {
            float halfWidth = ImGui::GetContentRegionAvail().x * 0.5f;
            float fullHeight = ImGui::GetContentRegionAvail().y;

            ImGui::BeginChild("##left_aim", ImVec2(halfWidth, fullHeight), true);
            ImGui::Checkbox("Trigger bot", &trigger);
            ImGui::EndChild();

            ImGui::SameLine();

            ImGui::BeginChild("##right_aim", ImVec2(halfWidth, fullHeight), true);
            ImGui::Text("Aimbot Settings");
            ImGui::EndChild();

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Misc"))
        {
            float halfWidth = ImGui::GetContentRegionAvail().x * 0.5f;
            float fullHeight = ImGui::GetContentRegionAvail().y;
            bool exitclose = false;

            ImGui::BeginChild("##left_misc", ImVec2(halfWidth, fullHeight), true);
            ImGui::Checkbox("Exit", &exitclose);
            ImGui::EndChild();

            if (exitclose)
            {
                exit(0);
            }

            ImGui::SameLine();

            ImGui::BeginChild("##Right misc", ImVec2(halfWidth, fullHeight), true);
            ImGui::Text("Misc Settings");
            ImGui::EndChild();

            ImGui::EndTabItem(); 
        }

        ImGui::EndTabBar();

        ImGui::End();
    }
}

void RenderUIForLoginAndShit()
{
    if (show_credentials_page) {
        if (show_login) {
            LogIn();
        }
        else if (show_create_account) {
            CreateAccount();
        }
    }
    else {
        Menu();  
    }
}