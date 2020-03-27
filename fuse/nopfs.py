import fuse

# Need this otherwise pyfuse will refuse to mount
fuse.fuse_python_api = (0, 2)

#inherit from fuse.Fuse
class NopFS(fuse.Fuse):
    pass


def main():
    # run fuse in a blocking loop
    server = NopFS()
    server.parse()
    server.main()

if __name__ == '__main__':
    main()
