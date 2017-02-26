project(visorglobal)
 
FIND_PACKAGE(KDE4 REQUIRED)
INCLUDE_DIRECTORIES( ${KDE4_INCLUDES} . )
 
set(visorglobal_SRCS
   main.cpp
   mainwindow.cpp
 )
 
kde4_add_executable(visorglobal ${visorglobal_SRCS})
 
target_link_libraries(visorglobal ${KDE4_KDEUI_LIBS} ${KDE4_KPARTS_LIBS})
 
########### install files ###############
install(TARGETS visorglobal DESTINATION ${BIN_INSTALL_DIR} )
install( FILES visorglobalui.rc 
    DESTINATION  ${DATA_INSTALL_DIR}/visorglobal )
