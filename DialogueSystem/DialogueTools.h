#pragma once
#include "Include.h"
#include "DialogueSystem.h"


namespace DialogueTools
{
    static ImGuiWindowFlags Dialogueflags { ImGuiWindowFlags_MenuBar };

    void ShowFileMenu();
    void ShowEditMenu();
    void ShowDebugMenu(DialogueSystem& system, sf::RenderWindow& window);
}