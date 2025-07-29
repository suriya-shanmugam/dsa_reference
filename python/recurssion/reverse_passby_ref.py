
# pass by reference 

def reverse(input_list) :

    if  len(input_list) == 0 :
        print("Base case")
        return 
    
    firstletter = input_list[0]
    print("before - ", firstletter)
    input_list.pop(0)
    reverse(input_list)
    
    print("after - ", firstletter)
    input_list.append(firstletter)
    
    return 

input = ['s','u']
input.append('y')
print(input)
reverse(input)
print(input)


