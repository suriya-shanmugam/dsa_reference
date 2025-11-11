# split -> List[substrings]
s = "suriya&shanmugam&ms&sanjose"
info = s.split('&')
print(info)

# partition -> tuple(first, partition, second)
s = "firstname=suriya"
key_sep_value = s.partition("=")  # Returns tuple order first, partition, second
print(key_sep_value)

# use join instead of += 
sentence = "Use double quotes by default if your team uses a formatter like Black it will enforce them anyway"

tokens = sentence.split(" ")
res = ""
for token in tokens:
	res += token + " " #bad performance as string is immutable - new memory allocated time and copied
print(res)

optimized_res = " ".join(tokens)
print(optimized_res)

encoded_str = r'''suriya\textbf{shanmugam} phone \textbf{2323232323}'''
bold_text_idx = encoded_str.find(r'''\textbf''') # Return first occurance
print(bold_text_idx) # Returns -1 if not found

bold_text_right_idx = encoded_str.rfind(r'''\textbf''')
print(bold_text_right_idx)

total_bold_count = encoded_str.count(r'''\textbf''')
print(total_bold_count)

multi_line = '''1.Suriya
2.MS in SE
3.Sanjose
'''
print(multi_line.splitlines()) # natural line split

name = "Suriya shanmugam"
print(name.lower())
print(name.upper())
print(name.title()) # capitalize first letter of every word
print(name.capitalize()) # Capitalize first letter only 

log = "#####LOGGER#######"
print(log.strip("#"))
print(log.rstrip("#"))
print(log.lstrip("#"))

print(log.replace("#","-"))


