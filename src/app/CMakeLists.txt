qt_add_executable(OTTQDesktop
    main.cpp
    mainwindow.cpp
    quiz_config_widget.cpp
    quiz_config.cpp
    factor_range.cpp
)

target_link_libraries(OTTQDesktop PRIVATE
    Qt6::Widgets
)

