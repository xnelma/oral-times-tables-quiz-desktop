qt_add_executable(OTTQDesktop
    main.cpp
    mainwindow.cpp
    mainwindow.ui
)

target_link_libraries(OTTQDesktop PRIVATE
    Qt6::Widgets
)

