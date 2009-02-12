#!/usr/bin/env python
import select
import sys
import re
import string

from os import sep
from os import path
import pybonjour

regtype = "_http._tcp"
timeout = 1
resolved = []
jsStrings = []

def htc(m):
    return chr(int(m.group(1)))

def urldecode(url):
    rex=re.compile('\\\(0[0-9a-hA-H][0-9a-hA-H])',re.M)
    return rex.sub(htc,url)

def resolve_callback(sdRef, flags, interfaceIndex, errorCode, fullname,
                     hosttarget, port, txtRecord):
    if errorCode == pybonjour.kDNSServiceErr_NoError:
        path = txtRecord[7:]
        print u"{'replyName':'%s','regType':'%s','url':'http://%s:%i/%s'}" \
        % (urldecode(fullname).replace('.'+regtype,'').replace('.local.',''), regtype, hosttarget, port, path)
        jsStrings.append(u"{'replyName':'%s','regType':'%s','url':'http://%s:%i/%s'}" \
        % (urldecode(fullname).replace('.'+regtype,'').replace('.local.',''), regtype, hosttarget, port, path))
        resolved.append(True)


def browse_callback(sdRef, flags, interfaceIndex, errorCode, serviceName,
                    regtype, replyDomain):
    if errorCode != pybonjour.kDNSServiceErr_NoError:
        return

    if not (flags & pybonjour.kDNSServiceFlagsAdd):
        # Removed
        return
    # Added
    resolve_sdRef = pybonjour.DNSServiceResolve(0,
                                                interfaceIndex,
                                                serviceName,
                                                regtype,
                                                replyDomain,
                                                resolve_callback)

    try:
        while not resolved:
            ready = select.select([resolve_sdRef], [], [], timeout)
            if resolve_sdRef not in ready[0]:
                # Resolve timed out
                break
            pybonjour.DNSServiceProcessResult(resolve_sdRef)
        else:
            resolved.pop()
    finally:
        resolve_sdRef.close()


browse_sdRef = pybonjour.DNSServiceBrowse(regtype = regtype,
                                          callBack = browse_callback)

try:
    try:
        ready = select.select([browse_sdRef], [], [], 1)
        if browse_sdRef in ready[0]:
            pybonjour.DNSServiceProcessResult(browse_sdRef)
            self_path = path.dirname(unicode(sys.executable, sys.getfilesystemencoding()))
            output_path = "%s%s..%scontent%s" % (self_path, sep, sep, sep)
            output = u'[%s]' % (u','.join(jsStrings))
            output = output.encode("utf-8")
            fout = open("%sservices.json" % (output_path), "w")
            fout.write( output )
            fout.close()
    except KeyboardInterrupt:
        pass
finally:
    browse_sdRef.close()
