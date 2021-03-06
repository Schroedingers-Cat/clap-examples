set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

#find_package(Qt6 COMPONENTS Core Widget Platform Qml Quick QuickControls2 REQUIRED)

add_library(clap-plugin-gui-common
    abstract-gui.hh
    abstract-gui.cc
    abstract-gui-listener.hh
    abstract-gui-listener.cc
    abstract-gui-factory.hh
    abstract-gui-factory.cc)
set_property(TARGET clap-plugin-gui-common PROPERTY CXX_STANDARD 20)
set_property(TARGET clap-plugin-gui-common PROPERTY POSITION_INDEPENDENT_CODE true)
target_link_libraries(clap-plugin-gui-common PUBLIC clap-core)

add_library(clap-plugin-gui
    gui-client.hh
    gui-client.cc

    parameter-proxy.hh
    parameter-proxy.cc
    plugin-proxy.hh
    plugin-proxy.cc
    transport-proxy.hh
    transport-proxy.cc
)
set_property(TARGET clap-plugin-gui PROPERTY CXX_STANDARD 20)
target_link_libraries(clap-plugin-gui PUBLIC clap-io clap-plugin-gui-common)
target_link_libraries(clap-plugin-gui PUBLIC Qt6::Quick)
set_property(TARGET clap-plugin-gui PROPERTY POSITION_INDEPENDENT_CODE true)
qt6_import_qml_plugins(clap-plugin-gui)

if(false)
    # Static link of qml gui
    qt6_add_qml_module(clap-plugin-gui
        URI clap
        VERSION 1.0
        RESOURCE_PREFIX /clap/imports
        QML_FILES
            qml/clap/Knob.qml
    )
endif()

add_library(clap-plugin-local-gui
    local-gui-factory.hh
    local-gui-factory.cc)
set_property(TARGET clap-plugin-local-gui PROPERTY CXX_STANDARD 20)
set_property(TARGET clap-plugin-local-gui PROPERTY POSITION_INDEPENDENT_CODE true)
target_link_libraries(clap-plugin-local-gui PUBLIC clap-plugin-gui)

add_library(clap-plugin-threaded-gui
    threaded-gui-factory.hh
    threaded-gui-factory.cc
    threaded-gui-proxy.hh
    threaded-gui-proxy.cc)
set_property(TARGET clap-plugin-threaded-gui PROPERTY CXX_STANDARD 20)
set_property(TARGET clap-plugin-threaded-gui PROPERTY POSITION_INDEPENDENT_CODE true)
target_link_libraries(clap-plugin-threaded-gui PUBLIC clap-plugin-gui)

add_library(clap-plugin-remote-gui
    remote-gui-factory-proxy.hh
    remote-gui-factory-proxy.cc
    remote-gui-proxy.hh
    remote-gui-proxy.cc)
set_property(TARGET clap-plugin-remote-gui PROPERTY CXX_STANDARD 20)
set_property(TARGET clap-plugin-remote-gui PROPERTY POSITION_INDEPENDENT_CODE true)
target_link_libraries(clap-plugin-remote-gui PUBLIC clap-plugin-gui-common clap-io)

add_executable(clap-gui
    gui-client-main.cc
    remote-gui-factory.hh
    remote-gui-factory.cc
    remote-gui-listener.hh
    remote-gui-listener.cc)
target_link_libraries(clap-gui PUBLIC clap-plugin-gui)
set_target_properties(clap-gui PROPERTIES CXX_STANDARD 20)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    add_library(clap-plugin-cf-timer cf-timer.hh cf-timer.cc)
    set_property(TARGET clap-plugin-cf-timer PROPERTY CXX_STANDARD 20)
    set_property(TARGET clap-plugin-cf-timer PROPERTY POSITION_INDEPENDENT_CODE true)
    target_link_libraries(clap-plugin-local-gui PUBLIC clap-plugin-cf-timer)
endif()

if (use_remote_gui)
    install(TARGETS clap-gui DESTINATION "bin")
endif()
