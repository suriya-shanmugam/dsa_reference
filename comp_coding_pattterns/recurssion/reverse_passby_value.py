

def reverse (input_str) :
    
    if  len(input_str) == 0 :
        return []
    return reverse(input_str[1:]) + [input_str[0]]

input = "civ"
print(reverse(input))
    