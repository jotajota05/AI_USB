#!/usr/bin/env python

"""
setup.py file for SWIG example
"""

from distutils.core import setup, Extension


example_module = Extension('_fitness',
                           sources=['fitness_wrap.cxx', 'fitness.cpp'],
                           )

setup (name = 'fitness',
       version = '0.1',
       author      = "SWIG Docs",
       description = """Simple swig example from docs""",
       ext_modules = [example_module],
       py_modules = ["fitness"],
       )
