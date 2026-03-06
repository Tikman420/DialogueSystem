#pragma once
#include <imgui.h>
#include <imgui-SFML.h>
#include <vector>
#include "Object.h"

namespace DialogueTools
{
    static ImGuiWindowFlags Dialogueflags { ImGuiWindowFlags_MenuBar };

    void ShowDebugMenu(std::string& Name, std::vector<std::string>* Buffer);
    void ShowFileMenu();
    void ShowEditMenu();
    void ImportText();

    class DialogueSystem : public GameObject
    {
    public:
        DialogueSystem(sf::Vector2f position, sf::Vector2f size, std::string spritePosition);
    };
}