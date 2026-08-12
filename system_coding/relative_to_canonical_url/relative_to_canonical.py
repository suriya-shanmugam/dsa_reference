
def canonical_path(path : str) -> list :     
    stack = []
    for resource in path.split('/') :
        if resource == "" or resource == '/' or resource == '.' :
            continue
        if resource == ".." :
            stack.pop()
            continue
        stack.append(resource)

    return "/" + "/".join(stack)

test1 = "/a/b//c"
print(canonical_path(test1) )
assert canonical_path(test1) == "/a/b/c"

test2 = "/a/./c"
print(canonical_path(test2) )
assert canonical_path(test2) == "/a/c"

test3 = "/a/../c"
print(canonical_path(test3) )
assert canonical_path(test3) == "/c"