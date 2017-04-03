#!/usr/bin/python

# -*- coding: utf-8 -*-
"""
Created on Sun Nov 27 00:46:20 2016

@author: okan
"""

import sys

fp = open('out.txt', 'a+')
fp.write(sys.argv[1]+"\n")
fp.close()
fp1=open('out1.txt','a+')
fp1.write('anan\n')
fp1.close()
