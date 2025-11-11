from collections import Counter

tasks = ["X","X","Y","Y"]
n = 2
freq_by_task = Counter(tasks)
        #print(freq_by_task)
cycles = 0
window = []
while freq_by_task :
    
    max_task = -1
    max_freq = -1
    
    # Find max_task
    for task,freq in freq_by_task.items() :
        
        # Ignore if task in  hot_window
        hot_window = False
        
        for i in range( max(0,cycles-n),cycles) :
            if window[i] == -1 :
                continue
            if window[i] == task :
                hot_window = True
                break
        
        if hot_window :
            continue
        
            # Set Max - If not in window
        if freq > max_freq :
            max_task = task
            max_freq = freq
        
    if max_freq != -1 :
        freq_by_task[max_task] -= 1
        if freq_by_task[max_task] == 0 :
            freq_by_task.pop(max_task)
        
    window.append(max_task)
    cycles += 1

print(cycles)