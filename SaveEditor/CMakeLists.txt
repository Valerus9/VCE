add_executable(save_editor
	${vce_CORE_SOURCES_LIST}
	"${PROJECT_SOURCE_DIR}/SaveEditor/save_editor_main.cpp")

target_link_libraries(save_editor PRIVATE VicCEngineCommon)

target_precompile_headers(save_editor REUSE_FROM VicCEngine)
