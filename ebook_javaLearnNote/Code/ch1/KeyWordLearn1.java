
class FileClassOne
{
    public void Print()
    {
        System.out.println("FileClassOne");
    }
}

class FileClassTwo
{
    public void Print()
    {
        System.out.println("FileClassTwo");
    }
}


public class KeyWordLearn1
{
    public int m_publicValue = 0;
    protected int m_protectedValue =1;
    private int m_privateValue = 2;

    public void Print()
    {
        FinalizeTest t = new FinalizeTest();
        t.Print();
        System.out.println(this.m_publicValue);
        System.out.println(this.m_protectedValue);
        System.out.println(this.m_privateValue);
    }
    class FinalizeTest
    {  
        public void Print()
        {
            FileClassOne one = new FileClassOne();
            one.Print();
            System.out.println("Outer ");
            System.out.println("Print");
        }
    }


    static class StaticClassTest
    {
        public void Print()
        {
            System.out.println("StaticClassTest  Print");
        }
    }

    public static void main(String[] argv)
    {
        System.out.println("KeyWordLearn1");
        KeyWordLearn1 learn1 = new KeyWordLearn1();
        learn1.Print();

        StaticClassTest t2 = new StaticClassTest();
        t2.Print();

        FileClassOne one = new FileClassOne();
        one.Print();

        FileClassTwo two = new FileClassTwo();
        two.Print();
    }
}