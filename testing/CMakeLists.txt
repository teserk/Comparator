find_package(GTest REQUIRED)

add_executable(Tests ../src/Comparator.cpp tests.cpp)
target_link_libraries(Tests PRIVATE GTest::GTest GTest::Main)
target_include_directories(Tests PUBLIC ${CMAKE_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(Tests)
