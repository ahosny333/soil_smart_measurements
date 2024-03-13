#idf_component_register(SRCS "main_project.cpp"
#                    INCLUDE_DIRS "")


set(requires arduino ArduinoJson Modbus)
set(COMPONENT_REQUIRES ${requires} )
set(srcs
    main_project.cpp
    app_modbus.cpp
    credentials.cpp
    app_wifi.cpp
    app_webserver_idf.cpp
    app_sd.cpp
    app_rf.cpp
    app_rtc.cpp
  )



idf_component_register(SRCS ${srcs} 
                    INCLUDE_DIRS "."
                    EMBED_FILES "web/ota.html" "web/index.html")

#target_compile_options(${COMPONENT_LIB} PRIVATE  -Wno-error=char-subscripts -Wno-error=format-truncation -Wno-error=format-overflow -Wno-error=format -Wno-error=format-overflow)



