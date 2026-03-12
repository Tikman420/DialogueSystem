#include "DialogueTools.h"

namespace DialogueTools 
{
    void ShowDebugMenu(DialogueSystem& system, sf::RenderWindow& window)
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

        ImGui::InputText("Dialogue Name", &system.currentDialogueName);

        if (ImGui::CollapsingHeader("Text"))
        {
            for (auto i = system.dialogueBuffer->begin(); i != system.dialogueBuffer->end(); i++)
            {
                std::string dialogueindex = system.currentDialogueName + '.' + std::to_string(std::distance(system.dialogueBuffer->begin(), i));
                ImGui::InputText(dialogueindex.c_str(), i._Ptr);
            }

            ImGui::Dummy(ImVec2(5, 5));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(5, 5));

            if (ImGui::Button("+ add Text"))
            {
                system.dialogueBuffer->push_back("");
            }
            ImGui::SameLine();
            if (ImGui::Button("- Remove Text"))
            {
                system.dialogueBuffer->pop_back();
            }
        }

        ImGui::Dummy(ImVec2(5, 5));
        ImGui::Text("Other Tools");
        ImGui::Separator();

        if (ImGui::Button("Previous Dialogue"))
        {
            system.StartDialogue(system.currentDialogue-1);
        } ImGui::SameLine();

        if (ImGui::Button("Restart Current Text")) 
        {
            system.StartDialogue(system.currentDialogue);
        } ImGui::SameLine();

        if (ImGui::Button("Next Dialogue"))
        {
            system.NextDialogue();
        }

        if (ImGui::TreeNode("dialogue transform")) 
        {
            ImGui::VSliderFloat("Pos.X", ImVec2(18, 160), &system.backGroundPosition.x, 0, window.getSize().x); ImGui::SameLine();
            ImGui::VSliderFloat("Pos.Y", ImVec2(18, 160), &system.backGroundPosition.y, 0, window.getSize().y); ImGui::SameLine();
            ImGui::VSliderFloat("Size.X", ImVec2(18, 160), &system.backGroundSize.x, 0, window.getSize().x); ImGui::SameLine();
            ImGui::VSliderFloat("Size.Y", ImVec2(18, 160), &system.backGroundSize.y, 0, window.getSize().y);
            if (ImGui::Button("Reset Transform"))
            {
                system.resetTransform();
            }
            ImGui::TreePop();
        }

        if (ImGui::BeginPopup("Load settings"))
        {
            std::string file;
            ImGui::InputText("fileName", &file);
            if (ImGui::Button("Load..."))
            {
                ImportText(file);
            }
        }
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

        if (ImGui::MenuItem("Import")) 
        { 
            ImGui::OpenPopup("Load settings");
        }
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
}