#idf_component_register(SRCS "main_project.cpp"
#                    INCLUDE_DIRS "")


set(requires arduino ArduinoJson Modbus)
set(COMPONENT_REQUIRES ${requires} )
set(srcs
    main_project.cpp
    app_rf.cpp
    app_firebase.cpp
  )



idf_component_register(SRCS ${srcs} 
                    INCLUDE_DIRS ".")

#target_compile_options(${COMPONENT_LIB} PRIVATE  -Wno-error=char-subscripts -Wno-error=format-truncation -Wno-error=format-overflow -Wno-error=format -Wno-error=format-overflow)



