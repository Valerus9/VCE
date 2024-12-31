add_executable(VicCEngine_Launcher WIN32
	${vce_CORE_SOURCES_LIST}
	"${PROJECT_SOURCE_DIR}/src/launcher/launcher_main.cpp"
	"${PROJECT_SOURCE_DIR}/src/VicCEngine.rc")

target_compile_definitions(VicCEngine_Launcher PUBLIC vce_NO_ENTRY_POINT)

target_link_libraries(VicCEngine_Launcher PRIVATE VicCEngineCommon)
target_link_libraries(VicCEngine_Launcher PRIVATE dbghelp)
target_precompile_headers(VicCEngine_Launcher REUSE_FROM VicCEngine)
