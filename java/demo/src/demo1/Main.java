package demo1;

public class Main {
    public static void main(String[] args) {
        bookcontainer container=new bookcontainer();
        book demoBook=new book("lightnovel","Tomorrow, When Spring Comes",58.50);
        container.save(demoBook);//存入物品
        container.iteratorTraverse();//遍历
        container.get(0);//通过索引取走物品
        container.iteratorTraverse();
        container.sort(0);//名称排序
        container.iteratorTraverse();
        container.sort(1);//价格排序
        container.iteratorTraverse();
        container.search(58.50);//查找
        container.statistics();//统计
    }
}
