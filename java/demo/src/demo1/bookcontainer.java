package demo1;

import java.util.*;
import java.util.stream.Collectors;

import demo1.thing.Pricecomparator;

public class bookcontainer {
    List<thing> list=new ArrayList<>();
    public bookcontainer(){
        book a=new book("lightnovel","Bizarre Love Triangle",52.80);
        pen b=new pen("mypen",30.70);
        studymachine c=new studymachine("eebbk",66.66);
        list.add(a);
        list.add(b);
        list.add(c);
    }
    public void save(thing a){
        list.add(a);
    }
    public void get(int a){
        list.remove(a);
    }
    public void normalTraverse(){
        for(Object a : list){
            System.out.println(a.toString());
        }
        System.out.println();
    }
    public void iteratorTraverse(){
        Iterator<thing> a=list.iterator();
        while(a.hasNext()){
            System.out.println(a.next().toString());
        }
        System.out.println();
    }
    public void statistics(){
        Map<String,Integer> map=new HashMap<>();
        for(thing a : list){
            String b=a.returntype();
            if(!map.containsKey(b)){
                map.put(b,1);
            }
            else{
                int c=map.get(b);
                c++;
                map.put(b,c);
            }
        }
        map.forEach((key,value)->{System.out.println("type:"+key+" num:"+value);});
        System.out.println();
    }
    public void sort(int n){
        if(n==0){
            Collections.sort(list);
        }
        else{
            Collections.sort(list,new Pricecomparator());
        }
    }
    public void search(double n){
        Collections.sort(list,new Pricecomparator());
        List<Double> pricelist  = list.stream().map(thing::getprice).collect(Collectors.toList());
        int index=Collections.binarySearch(pricelist, n);
        if(index<0){
            System.out.println("not found");
        }
        else{
            System.out.println(list.get(index).toString());
        }
        System.out.println();
    }
}
