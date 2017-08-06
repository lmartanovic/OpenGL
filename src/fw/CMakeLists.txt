set(FW_SOURCES shader.cpp)

add_library(fw_lib STATIC ${FW_SOURCES})
set_target_properties(fw_lib
                      PROPERTIES
                      PREFIX "")
