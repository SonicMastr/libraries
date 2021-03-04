#!/usr/bin/env python3

#
#   Copyright (C) 2021 Reiko Asakura. All Rights Reserved.
#
#   Vita Development Suite Libraries
#

import sys
from pathlib import Path

import yaml
try:
	from yaml import CLoader as YamlLoader
except ImportError:
	from yaml import SafeLoader as YamlLoader

def load(nids):
	if isinstance(nids, Path):
		nids = yaml.load(nids.read_bytes(), Loader=YamlLoader)
	elif not isinstance(nids, dict):
		nids = yaml.load(nids, Loader=YamlLoader)

	return nids

def process(nids, modules_cb=None, module_cb=None, libraries_cb=None, library_cb=None, functions_cb=None, variables_cb=None, export_cb=None, user_data=None):

	nids = load(nids)

	if modules_cb:
		modules_cb(user_data, nids['modules'])
	for modname, module in sorted(nids['modules'].items()):
		if module_cb:
			module_cb(user_data, modname, module)
		if 'libraries' in module:
			if libraries_cb:
				libraries_cb(user_data, module['libraries'])
			for libname, library in sorted(module['libraries'].items()):
				if library_cb:
					library_cb(user_data, libname, library)
				if 'functions' in library:
					if functions_cb:
						functions_cb(user_data, library['functions'])
					if export_cb:
						for name, nid in sorted(library['functions'].items()):
							export_cb(user_data, 'functions', name, nid)
				if 'variables' in library:
					if variables_cb:
						variables_cb(user_data, library['variables'])
					if export_cb:
						for name, nid in sorted(library['variables'].items()):
							export_cb(user_data, 'variables', name, nid)

def dump_string(nids):
	def modules_cb(ud, modules):
		if modules:
			ud.append('modules:\n')
		else:
			ud.append('modules: {}\n')

	def module_cb(ud, modname, module):
		ud.append(f'  {modname}:\n')
		ud.append(f'    nid: 0x{module["nid"]:08X}\n')

	def libraries_cb(ud, libraries):
		if libraries:
			ud.append('    libraries:\n')

	def library_cb(ud, libname, library):
		ud.append(f'      {libname}:\n')
		ud.append(f'        nid: 0x{library["nid"]:08X}\n')

	def functions_cb(ud, functions):
		if functions:
			ud.append('        functions:\n')

	def variables_cb(ud, variables):
		if variables:
			ud.append('        variables:\n')

	def export_cb(ud, kind, name, nid):
		ud.append(f'          {name}: 0x{nid:08X}\n')

	ud = []
	process(nids, modules_cb, module_cb, libraries_cb, library_cb, functions_cb, variables_cb, export_cb, ud)
	return ''.join(ud)

def iterdir(path, func):
	for c in Path(path).iterdir():
		if c.is_file():
			func(c)
		elif c.is_dir():
			iterdir(c, func)
		else:
			sys.exit('Unexpected file type')
