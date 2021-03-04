#!/usr/bin/env python3

#
#   Copyright (C) 2021 Reiko Asakura. All Rights Reserved.
#
#   Vita Development Suite Libraries
#

import sys

import nids

def modules_cb(ud, modules):
	if len(modules) == 0:
		sys.exit(f'{ud} contains no modules')
	elif len(modules) > 1:
		sys.exit(f'{ud} contains more than one module')

	module_name = next(iter(modules))
	if ud.stem != module_name:
		sys.exit(f'{ud} contains module {module_name}')

def check_split(f):
	nids.process(f, modules_cb=modules_cb, user_data=f)

nids.iterdir('nids', check_split)
