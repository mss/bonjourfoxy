import sys, os
from distutils.core import setup
from py2exe.build_exe import py2exe

import psyco
psyco.full()

if os.name == 'nt':
    setup(name='bonjour2content-json',
          version='0.1',
          description = "",
          long_description="",
          url='http://bonjourfoxy.sf.net',
          author='Andrew Tunnell-Jones',
          author_email='andrew@tj.id.au',
          console=['bonjour2content-json.py'],
          options={"py2exe": {
                        "optimize": 2,
                        "bundle_files": 1
                        }
                   },
          zipfile = None
          )
else:
    print "I'll get to ya...."