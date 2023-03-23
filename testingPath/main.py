def _print_path(filename):
    f = open(filename, "r")
    paths = f.readline()
    f.close()
    list_of_paths = paths.split(":")

    for path in list_of_paths:
        print(path)

_print_path("path.txt")
print("----------------------")
_print_path("path2.txt")