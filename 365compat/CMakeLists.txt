#
#   Copyright (C) 2021 Reiko Asakura. All Rights Reserved.
#
#   Vita Development Suite Libraries
#

include_directories(SYSTEM
  ../include/kernel
  ../include/common
)

add_library(365compat STATIC
  sceKernelCpuUnrestrictedMemcpy.c
)

install(TARGETS
  365compat
  ARCHIVE DESTINATION lib/vdsuite
)
