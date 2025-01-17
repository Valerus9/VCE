#94723 <-- DO NOT REMOVE ... the file system tests are looking for this

list(APPEND TESTS_CORE_SOURCES_LIST
	"${PROJECT_SOURCE_DIR}/tests/test_main.cpp"
	"${PROJECT_SOURCE_DIR}/tests/dcon_tests.cpp"
	"${PROJECT_SOURCE_DIR}/tests/determinism_tests.cpp"
	"${PROJECT_SOURCE_DIR}/tests/file_system_tests.cpp"
	"${PROJECT_SOURCE_DIR}/tests/gui_graphics_parsing_tests.cpp"
	"${PROJECT_SOURCE_DIR}/tests/misc_tests.cpp"
	"${PROJECT_SOURCE_DIR}/tests/parsers_tests.cpp"
	"${PROJECT_SOURCE_DIR}/tests/test_bench.cpp"
	"${PROJECT_SOURCE_DIR}/tests/test_simdify.cpp"
	"${PROJECT_SOURCE_DIR}/tests/test_simdify_demo.cpp"
	"${PROJECT_SOURCE_DIR}/tests/triggers_tests.cpp"
	"${PROJECT_SOURCE_DIR}/tests/ve_tests.cpp"
)

if(WIN32)
add_executable(tests_project
	${TESTS_CORE_SOURCES_LIST}
	${vce_CORE_SOURCES_LIST}
	
	"${PROJECT_SOURCE_DIR}/src/map/map_state.cpp"
	"${PROJECT_SOURCE_DIR}/src/map/map_data_loading.cpp"
	"${PROJECT_SOURCE_DIR}/src/map/map_borders.cpp"
	"${PROJECT_SOURCE_DIR}/src/map/map.cpp"
	"${PROJECT_SOURCE_DIR}/src/graphics/xac.cpp"
	"${PROJECT_SOURCE_DIR}/src/VicCEngine.rc")
else()
add_executable(tests_project
	${TESTS_CORE_SOURCES_LIST}
	${vce_CORE_SOURCES_LIST}

	"${PROJECT_SOURCE_DIR}/src/map/map_state.cpp"
	"${PROJECT_SOURCE_DIR}/src/map/map_data_loading.cpp"
	"${PROJECT_SOURCE_DIR}/src/map/map_borders.cpp"
	"${PROJECT_SOURCE_DIR}/src/map/map.cpp"
	"${PROJECT_SOURCE_DIR}/src/graphics/xac.cpp")
endif()
target_link_libraries(tests_project PRIVATE VicCEngineCommon)

FetchContent_MakeAvailable(Catch2)

# Link to the desired libraries
target_link_libraries(tests_project
    PRIVATE
    Catch2::Catch2
)

target_compile_definitions(tests_project PUBLIC vce_NO_ENTRY_POINT)
#target_precompile_headers(tests_project REUSE_FROM VicCEngine)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib)
list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(tests_project)

# add_custom_command(
#    TARGET tests_project
#     COMMENT "Run tests"
#     POST_BUILD
#     WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#     COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> -R "^tests_project$" --output-on-failures
# )
