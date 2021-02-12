#!/usr/bin/env python3

#
#   Copyright (C) 2021 Reiko Asakura. All Rights Reserved.
#
#   Vita Development Suite Libraries
#

from pathlib import Path

def collect_headers(base, acc):
	headers = []
	for c in (base / acc).iterdir():
		if c.is_file():
			headers.append(acc / c.name)
		elif c.is_dir():
			headers.extend(collect_headers(base, acc / c.name))
		else:
			sys.exit("Unexpected file type")
	return headers

def write_one(prefix, p):
	q = str(p).replace("/", "-").replace("\\", "-")
	q = f'{prefix}-{q}.cpp'
	with open(q, 'w') as f:
		f.write(f'#include <{p}>\n')
		f.write('int main(void) { return 0; }\n')

incl_template = '#include <{}> // IWYU pragma: keep\n'
main_template = 'int main(void) { return 0; }\n'

with open('all-common.cpp', 'w') as f:
	for p in collect_headers(Path('include/common'), Path('')):
		write_one('common', p)
		f.write(incl_template.format(p))
	f.write(main_template)

with open('all-user.cpp', 'w') as f:
	for p in collect_headers(Path('include/user'), Path('')):
		write_one('user', p)
		f.write(incl_template.format(p))
	for p in collect_headers(Path('include/common'), Path('')):
		f.write(incl_template.format(p))
	f.write(main_template)

with open('all-kernel.cpp', 'w') as f:
	for p in collect_headers(Path('include/kernel'), Path('')):
		write_one('kernel', p)
		f.write(incl_template.format(p))
	for p in collect_headers(Path('include/common'), Path('')):
		f.write(incl_template.format(p))
	f.write(main_template)
