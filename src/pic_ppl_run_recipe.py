#!/usr/bin/env python
from __future__ import print_function

import argparse
import hpccm
from hpccm.building_blocks import packages, boost, gnu
from hpccm.primitives import copy, shell, environment, workdir
from hpccm.primitives import baseimage, runscript

parser = argparse.ArgumentParser(description='4DViewer with HPCCM')
parser.add_argument('--format', type=str, default='singularity',
                    choices=['docker', 'singularity'],
                    help='Container specification format (default: singularity)')

args, unknown = parser.parse_known_args()

Stage0 = hpccm.Stage()

### Start "Recipe"
Stage0.name = 'build'
Stage0 += baseimage(image='nvidia/opengl:1.0-glvnd-devel-ubuntu18.04')
Stage0 += packages(ospackages=['cmake', 'freeglut3-dev', 'gcc', 'g++', 'libglu1-mesa-dev', 'pciutils'])
#Stage0 += copy(src='buildHPVServices.sh', dest='/opt/', _mkdir=True)
#Stage0 += copy(src='deps', dest='/opt/', _mkdir=True)
#Stage0 += copy(src='oiv/openinventorc++-headless_10.2.2_amd64.tar.gz', dest='/opt/', _mkdir=True)
#Stage0 += shell(commands=['cd /opt', 'mkdir -p builds', 'mkdir -p deps','mkdir -p oiv1022', 'cd oiv1022', 'tar -zxvf ../openinventorc++-headless_10.2.2_amd64.tar.gz arch-Linux-x86_64-gcc7-release/lib include', 'cd -', 'rm -f openinventorc++-headless_10.2.2_amd64.tar.gz'])
Stage0 += shell(commands=['mkdir -p /opt', 'cd /opt', 'mkdir -p workspace', 'mkdir -p gcc7'])
Stage0 += runscript(commands=['/opt/workspace/src/SingularityContainer/buildHPVServices.sh'])
### End "Recipe"

hpccm.config.set_container_format(args.format)

print(Stage0)