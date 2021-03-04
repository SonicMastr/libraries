#!/usr/bin/env python3

#
#   Copyright (C) 2021 Reiko Asakura. All Rights Reserved.
#
#   Vita Development Suite Libraries
#

import sys

import nids

def check_sort(f):
	nids_string = f.read_text()
	sorted_nids_string = nids.dump_string(nids_string)
	if nids_string != sorted_nids_string:
		f.write_text(sorted_nids_string)
		sys.exit(f'{f} was not sorted and has been sorted')

nids.iterdir('nids', check_sort)
