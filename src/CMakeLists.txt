set(CMAKE_AUTOMOC_ON)

find_package(Qt5Widgets REQUIRED)

include_directories(${Qt5Widgets_INCLUDES})
add_definitions(${Qt5Widgets_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

add_executable (fs-batter
    main.cpp
)

include_directories(
    ${SQLITE3_INCLUDE_DIRS}
    inc
)

set_target_properties(fs-batter PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
INSTALL(PROGRAMS ${CMAKE_SOURCE_DIR}/bin/fs-batter DESTINATION bin)

target_link_libraries(fs-batter
    ${Qt5Widgets_LIBRARIES}
    #${SQLITE3_LIBRARIES}
)

link_directories(
    #${SQLITE3_LIBRARY_DIRS}
)

