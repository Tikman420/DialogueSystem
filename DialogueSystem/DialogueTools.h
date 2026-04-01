#pragma once
#include "Include.h"
#include "DialogueSystem.h"


namespace DialogueTools
{
    //default flags for debug menu
    static ImGuiWindowFlags Dialogueflags { ImGuiWindowFlags_MenuBar };

    //debug menu rendering functions
    void ShowFileMenu();
    void ShowEditMenu();
    void ShowDebugMenu(DialogueSystem& system, sf::RenderWindow& window);
}