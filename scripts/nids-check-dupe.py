#!/usr/bin/env python3

#
#   Copyright (C) 2021 Reiko Asakura. All Rights Reserved.
#
#   Vita Development Suite Libraries
#

import sys
from pathlib import Path

import nids

def check_dupe(f):
	def library_cb(ud, libname, library):
		ud[0] = set()

	def export_cb(ud, kind, name, nid):
		if nid in ud[0]:
			sys.exit(f'Duplicate NID: {name}')
		ud[0].add(nid)

	nids.process(f, library_cb=library_cb, export_cb=export_cb, user_data=[None])

nids.iterdir('nids', check_dupe)
