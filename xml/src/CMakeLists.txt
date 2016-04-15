include_directories(${PROJECT_SOURCE_DIR}/tinyxml/inc)
set(LIB_SRC tinystr.cpp 
 tinyxml.cpp
 tinyxmlerror.cpp
 tinyxmlparser.cpp
)
add_library(tinyxml  ${LIB_SRC})
add_definitions(-DLINUX -DHAVE_USR_INCLUDE_MALLOC_H)

