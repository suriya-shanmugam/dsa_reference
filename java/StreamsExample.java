import java.util.*;
import java.util.stream.Collectors;
class Pair{
    String name;
    Integer value;
    Pair (String name, Integer value){
        this.name = name;
        this.value = value;
    }
}
public class StreamsExample {
    public static void main(String[] args){
        
        Integer[] nums = {1,2,300,-1};
        List<Integer> sorted = Arrays.stream(nums)
                                .sorted()
                                .toList();
        
        sorted = Arrays.stream(nums)
                    .sorted(Comparator.reverseOrder())
                    .toList();
                               
        
        System.out.println("sorting streams");
        for (Integer num : sorted){
            System.out.println(num);
        }

        
        ArrayList<Pair> freqs = new ArrayList<>();
        freqs.add(new Pair("A", 10));
        freqs.add(new Pair("B", 5));
        freqs.add(new Pair("C", 50));
        freqs.add(new Pair("AC", 50));

        ArrayList<Pair> filtered = freqs.stream()
            .filter(freq -> freq.value > 10)
            .collect(Collectors.toCollection(ArrayList::new));

        for (Pair p : filtered){
            System.out.println(p.name);
            System.out.println(p.value);
        }

        List<Pair> customSorted = freqs.stream()
                                .sorted(Comparator.comparing( (Pair freq) -> freq.value ).reversed()
                                                  .thenComparing((Pair freq) -> freq.name))
                                .toList();
        
        System.out.println("sorting custom streams");
        for (Pair p : customSorted){
            System.out.print(p.name);
            System.out.print("-" + p.value);
            System.out.println();
        }
        
        
    }
}
