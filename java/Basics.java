import java.util.*;

public class Basics{

    public static void main(String[] args){
        
        
        
        // Primitive initialization
        int a = 10;
        double pi = 3.14;
        char letter = 'A';
        boolean flag = true;

        // Wrapper initialization
        Integer x = 100;        // autoboxing
        Double y = Double.valueOf(3.14);
        Character ch = 'B';     // autoboxing
        Boolean b = Boolean.TRUE;

        

        int index = 0;
        while (index < 5) {
            System.out.println(index);
            index++;
        }

        int j = 0;
        do {
            System.out.println(j);
            j++;
        } while (j < 5);

        int value = 10;
        if (value > 0) {
            System.out.println("Positive");
        } else if (value < 0) {
            System.out.println("Negative");
        } else {
            System.out.println("Zero");
        }

        // Ternary operator
        int num4 = 10;
        String result = (num4 > 0) ? "Positive" : "Non-positive";
        System.out.println(result);
        
        int day = 3;
        
        switch(day) {
            case 1:
                System.out.println("Monday");
                break;
            case 2:
                System.out.println("Tuesday");
                break;
            case 3:
                System.out.println("Wednesday");
                break;
            default:
                System.out.println("Other day");
        }

        for (int i=0; i<5; i++) {
        if (i==3) break;      // exits loop completely
            System.out.println(i);
        }

        for (int i=0; i<5; i++) {
            if (i==3) continue;   // skips current iteration
            System.out.println(i);
        }
        
        int[] prim_nums = {1,2,3,4,5};
        // Classic for-loop
        for(int i=0; i<prim_nums.length; i++) {
            System.out.println(prim_nums[i]);
        }

        // Enhanced for-loop
        for(int n : prim_nums) {
            System.out.println(n);
        }

        Integer[] numsObj = {10, 20, 30};

        for(int i=0; i<numsObj.length; i++) {
            System.out.println(numsObj[i]);
        }
        
        // Enhanced for-loop (wrapper array)
        for(Integer n : numsObj) {
            System.out.println(n);
        }
        
        
        // Primitive wrapper classes advantages

        // Collection compatability
        //ArrayList<int> numsList = new ArrayList<>(); // ❌ invalid
        ArrayList<Integer> numsList = new ArrayList<>(); // ✅ valid
        
        // Util Methods
        int p = Integer.parseInt("123");
        Double.isNaN(0.0 / 0.0);
        Character.isDigit('7');

        // Nullability
        Integer wow = null;  // valid
        //int x = null;      // ❌ invalid
        
        
        // Wrong comparison (WrapperObjects are Objects)
        Integer num1 = 128, same_num1 = 128;
        System.out.println(num1 == same_num1);       // false
        System.out.println(num1.equals(same_num1));  // true
        
        //Basic Conversion
        Integer[] arr = {1,2,3};
        List<Integer> arrList = Arrays.asList(arr);
        System.out.println(arrList);
        
        Integer[] back = arrList.toArray(new Integer[arrList.size()]);
        //Integer[] back = arrList.toArray(new Integer[0]);
        for (Integer num : back){
            System.out.println(num);
        }


        // Iteration
        ArrayList<Integer> sampleList = new ArrayList<>(Arrays.asList(10,20,30));
        for (int i = 0; i < sampleList.size(); i++) {
            System.out.println(sampleList.get(i));
        }
        for (Integer num : sampleList) {
            System.out.println(num);
        }
        
        Iterator<Integer> itr = sampleList.iterator();
        while (itr.hasNext()) {
            Integer n = itr.next();
            if (n == 20) itr.remove(); // safe removal during iteration
        }

        ListIterator<Integer> bdlit = sampleList.listIterator();
        while (bdlit.hasNext()) {
            System.out.println(bdlit.next());
        }
        while (bdlit.hasPrevious()) {
            System.out.println(bdlit.previous());
        }

        
        //ArrayList
        System.out.println("---ArrayList---");
        ArrayList<String> list = new ArrayList<>();
        list.add("Oranges");
        list.add(0,"apples");
        System.out.println(list);
        System.out.println(list.get(1));
        list.set(0,"Apple");
        list.remove(1);
        System.out.println(list.contains("Apple"));
        System.out.println( ""+list.size() );

        Iterator<String> it = list.iterator();
        while(it.hasNext()){
            System.out.println(it.next());
        }
        list.clear();
        System.out.println( ""+list.isEmpty() );
        
        

        //LinkedList
        System.out.println("---LinkedList---");
        LinkedList<Integer> numList = new LinkedList<>();
        numList.add(20);
        numList.addFirst(10);
        numList.addLast(100);
        System.out.println(numList);
        numList.removeFirst();
        numList.removeLast();
        System.out.println(numList);
        

        //HashSet
        System.out.println("---HashSet---");
        HashSet<String> set = new HashSet<>();
        set.add("Apple");
        set.add("Banana");
        System.out.println(""+set.contains("Banana"));
        System.out.println(set.size());
        set.clear();
        
        String[] fruits = {"Apple", "Banana", "Apple"};
        HashSet<String> seen = new HashSet<>();
        for(String s : fruits){
            if(!seen.add(s)){
                System.out.println("duplicate " + s);
            }
        }

        //HashMap
        System.out.println("---HashMap---");
        HashMap<String, Integer> map = new HashMap<>();
        map.put("Apple", 10);
        map.put("Banana", 20);
        System.out.println(map.get("Apple"));
        System.out.println(""+map.containsKey("Banana"));
        // Counting problems
        map.put("Apple", map.getOrDefault("Apple",0) + 10);
        
        for (String key: map.keySet() ){
            System.out.println(key);
        }

        for (Integer num : map.values()){
            System.out.println(num);
        }

        for (Map.Entry<String, Integer> entry : map.entrySet()){
            System.out.println(entry.getKey() + " " + entry.getValue());
        }

        Map<String, List<Integer>> groups = new HashMap<>();
        groups.computeIfAbsent("A", k -> new ArrayList<>()).add(10);
        groups.computeIfAbsent("A", k -> new ArrayList<>()).add(20);

        System.out.println(groups);

        
        // Queue
        System.out.println("---Basic Queue---");
        Queue<Integer> q = new LinkedList<>();
        q.offer(1);
        q.offer(2);
        System.out.println(q.peek());
        System.out.println(q.poll());

        //Stack
        System.out.println("-- Deque [Can be Stack]---");
        Deque<Integer> dq = new ArrayDeque<>();
        dq.push(10);
        dq.push(20);
        System.out.println(dq.pop());
        System.out.println(dq.peek());
        dq.addFirst(100);
        dq.addLast(200);
        System.out.println(dq.peekFirst()); // 100
        System.out.println(dq.pollLast());  // 200

        //PriorityQueue
        System.out.println("---PQ(Min Heap)---");
        PriorityQueue<Integer> minheap = new PriorityQueue<>();
        minheap.add(10);
        minheap.offer(20);
        System.out.println(minheap);
        System.out.println(minheap.peek());
        System.out.println(minheap.poll());
        System.out.println(minheap.size());


        //PriorityQueue
        System.out.println("---PQ(Max Heap)---");
        PriorityQueue<Integer> maxheap = new PriorityQueue<>(Collections.reverseOrder());
        maxheap.add(10);
        maxheap.offer(20);
        System.out.println(maxheap);
        System.out.println(maxheap.peek());
        System.out.println(maxheap.poll());
        System.out.println(maxheap.size());
        
        // Sorting
        List<Integer> nums = new ArrayList<>(Arrays.asList(5,3,8,1));
        Collections.sort(nums);
        //Collections.sort(nums, (a,b) -> b-a);
        System.out.println(nums);
        
        // Object overrided equals 
        System.out.println("---Object equals---");
        Car c1 = new Car("Ford");
        Car c2 = new Car("Ford");
        System.out.println( ""+c1.equals(c2) );
        
    }

}

class Car {
    
    String name;
    Car (String name)  {
        this.name = name;
    }
    
    void start(){
        System.out.println(this.name + " started...");
    }

    @Override
    public boolean equals(Object o){
        if (this == o) return true;
        if (!(o instanceof Car)) return false;
        Car c = (Car) o;
        return name.equals(c.name);

    }

}


