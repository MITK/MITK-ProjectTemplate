project(ExampleApp)

add_executable(MitkExampleApp
  src/main.cpp
  src/MainWindow.h
  src/MainWindow.cpp
)

target_link_libraries(MitkExampleApp
  PRIVATE
    MitkQtWidgets
)

# A plain (non-BlueBerry) application does not go through
# mitkFunctionCreateBlueBerryApplication, which is what normally assigns an
# application to a solution folder. Do the same thing it does: an application
# that lives in an MITK extension is grouped under "<extension>/Applications",
# while MITK's own applications use "${MITK_ROOT_FOLDER}/Applications".
set(_solution_folder "${MITK_ROOT_FOLDER}/Applications")

foreach(_extension_dir ${MITK_ABSOLUTE_EXTENSION_DIRS})
  if("${CMAKE_CURRENT_SOURCE_DIR}/" MATCHES "^${_extension_dir}/.*")
    get_filename_component(_extension_name "${_extension_dir}" NAME)
    set(_solution_folder "${_extension_name}/Applications")
    break()
  endif()
endforeach()

set_target_properties(MitkExampleApp PROPERTIES
  AUTOMOC ON
  FOLDER "${_solution_folder}"
)

mitkFunctionConfigureVisualStudioUserProjectFile(NAME MitkExampleApp)
