#!/usr/bin/env python

import os
import sys

# Variables configured at build time.
llvm_source_root = "C:/slaves/emslave/buildslave/win-tagbuilder/emsdk/clang/tag-e1.37.9/src"
llvm_obj_root = "C:/slaves/emslave/buildslave/win-tagbuilder/emsdk/clang/tag-e1.37.9/build_tag-e1.37.9_vs2015_64"

# Make sure we can find the lit package.
sys.path.insert(0, os.path.join(llvm_source_root, 'utils', 'lit'))

# Set up some builtin parameters, so that by default the LLVM test suite
# configuration file knows how to find the object tree.
builtin_parameters = {
    'build_mode' : "Release",
    'llvm_site_config' : os.path.join(llvm_obj_root, 'test', 'lit.site.cfg'),
    'llvm_unit_site_config' : os.path.join(llvm_obj_root, 'test', 'Unit',
                                           'lit.site.cfg')
    }

clang_obj_root = os.path.join(llvm_obj_root, 'tools', 'clang')

if os.path.exists(clang_obj_root):
    builtin_parameters['clang_site_config'] = \
        os.path.join(clang_obj_root, 'test', 'lit.site.cfg')
    clang_tools_extra_obj_root = os.path.join(clang_obj_root, 'tools', 'extra')
    if os.path.exists(clang_tools_extra_obj_root):
        builtin_parameters['clang_tools_extra_site_config'] = \
            os.path.join(clang_tools_extra_obj_root, 'test', 'lit.site.cfg')

lld_obj_root = os.path.join(llvm_obj_root, 'tools', 'lld')
if os.path.exists(lld_obj_root):
    builtin_parameters['lld_site_config'] = \
        os.path.join(lld_obj_root, 'test', 'lit.site.cfg')

compilerrt_obj_root = os.path.join(llvm_obj_root, 'projects', 'compiler-rt')
if os.path.exists(compilerrt_obj_root):
    builtin_parameters['compilerrt_site_basedir'] = \
            os.path.join(compilerrt_obj_root, 'test')

if __name__=='__main__':
    from lit.main import main
    main(builtin_parameters)
