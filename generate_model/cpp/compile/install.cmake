install(TARGETS ${compo_lib_name} LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(FILES ${inc_file} DESTINATION inc)
install(FILES {{FILE}} DESTINATION .)
install(DIRECTORY compile/${compo_lib_name} DESTINATION compile)
include("${CMAKE_CURRENT_LIST_DIR}/Ext_install.cmake" OPTIONAL)
