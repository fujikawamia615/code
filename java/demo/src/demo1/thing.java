package demo1;

import java.util.Comparator;

public abstract class thing implements Comparable<thing>{
    public String name;
    public double price;
    public int compareTo(thing other){
        return this.name.compareTo(other.name);
    }
    public static class Pricecomparator implements Comparator<thing>{
        @Override
        public int compare(thing a,thing b){
            if(a.price>b.price){
                return 1;
            }
            else if(a.price==b.price){
                return 0;
            }
            else{
                return -1;
            }
        }
    }
    public String getname(){
        return this.name;
    }
    public double getprice(){
        return this.price;
    }
    public abstract String returntype();
}
