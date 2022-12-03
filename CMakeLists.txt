cmake_minimum_required(VERSION 3.22)
project(EIPO)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

find_package(SDL2 REQUIRED SDL2)

include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_INCLUDE_DIRS}/../
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/RES/
)

add_subdirectory(lvgl)
add_subdirectory(lv_drivers)

add_executable(main main.cpp main.rc mouse_cursor_icon.c ${SOURCES} ${INCLUDES} LEVELS/levelTree.h LEVELS/TITLE/title_ui.cpp LEVELS/thread_.cpp BATTLE/battleTree.h PlayerData.cpp PlayerData.h EnemyData.cpp EnemyData.h BATTLE/test/testBattle.cpp LEVELS/Lanix_outskirt_unknownCave/ui.cpp LEVELS/Lanix_outskirt_unknownCave/01.cpp LEVELS/Lanix_outskirt_unknownCave/store.h RES/title_img.c RES/cave_img.c RES/Player_FullImage.c RES/crystals.c LEVELS/Lanix_outskirt_unknownCave/02.cpp RES/res.h LEVELS/Lanix_outskirt_unknownCave/03.cpp)


target_link_libraries(main PRIVATE lvgl lvgl::examples lvgl::demos lvgl::drivers ${SDL2_LIBRARIES})

