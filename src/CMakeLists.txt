# C++

enable_language(CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Boost C++ Libraries

find_package(Boost REQUIRED COMPONENTS program_options)

include_directories(${Boost_INCLUDE_DIRS})

# International Components for Unicode

if (APPLE)
    set(ICU_ROOT "/usr/local/opt/icu4c")
endif (APPLE)

find_package(ICU REQUIRED COMPONENTS uc)

include_directories(${ICU_INCLUDE_DIR})

# executable

set(${PROJECT_NAME}_SOURCES
    NfdFind.cpp
    main.cpp
)

add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    Boost::program_options
    ICU::uc
)

# install

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION $ENV{HOME}/bin)
