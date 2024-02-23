cmake_minimum_required(VERSION 3.5)

set(includedirs
  src/
  src/ArduinoJson/Data
  src/ArduinoJson/Deserialization
  src/ArduinoJson/Polyfills
  src/ArduinoJson/Serialization
  src/ArduinoJson/StringTraits
  src/ArduinoJson/TypeTraits
  src/ArduinoJson
  )



idf_component_register(SRCS "" 
                    INCLUDE_DIRS ${includedirs}
                    REQUIRES "arduino" )
project(ArduinoJson)
