#include "DialougeTools.h"
#include <misc/cpp/imgui_stdlib.h>
#include <iostream>

//DialogueTools::Dialogueflags += ImGuiWindowFlags_UnsavedDocument;

namespace DialogueTools 
{
    void ShowDebugMenu(std::string& Name, std::vector<std::string>* Buffer)
    {
        if (!ImGui::Begin("Dialogue", nullptr, DialogueTools::Dialogueflags))
        {
            ImGui::End();
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                DialogueTools::ShowFileMenu();
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                DialogueTools::ShowEditMenu();
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        ImGui::InputText("Dialogue Name", &Name);

        if (ImGui::CollapsingHeader("Text"))
        {
            for (auto i = Buffer->begin(); i != Buffer->end(); i++)
            {
                std::string dialogueindex = Name + '.' + std::to_string(std::distance(Buffer->begin(), i));
                ImGui::InputText(dialogueindex.c_str(), i._Ptr);
            }

            ImGui::Dummy(ImVec2(5, 5));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(5, 5));

            if (ImGui::Button("+ add Text"))
            {
                Buffer->push_back("");
            }
            ImGui::SameLine();
            if (ImGui::Button("- Remove Text"))
            {
                Buffer->pop_back();
            }
        }

        ImGui::Dummy(ImVec2(5, 5));
        ImGui::Text("Other Tools");
        ImGui::Separator();
        ImGui::Button("Redo Current Text");
        ImGui::End();
    }

    void ShowFileMenu()
    {
        if (ImGui::MenuItem("New")) {}
        if (ImGui::MenuItem("Open", "Ctrl+O")) {}
        ImGui::Separator();

        if (ImGui::MenuItem("Save", "Ctrl+S")) 
        {
            DialogueTools::Dialogueflags -= ImGuiWindowFlags_UnsavedDocument;
            std::cout << "Saved!!" << std::endl;
        }
        if (ImGui::MenuItem("Save As..")) 
        { 
            DialogueTools::Dialogueflags -= ImGuiWindowFlags_UnsavedDocument; 
        }
        ImGui::Separator();

        if (ImGui::MenuItem("Import")) { ImportText(); }
    }

    void ShowEditMenu()
    {
        if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
        if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
        ImGui::Separator();

        if (ImGui::MenuItem("Cut", "CTRL+X")) {}
        if (ImGui::MenuItem("Copy", "CTRL+C")) {}
        if (ImGui::MenuItem("Paste", "CTRL+V")) {}
    }

    void ImportText() 
    {

    }

    DialogueSystem::DialogueSystem(sf::Vector2f position, sf::Vector2f size, std::string spritePosition) : GameObject{position, size, spritePosition}
    {

    }
}