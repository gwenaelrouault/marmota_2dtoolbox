#include <SDL.h>
#include <SDL_image.h>
#include "editor_gui_import_sheet.h"
#include "imgui.h"
#include "ImGuiFileDialog.h"

using namespace marmot;
using namespace std;

void GUIImportSpriteSheet::display()
{
    float height = ImGui::GetContentRegionAvail().y / 2.0f;
    std::string selectedPath;
    ImGui::BeginChild("SDL Frame", ImVec2(0, height), true);
    ImGui::TextUnformatted("Importer une spritesheet");
    ImGui::SameLine();
    float fullWidth = ImGui::GetContentRegionAvail().x;
    float buttonWidth = 120.0f;
    ImGui::SameLine(ImGui::GetCursorPosX() + fullWidth - buttonWidth - 20);
    IGFD::FileDialogConfig config;
    config.path = ".";
    config.flags = ImGuiFileDialogFlags_Modal;
    config.sidePaneWidth = 200;
    if (ImGui::Button("Ouvrir", ImVec2(buttonWidth, 0)))
    {
        ImGuiFileDialog::Instance()->OpenDialog(
            "ChooseSpriteSheet",
            "Sélectionnez une spritesheet",
            ".png,.jpg,.jpeg,.bmp,.tga",
            config);
    }

    if (ImGuiFileDialog::Instance()->Display("ChooseSpriteSheet"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            selectedPath = ImGuiFileDialog::Instance()->GetFilePathName();
        }
        ImGuiFileDialog::Instance()->Close();
    }
    if (!selectedPath.empty())
    {
        std::unique_ptr<ImportSheet> async_import = make_unique<ImportSheet>(_logger, ImportSheetJob{_logger, _model, selectedPath, _width, _height}, ImportSheetCallback{_logger});
        _worker->async(std::move(async_import));
    }
    display_params();
    ImGui::Dummy(ImVec2(400, 200));
    display_sheet();
    ImGui::EndChild();
}

void GUIImportSpriteSheet::display_params()
{
    ImGui::TextUnformatted("Paramètres");
    ImGui::SameLine();

    ImGui::TextUnformatted("Width");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    ImGui::InputInt("##width", &_width);

    ImGui::SameLine();
    ImGui::TextUnformatted("Height");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    ImGui::InputInt("##height", &_height);

    SDL_Texture* tex = IMG_LoadTexture(_renderer, "sprite.png");
    //ImTextureID texId = (ImTextureID)tex;

    //ImGui::Image(texId, ImVec2(64, 64));
}

void GUIImportSpriteSheet::display_sheet() {
    vector<SurfacePtr> tiles = _model->get_tiles();
    for (auto &t : tiles) {
        _logger.infoStream() << "GUI:ImportSpriteSheet:display tile";
    }
}