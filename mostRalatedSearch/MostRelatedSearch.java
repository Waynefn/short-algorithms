package li;
import java.util.*;

public class Main  {

	public static String getMaxWord(Map<String,Set<String>> usersList, Set<String> users, String thisWord) throws Exception {
		Map<String,Integer> count=new HashMap<String, Integer>();
		for(String u:users) {
			for(String w:usersList.get(u)) {
				if(w.equals(thisWord))continue;
				if(count.containsKey(w)) {
					count.put(w, count.get(w)+1);
				}
				else {
					count.put(w, 1);
				}
			}
		}
		if(count.size()==0)return "0";
		List<Map.Entry<String,Integer>> list=new ArrayList<Map.Entry<String,Integer>>(count.entrySet());
		Collections.sort(list, new Comparator<Map.Entry<String, Integer>>() {  
		    public int compare(Map.Entry<String, Integer> e1,  
		            Map.Entry<String, Integer> e2) {  
		        if (e1.getValue()== e2.getValue()) {
		        	return e1.getKey().compareTo(e2.getKey());
		        }
		        else {
		        	return e2.getValue()- e1.getValue();
		        }
		    }  
		});

		
		Integer freq=list.get(0).getValue();
		String result=freq.toString();
		for(Map.Entry<String,Integer> l:list) {
			if(l.getValue()==freq)
				result=result+" "+l.getKey();
			else break;
		}
		return result;
	}

    public static void main(String args[] ) throws Exception {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT */
        Map<String,Set<String>> wordsList= new HashMap<String,Set<String>>();
        Map<String,Set<String>> usersList= new HashMap<String,Set<String>>();
    	Scanner sc = new Scanner(System.in);
        int Num = sc.nextInt();
        for(int i=0;i<Num;i++) {
        	String user=sc.next();
        	String word=sc.next();
        	
        	if(!usersList.containsKey(user)) {
        		Set<String> list=new HashSet<String>();
        		list.add(word);
        		usersList.put(user, list);
        	}
        	else {
        		usersList.get(user).add(word);
        	}
        	
        	if(!wordsList.containsKey(word)) {
        		Set<String> list=new HashSet<String>();
        		list.add(user);
        		wordsList.put(word, list);
        		System.out.println("0");
        	}else {
        		System.out.println(Main.getMaxWord(usersList, wordsList.get(word),word));
        		wordsList.get(word).add(user);
        	}
        }
        sc.close();
    }
}
