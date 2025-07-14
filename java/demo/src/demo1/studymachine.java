package demo1;

public class studymachine extends thing implements studything{
    public studymachine(){
        this.name="default";
        this.price=0.00;
    }
    public studymachine(String name,double price){
        this.name=name;
        this.price=price;
    }
    @Override
    public String toString(){
        return "name="+this.name+" price="+this.price;
    }
    @Override
    public String returntype(){
        return "studymachine";
    }
    @Override
    public void study(){
        System.out.println("study");
    }
}
