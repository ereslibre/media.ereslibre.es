project(ejemploxmlgui)

find_package(KDE4 REQUIRED)
include_directories(${KDE4_INCLUDES})

set(ejemploxmlgui_SRCS 
    main.cpp
    mainwindow.cpp
)

kde4_add_executable(ejemploxmlgui ${ejemploxmlgui_SRCS})

target_link_libraries(ejemploxmlgui ${KDE4_KDEUI_LIBS})

install(TARGETS ejemploxmlgui DESTINATION ${BIN_INSTALL_DIR})
install(FILES ejemploxmlguiui.rc 
        DESTINATION  ${DATA_INSTALL_DIR}/ejemploxmlgui)
