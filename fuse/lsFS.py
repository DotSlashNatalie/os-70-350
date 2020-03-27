import errno
import stat

import fuse

# Need this otherwise pyfuse will refuse to mount
fuse.fuse_python_api = (0, 2)

#inherit from fuse.Fuse
class LsFS(fuse.Fuse):
    def getattr(self, path):
        # see https://www.gnu.org/software/libc/manual/html_node/Attribute-Meanings.html
        st = fuse.Stat()
        st.st_nlink = 1
        if path[1:] == "some_dir" or path == '/':
            st.st_mode = stat.S_IFDIR | 0755
        elif path[1:] == "some_file":
            st.st_mode = stat.S_IFREG | 0644
        else:
            return -errno.ENOENT
        return st

    def readdir(self, path, offset):
        if path == "/":
            # This is the directory listing basically
            for name in [".", "..", "some_file", "some_dir"]:
                yield fuse.Direntry(name)


def main():
    server = LsFS(dash_s_do='setsingle')
    server.parse()
    server.main()

if __name__ == '__main__':
    main()
