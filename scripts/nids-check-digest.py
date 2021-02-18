#!/usr/bin/env python3

#
#   Copyright (C) 2021 Reiko Asakura. All Rights Reserved.
#
#   Vita Development Suite Libraries
#

import sys
from hashlib import sha1
from pathlib import Path

from yaml import load
try:
	from yaml import CLoader as Loader
except ImportError:
	from yaml import SafeLoader as Loader

def name2nid(n, s):
	digest = sha1((n + s).encode('utf-8')).digest()
	return int.from_bytes(digest[:4], byteorder='little')

def print_ex_expect(exports, suffix):
	for name, nid in exports.items():
		computed_nid = name2nid(name, suffix)
		if nid != computed_nid:
			print(f'  {nid:08X} ≠ {computed_nid:08X} {name}')

def print_lib_expect(libname, lib, suffix):
	if lib['nid'] == name2nid(libname, suffix):
		print(f'{libname} [{suffix}]')
		if 'functions' in lib:
			print_ex_expect(lib['functions'], suffix)
		if 'variables' in lib:
			print_ex_expect(lib['variables'], suffix)
		return 1
	return 0

def check_digest(d):
	for c in d.iterdir():
		if c.is_file():
			for modname, mod in load(c.read_bytes(), Loader=Loader)['modules'].items():
				for libname, lib in mod['libraries'].items():
					if not print_lib_expect(libname, lib, ''):
						if not print_lib_expect(libname, lib, libname):
							print_lib_expect(libname, lib, modname)
		elif c.is_dir():
			check_digest(c)
		else:
			sys.exit("Unexpected file type")

check_digest(Path('nids'))
