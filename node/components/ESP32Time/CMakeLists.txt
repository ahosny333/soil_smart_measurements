cmake_minimum_required(VERSION 3.5)

set(includedirs
  .
  )

set(srcs
  ESP32Time.cpp
  )

idf_component_register(SRCS ${srcs} 
                    INCLUDE_DIRS ${includedirs}
                    REQUIRES "arduino"  )
project(ESP32Time)