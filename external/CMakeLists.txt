function(mark_target_as_system_include target)
  get_target_property(include_dir ${target} INTERFACE_INCLUDE_DIRECTORIES)
  set_target_properties(
    ${target} PROPERTIES INTERFACE_SYSTEM_INCLUDE_DIRECTORIES "${include_dir}")
endfunction()

add_subdirectory(Catch2 EXCLUDE_FROM_ALL)
mark_target_as_system_include(Catch2)
