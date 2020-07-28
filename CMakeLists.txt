cmake_minimum_required(VERSION 3.0)

set(ARCH "arm-dolce-eabi" CACHE STRING "Target architecture")
set(CMAKE_INSTALL_PREFIX "$ENV{DOLCESDK}/" CACHE PATH "Install prefix")

if(DEFINED ENV{DOLCESDK})
  set(LIBS_GEN "$ENV{DOLCESDK}/bin/dolce-libs-gen" CACHE STRING "libs-gen command")
else()
  set(LIBS_GEN "dolce-libs-gen" CACHE STRING "libs-gen command")
endif()

project(dolcesdk-target-headers LANGUAGES NONE)

set(STUBS_DIR stubs)
set(DB_FILE "${CMAKE_SOURCE_DIR}/db.yml")
set(DB_365_FILE "${CMAKE_SOURCE_DIR}/db_365.yml")

add_custom_command(OUTPUT "${STUBS_DIR}"
  DEPENDS "${DB_FILE}" "${DB_365_FILE}"
  COMMAND ${CMAKE_COMMAND} -E make_directory "${STUBS_DIR}"
  COMMAND "${LIBS_GEN}" "${DB_FILE}" "${STUBS_DIR}/cex-3600"
  COMMAND "${LIBS_GEN}" "${DB_365_FILE}" "${STUBS_DIR}/cex-3650"
)

add_custom_target(prepare-stubs ALL
  DEPENDS "${STUBS_DIR}"
)

install(DIRECTORY include/ DESTINATION "${ARCH}/include")
install(FILES db.yml db_365.yml DESTINATION share)
