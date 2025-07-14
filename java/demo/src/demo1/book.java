package demo1;

public class book extends thing implements studything{
    String type;
    public book(){
        this.type="default";
        this.name="default";
        this.price=0.00;
    }
    public book(String type,String name,double price){
        this.type=type;
        this.name=name;
        this.price=price;
    }
    @Override
    public String toString(){
        return "name="+this.name+" type="+this.type+" price="+this.price;
    }
    @Override
    public String returntype(){
        return "book";
    }
    @Override
    public void study(){
        System.out.println("study");
    }
}
