add_executable(dbg_vce WIN32 "${PROJECT_SOURCE_DIR}/DbgVicCEngine/dbg_vce_main.cpp")

target_link_libraries(dbg_vce PRIVATE VicCEngineCommon)
target_link_libraries(dbg_vce PRIVATE dbghelp)
target_precompile_headers(dbg_vce REUSE_FROM VicCEngine)
