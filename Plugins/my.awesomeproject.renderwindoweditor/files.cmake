SET(SRC_CPP_FILES
)

SET(INTERNAL_CPP_FILES
  my_awesomeproject_renderwindoweditor_Activator.cpp
  QmitkAwesomeRenderWindowEditor.cpp
)

SET(MOC_H_FILES
  src/internal/my_awesomeproject_renderwindoweditor_Activator.h
  src/internal/QmitkAwesomeRenderWindowEditor.h
)

SET(UI_FILES
)

SET(CACHED_RESOURCE_FILES
  plugin.xml
)

SET(QRC_FILES
)

SET(CPP_FILES )

foreach(file ${SRC_CPP_FILES})
  SET(CPP_FILES ${CPP_FILES} src/${file})
endforeach(file ${SRC_CPP_FILES})

foreach(file ${INTERNAL_CPP_FILES})
  SET(CPP_FILES ${CPP_FILES} src/internal/${file})
endforeach(file ${INTERNAL_CPP_FILES})
