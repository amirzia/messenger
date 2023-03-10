include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    main_test
    main_test.cpp
)
target_link_libraries(
    main_test 
    GTest::gtest_main
    client_lib
    server_lib
)

include(GoogleTest)
gtest_discover_tests(main_test)