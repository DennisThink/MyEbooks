public class Clone{
    

    class CloneEnable{
        @Override
        public CloneEnable clone(){
            return new CloneEnable();
        }

        @Override
        public String toString(){
            return "CloneEnable";
        }
    }

   static class CloneDisable{

    }
    public static void main(String[] args){
       /* CloneEnable ena = new CloneEnable();
        try{
            CloneEnable copy = ena.clone();
            System.out.println(copy.toString());
        }
        catch(CloneNotSupportedException e){
            System.out.println(e);
        }*/

        Clone c = new Clone();
        System.out.println(c.toString());
       
    }

    
}