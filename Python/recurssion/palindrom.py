
def ispalindrom( input_str )  :

    if len(input_str) <= 1 :
        return True

    if input_str[0] != input_str[len(input_str)-1]:
        return False
    
    return ispalindrom(input_str[1:len(input_str)-1])


input = "amma"
print(ispalindrom(input))

