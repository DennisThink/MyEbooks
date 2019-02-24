public class Item25{
    public static void main(String[] argv){
        //Fails at runtime
        Object[] objectArray = new Long[1];
        objectArray[0] = "I don't fit in";//Throw ArrayStoreException
    }
}