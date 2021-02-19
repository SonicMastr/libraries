#!/usr/bin/env python3

#
#   Copyright (C) 2021 Reiko Asakura. All Rights Reserved.
#
#   Vita Development Suite Libraries
#

import sys
from pathlib import Path

from yaml import load
try:
	from yaml import CLoader as Loader
except ImportError:
	from yaml import SafeLoader as Loader

def write_export_syms(syms):
	out = ''
	for name, nid in sorted(syms.items()):
		out += f'          {name}: 0x{nid:08X}\n'
	return out

def write_export_libs(exports):
	out = ''
	for libname, library in sorted(exports.items()):
		out += f'      {libname}:\n'
		out += f'        nid: 0x{library["nid"]:08X}\n'
		if 'functions' in library and library['functions']:
			out += '        functions:\n'
			out += write_export_syms(library['functions'])
		if 'variables' in library and library['variables']:
			out += '        variables:\n'
			out += write_export_syms(library['variables'])
	return out

def write_nids(nids):
	out = 'modules:\n'
	for modname, module in sorted(nids['modules'].items()):
		out += f'  {modname}:\n'
		out += f'    nid: 0x{module["nid"]:08X}\n'
		if 'libraries' in module and module['libraries']:
			out += '    libraries:\n'
			out += write_export_libs(module['libraries'])
	return out

def check_sort(d):
	for c in d.iterdir():
		if c.is_file():
			c_text = c.read_text()
			c_sorted = write_nids(load(c_text, Loader=Loader))
			if c_text != c_sorted:
				print(f'{c} is not sorted')
				print(c_sorted)
				sys.exit(1)
		elif c.is_dir():
			check_sort(c)
		else:
			sys.exit("Unexpected file type")

check_sort(Path('nids'))
