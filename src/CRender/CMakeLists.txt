cmake_minimum_required(VERSION 3.5)
project(Informatica_Olympiade_2016_2017_CRender)

# Project files
set(SOURCE_FILES main.cpp Renderer.cpp Renderer.h CRender.cpp CRender.h Entities/Entity.h Entities/PointsEntity.cpp Entities/PointsEntity.h InputHandler.cpp InputHandler.h Entities/PathEntity.cpp Entities/PathEntity.h Entities/InformationEntity.cpp Entities/InformationEntity.h)
add_executable(Informatica_Olympiade_2016_2017_CRender ${SOURCE_FILES})

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

#SFML
target_link_libraries(Informatica_Olympiade_2016_2017_CRender sfml-window)
target_link_libraries(Informatica_Olympiade_2016_2017_CRender sfml-graphics)
target_link_libraries(Informatica_Olympiade_2016_2017_CRender sfml-system)

#CCore
target_link_libraries(Informatica_Olympiade_2016_2017_CRender Informatica_Olympiade_2016_2017_CCore)

#Copy assets
add_custom_command(
        TARGET Informatica_Olympiade_2016_2017_CRender POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/src/CRender/Assets/
                $<TARGET_FILE_DIR:Informatica_Olympiade_2016_2017_CRender>/Assets)

