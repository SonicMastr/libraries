#
#   Copyright (C) 2021 Reiko Asakura. All Rights Reserved.
#
#   Vita Development Suite Libraries
#

file(GLOB NIDS_360 "${NIDS_DIR}/360/*.yml")
file(GLOB NIDS_365 "${NIDS_DIR}/365/*.yml")
file(GLOB NIDS_OTHER "${NIDS_DIR}/*.yml")

foreach(NID ${NIDS_360})
  message(STATUS "Generating stubs from ${NID}")
  execute_process(
    COMMAND ${VDSUITE_LIBGEN} ${NID} ${CMAKE_INSTALL_PREFIX}/lib/vdsuite
  )
endforeach()

foreach(NID ${NIDS_365})
  message(STATUS "Generating stubs from ${NID}")
  execute_process(
    COMMAND ${VDSUITE_LIBGEN} --merge --export-suffix _365 ${NID} ${CMAKE_INSTALL_PREFIX}/lib/vdsuite
    COMMAND ${VDSUITE_LIBGEN} ${NID} ${CMAKE_INSTALL_PREFIX}/lib/vdsuite/365
  )
endforeach()

foreach(NID ${NIDS_OTHER})
  message(STATUS "Generating stubs from ${NID}")
  execute_process(
    COMMAND ${VDSUITE_LIBGEN} ${NID} ${CMAKE_INSTALL_PREFIX}/lib/vdsuite
  )
endforeach()
