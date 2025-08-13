s = "12345"

nums = list(s[::-1])  #Reversing using slicing   start:end:step 
total = 0
for num in nums :
	total += int(num)
print(total)

word = "civic"
print(f'''Is word {word} is palindrome { word == word[::-1] } ''')


applicant_id = [12,34,78,99,45,90,200,38,42]
# Let split them for two queues
print(applicant_id[0::2]) # Even Indices for queue1
print(applicant_id[1::2]) # Odd Indices for queue2

sentence = '''chunking is the process of breaking down large documents into smaller, manageable pieces, or chunks to improve the efficiency and accuracy of information retrieval and generation'''

chunks = [sentence[i:i+3] for i in range(0,len(sentence),3)]

print(chunks)

