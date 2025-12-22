cmake_minimum_required(VERSION 3.16)
project(gwen2d VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API ON)

find_package(PkgConfig REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(cxxopts REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(yaml-cpp REQUIRED)
find_path(LOG4CPP_INCLUDE_DIR NAMES log4cpp/Category.hh)
find_library(LOG4CPP_LIBRARY NAMES log4cpp)
find_library(ROCKSDB_LIB rocksdb)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

add_executable(marmot_studio
	imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_demo.cpp
    imgui/backends/imgui_impl_sdl2.cpp
    imgui/backends/imgui_impl_sdlrenderer2.cpp
	imgui/ImGuiFileDialog.cpp
	
	src/marmota/assets_db.cpp
	src/marmota/model/marmota_cache.cpp
	src/marmota/model/marmota_sprite.cpp
	src/marmota/model/marmota_state.cpp
	src/marmota/model/marmota_frame.cpp
	src/marmota/tables/index_table.cpp
	src/marmota/tables/table_frame.cpp
	src/marmota/tables/table_state.cpp
	src/marmota/tables/table_sprite.cpp
	src/marmota/tables/table_level.cpp
	src/marmota/tables/table_level_sprite.cpp
	src/marmota/marmota_asset_store.cpp
	
	src/async/worker.cpp

	src/marmot_studio/evt/init_event.cpp
	src/marmot_studio/evt/create_sprite_event.cpp
	src/marmot_studio/evt/update_sprite_event.cpp
	src/marmot_studio/evt/delete_sprite_event.cpp
	src/marmot_studio/evt/create_state_event.cpp
	src/marmot_studio/evt/update_state_event.cpp
	src/marmot_studio/evt/delete_state_event.cpp
	src/marmot_studio/evt/create_frame_event.cpp

	src/marmot_studio/db/asset_db.cpp

	src/marmot_studio/async/import_sheet.cpp
	src/marmot_studio/async/open_project.cpp
	src/marmot_studio/async/create_sprite.cpp
	src/marmot_studio/async/update_sprite.cpp
	src/marmot_studio/async/remove_sprite.cpp
	src/marmot_studio/async/create_state.cpp
	src/marmot_studio/async/delete_state.cpp
	src/marmot_studio/async/update_state.cpp
	src/marmot_studio/async/create_frame.cpp
	src/marmot_studio/async/event_queue.cpp
	
	src/marmot_studio/model/editor_state.cpp
	src/marmot_studio/services/editor_cmd.cpp
	src/marmot_studio/services/import_sheet_model.cpp
	src/marmot_studio/panels/editor_menu.cpp
	src/marmot_studio/panels/editor_import_sheet_panel.cpp
	src/marmot_studio/panels/editor_sprites_panel.cpp
	src/marmot_studio/panels/editor_main_panel.cpp
	src/marmot_studio/editor.cpp
	src/marmot_studio/marmot_studio.cpp
)

add_executable(marmot_baby
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_demo.cpp
    imgui/backends/imgui_impl_sdl2.cpp
    imgui/backends/imgui_impl_opengl3.cpp
	src/main.cpp
)

include_directories(
	include
	include/utils
	include/marmot_studio/
	include/marmot_studio/async
	include/marmot_studio/model
	include/marmot_studio/evt
	include/marmot_studio/panels
	include/marmot_studio/services
	include/marmot_studio/db
	include/marmota/model
	include/marmota/tables
	include/marmota
	include/async
)

target_include_directories(marmot_baby PRIVATE
	${SDL2_INCLUDE_DIRS}
	${SQLite3_INCLUDE_DIRS}
	${cxxopts_INCLUDE_DIRS}
	${nlohmann_json_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/imgui
    ${CMAKE_SOURCE_DIR}/imgui/backends
)

target_compile_options(marmot_baby PRIVATE
)

target_link_libraries(marmot_baby PRIVATE
	${SDL2_LIBRARIES}
	${SQLite3_LIBRARIES}
	${cxxopts_LIBRARIES}
	OpenGL::GL
)

target_include_directories(marmot_studio PRIVATE
	${SDL2_INCLUDE_DIRS}
	${SQLite3_INCLUDE_DIRS}
	${cxxopts_INCLUDE_DIRS}
	${nlohmann_json_INCLUDE_DIRS}
	log4cpp
    ${CLI11_LIBRARIES}
	${CMAKE_SOURCE_DIR}/imgui
    ${CMAKE_SOURCE_DIR}/imgui/backends
	${YAML_CPP_INCLUDE_DIR}
)

target_link_libraries(marmot_studio PRIVATE
	${SDL2_LIBRARIES}
	${SDL2_IMAGE_LIBRARIES}
	${SQLite3_LIBRARIES}
	${cxxopts_LIBRARIES}
	log4cpp
	${ROCKSDB_LIB}
	${YAML_CPP_LIBRARIES}
)