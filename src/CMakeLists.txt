
add_executable(server server_main.cpp)
add_executable(client client_main.cpp)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    message("-- Boost link to: ${Boost_VERSION_STRING}")
else()
    message(FATAL_ERROR "Boost not found!")
endif()


add_library(client_lib client.cpp client.h)
add_library(server_lib server.cpp server.h)

target_link_libraries(server server_lib ${Boost_LIBRARIES})
target_link_libraries(client client_lib ${Boost_LIBRARIES})

target_include_directories(client_lib
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
target_include_directories(server_lib
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
  )
