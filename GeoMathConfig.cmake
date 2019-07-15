if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

set(GeoMath_INCLUDE_DIRS "/usr/local/include/GeoMath.h")
set(GeoMath_LIBRARY "/usr/local/lib/libGeoMath_lib.a")
set(GeoMath_LIBS "/usr/local/lib/libGeoMath_lib.a")

message("${BoldYellow}~~~~~~~~~~~~~~~~~~~~${ColourReset}\n\n")
message("${BoldYellow}~~ ${GeoMath_LIBRARIES} ${ColourReset}")
message("\n\n${BoldYellow}~~~~~~~~~~~~~~~~~~~~${ColourReset}")