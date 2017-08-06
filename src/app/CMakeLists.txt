include_directories(../fw)

set(APP_SOURCES main.cpp)
set(APP_NAME OpenGL)

add_executable(${APP_NAME} ${APP_SOURCES})
set_target_properties(${APP_NAME}
                      PROPERTIES
                      LINK_FLAGS "-L${SFML_LIB_ROOT}")
target_link_libraries(${APP_NAME} fw_lib
                                  sfml-system
                                  sfml-window
                                  sfml-graphics
                                  GL
                                  GLEW)
