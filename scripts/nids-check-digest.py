#!/usr/bin/env python3

#
#   Copyright (C) 2021 Reiko Asakura. All Rights Reserved.
#
#   Vita Development Suite Libraries
#

from hashlib import sha1
from pathlib import Path

import nids

def name2nid(n, s):
	digest = sha1((n + s).encode('utf-8')).digest()
	return int.from_bytes(digest[:4], byteorder='little')

def module_cb(ud, modname, module):
	ud[0] = modname

def library_cb(ud, libname, library):
	for suffix in ['', ud[0], libname]:
		if library['nid'] == name2nid(libname, suffix):
			print(f'{libname} [{suffix}]')
			ud[1] = suffix
			return
	ud[1] = None

def export_cb(ud, kind, name, nid):
	if ud[1] is not None:
		computed_nid = name2nid(name, ud[1])
		if nid != computed_nid:
			print(f'  {nid:08X} ≠ {computed_nid:08X} {name}')

def check_digest(f):
	nids.process(f, module_cb=module_cb, library_cb=library_cb, export_cb=export_cb, user_data=[None, None])

nids.iterdir('nids', check_digest)
