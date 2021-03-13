#!/usr/bin/env python3

#
#   Copyright (C) 2021 Reiko Asakura. All Rights Reserved.
#
#   Vita Development Suite Libraries
#

import sys
from pathlib import Path

import nids

def check_file(base, f):
	mode = f.stat().st_mode

	if mode != 0o100644:
		sys.exit(f'{f} has incorrect permission mode {mode:o}')

	if f.suffix != '.h' or f.stem != Path(f.stem).stem:
		sys.exit(f'{f} has incorrect file name format')

	text = f.read_bytes().decode()

	if '\r' in text:
		sys.exit(f'{f} has carriage return')

	if not text.startswith('/*\n\tVita Development Suite Libraries\n*/'):
		sys.exit(f'{f} has incorrect boilerplate')

	if not text.endswith('\n'):
		sys.exit(f'{f} does not have trailing line feed')

	include_guard = ('#define _VDSUITE_' + f'{f.relative_to(base)}'
		.replace('/', '_')
		.replace('\\', '_')
		.replace('.', '_')
		.upper())

	if include_guard not in text:
		sys.exit(f'{f} has incorrect include guard\n{include_guard}')

nids.iterdir(Path('include'), lambda f: check_file(Path('include'), f))
