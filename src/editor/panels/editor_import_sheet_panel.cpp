#include <SDL.h>
#include <SDL_image.h>
#include "editor_import_sheet_panel.h"
#include "imgui.h"
#include "ImGuiFileDialog.h"

using namespace marmot::studio;
using namespace std;

void ImportSheetPanel::display()
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
    display_sheet();
    ImGui::EndChild();
}

void ImportSheetPanel::display_params()
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
}

void ImportSheetPanel::display_sheet()
{
    auto dim = ImGui::GetContentRegionAvail();
    int avail_w = dim.x;
    int w_tile = _model->get_width();
    int h_tile = _model->get_height();
    int count_col = avail_w / w_tile;
    int col = 0;
    int index = 0;
    _tiles.clear();
    _model->get_tiles(_renderer, _tiles);
    for (auto &texture : _tiles)
    {
        display_sheet_tile(texture, ++index, w_tile, h_tile);
        if (++col < count_col)
        {
            ImGui::SameLine();
        }
        else
        {
            col = 0;
        }
    }
}

void ImportSheetPanel::display_sheet_tile(TexturePtr& tile, int index, int width, int height) {
    ImGui::Image((void *)tile.get(), ImVec2(width, height));
    if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
        string id = "SP_IMG" + to_string(index);
        ImGui::SetDragDropPayload(id.c_str(), &index, sizeof(int));
        ImGui::Image((ImTextureID)tile.get(), ImVec2(width, height));
        ImGui::EndDragDropSource();
    }
}