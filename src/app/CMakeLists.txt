qt_add_executable(OTTQDesktop
    main.cpp
    mainwindow.cpp
)

target_link_libraries(OTTQDesktop PRIVATE
    Qt6::Widgets
)

