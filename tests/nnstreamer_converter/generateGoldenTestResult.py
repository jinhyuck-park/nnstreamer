#!/usr/bin/env python

##
# Copyright (C) 2018 Samsung Electronics
# License: LGPL-2.1
#
# @file generateGoldenTestResult.py
# @brief Generate golden test results for test cases
# @author MyungJoo Ham <myungjoo.ham@samsung.com>

from __future__ import print_function

import sys
import os
sys.path.append(os.path.dirname(os.path.abspath(os.path.dirname(__file__))))
import gen24bBMP as bmp


# Allow to create specific cases only if proper argument is given
target = -1  # -1 == ALL
if len(sys.argv) >= 2:  # There's some arguments
    target = int(sys.argv[1])

if target == -1 or target == 1:
    bmp.write('testcase01.rgb.golden', bmp.gen_RGB()[0])
    bmp.write('testcase01.bgrx.golden', bmp.gen_BGRx()[0])
if target == -1 or target == 2:
    bmp.write('testcase02_RGB_640x480.golden', bmp.gen_BMP_random('RGB', 640, 480, 'testcase02')[0])
    bmp.write('testcase02_BGRx_640x480.golden', bmp.gen_BMP_random('BGRx', 640, 480, 'testcase02')[0])
    bmp.write('testcase02_RGB_642x480.golden', bmp.gen_BMP_random('RGB', 642, 480, 'testcase02')[0])
    bmp.write('testcase02_BGRx_642x480.golden', bmp.gen_BMP_random('BGRx', 642, 480, 'testcase02')[0])
if target == -1 or target == 8:
    bmp.gen_BMP_stream('testsequence', 'testcase08.golden', 1)
if target == -1 or target == 9:
    buf = bmp.gen_BMP_random('RGB', 100, 100, 'testcase02')[0]
    bmp.write('testcase01_RGB_100x100.golden', buf)
    bmp.write('testcase02_RGB_100x100.golden', buf+buf)
    bmp.write('testcase03_RGB_100x100.golden', buf+buf+buf)
    bmp.gen_BMP_stream('testsequence01', 'testcase01.golden', 1)
    bmp.gen_BMP_stream('testsequence02', 'testcase02.golden', 2)
    bmp.gen_BMP_stream('testsequence03', 'testcase03.golden', 3)
    bmp.gen_BMP_stream('testsequence04', 'testcase04.golden', 4)
if target == -1 or target == 10:
    buf = bmp.gen_BMP_random('RGB', 100, 100, 'testcase')[0]
    bmp.write('testcase.golden', buf)
    bmp.gen_BMP_stream('testsequence', 'testcase_stream.golden', 1)
