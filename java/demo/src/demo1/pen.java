package demo1;

public class pen extends thing implements studything{
    public pen(){
        this.name="default";
        this.price=0.00;
    }
    public pen(String name,double price){
        this.name=name;
        this.price=price;
    }
    @Override
    public String toString(){
        return "name="+this.name+" price="+this.price;
    }
    @Override
    public String returntype(){
        return "pen";
    }
    @Override
    public void study(){
        System.out.println("study");
    }
}
