set(target_CPP
    CoHSceneConverter.cpp
    )
set(target_INCLUDE
    CohModelConverter.h
    CoHModelLoader.h
    CoHSceneConverter.h
    CohTextureConverter.h
    )
set(target_SOURCES
    ${target_CPP}
    ${target_INCLUDE}
    )
add_library(map_loader STATIC ${target_SOURCES})
target_link_libraries(gameData)
qt5_use_modules(map_loader LINK_PUBLIC Core)
