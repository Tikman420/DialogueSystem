#include "DialougeTools.h"
#include <misc/cpp/imgui_stdlib.h>
#include <iostream>
#include <fstream>

//DialogueTools::Dialogueflags += ImGuiWindowFlags_UnsavedDocument;

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

    std::vector<std::string> ImportText(std::string file)
    {
        //UwU: impwementot
        std::vector<std::string> result;
        std::ifstream source = std::ifstream(file, std::ios::ate);

        int size = source.tellg();
        source.seekg(0);

        std::string str;
        //https://stackoverflow.com/questions/13035674/how-to-read-a-file-line-by-line-or-a-whole-text-file-at-once
        while (std::getline(source, str)) 
        {
            std::cout << str << std::endl;
            result.emplace_back(str);
        }

        return result;
    }

    DialogueSystem::DialogueSystem()
    {
        mainWindow.setFillColor(backgroundColor);
        resetTransform();
        mainWindow.setOrigin(sf::Vector2(backGroundSize.x / 2, backGroundSize.y / 2));
        profile.setOrigin(sf::Vector2f(profile.getTextureRect().size.x/2, profile.getTextureRect().size.y/2));
        profile.setScale(sf::Vector2f(1.5,1.5));
        dialogueText.setPosition(backGroundPosition - sf::Vector2f(300, backGroundSize.y / 2 - 20));
        dialogueText.setCharacterSize(45);

        //debug
        dialogueBuffer->push_back("Hello World!");
    }

    void DialogueSystem::ProcessEvent(const sf::RenderWindow& window, const sf::Event& event) 
    {
        if (currentDialogueName == "") 
        {
            return;
        }

        if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Space) 
            {
                NextDialogue();
            }
        }
    }

    void DialogueSystem::Draw(sf::RenderWindow& window)
    {
        mainWindow.setPosition(backGroundPosition);
        mainWindow.setSize(backGroundSize);
        window.draw(mainWindow);

        profile.setPosition(backGroundPosition + sf::Vector2f(-510,0));
        window.draw(profile);

        window.draw(dialogueText);
    }

    void DialogueSystem::RenderText(sf::Text& dialogueBox, std::string text) 
    {
        WordWrapping(text, WrappingCount);
        dialogueBox.setString(text);
    }

    void DialogueSystem::WordWrapping(std::string& text, int wrapLength)
    {
        int lastSpace = 0;
        int lastEnter = 0;
        for (int i = 0; i < text.size(); i++)
        {
            if (text[i] == ' ' || text[i] == '\n')
            {
                lastSpace = i;
            }

            if (i - lastSpace > wrapLength) 
            {
                text.insert(i, "-\n");
                lastSpace = lastEnter = i;
                continue;
            }

            if (i - lastEnter > wrapLength)
            {
                text[lastSpace] = '\n';
                lastEnter = lastSpace;
            }
        }
    }

    void DialogueSystem::InitDialogue(std::string dialogueName)
    {
        currentDialogueName = dialogueName;

        *dialogueBuffer = ImportText("Game/" + dialogueName + ".txt");

        StartDialogue(0);
    }

    void DialogueSystem::StartDialogue(int index) 
    {
        if (index >= dialogueBuffer->size()) 
        {
            currentDialogueName = "";
            return;
        }

        RenderText(dialogueText, (*dialogueBuffer)[index]);
        currentDialogue = index;
    }

    void DialogueSystem::NextDialogue() 
    {
        StartDialogue(currentDialogue+1);
    }

    const void DialogueSystem::resetTransform() 
    {
        backGroundPosition = defaultPosition;
        backGroundSize = defaultSize;
    }
}