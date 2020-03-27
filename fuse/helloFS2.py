import os, stat, errno

import fuse
from fuse import Fuse
from urllib2 import urlopen

# Need this otherwise fuse will complain
fuse.fuse_python_api = (0, 2)

hello_path = '/hello'

class HelloFS(Fuse):

    def getattr(self, path):
        st = fuse.Stat()
        if path == '/':
            st.st_mode = stat.S_IFDIR | 0o755
            st.st_nlink = 2
        elif path == hello_path:
            st.st_mode = stat.S_IFREG | 0o444
            st.st_nlink = 1
            data = str(urlopen("http://example.com").read())
            st.st_size = len(data)
        else:
            return -errno.ENOENT
        return st

    def readdir(self, path, offset):
        for r in  '.', '..', hello_path[1:]:
            yield fuse.Direntry(r)

    def open(self, path, flags):
        if path != hello_path:
            return -errno.ENOENT
        accmode = os.O_RDONLY | os.O_WRONLY | os.O_RDWR
        if (flags & accmode) != os.O_RDONLY:
            return -errno.EACCES

    def read(self, path, size, offset):
        if path != hello_path:
            return -errno.ENOENT
        data = str(urlopen("http://example.com").read())
        slen = len(data)
        if offset < slen:
            if offset + size > slen:
                size = slen - offset
            buf = data[offset:offset+size]
        else:
            buf = b''
        return buf

def main():
    fuseFS = HelloFS(version="%prog " + fuse.__version__,
                         dash_s_do='setsingle')
    fuseFS.parse(errex=1)
    fuseFS.main()

if __name__ == '__main__':
    main()
